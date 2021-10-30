#ifndef JNT_LINUX_TYPES_H
#define JNT_LINUX_TYPES_H

#define JNT_CDECL __attribute__((__cdecl__))

#ifndef __cdecl
#define __cdecl
#endif

#include <dxgiformat.h>
#include <assert.h>
#include <cstdarg>
#include <cstdint>
#include <math.h>
#include <wchar.h>

//Sal annotations
#define _Use_decl_annotations_
#define _In_
#define _In_opt_
#define _In_z_
#define _In_reads_(size)
#define _In_reads_opt_(size)
#define _In_reads_bytes_(size)
#define _Out_
#define _Out_opt_
#define _Out_writes_(size)
#define _Out_writes_opt_(size)
#define _Out_writes_bytes_(size)
#define _Inout_
#define _Inout_opt_
#define _Inout_updates_all_(size)
#define _Inout_updates_all_opt_(size)
#define _Inout_updates_bytes_all_(size)
#define _When_(expr, annotes)
#define _Printf_format_string_
#define _Analysis_assume_(expr)
#define __in_ecount(size)
#define __out_ecount(size)
#define _Success_(expr)
#define _Analysis_assume_(expr)

//------------------------------------------------------------------------------

#ifndef _HRESULT_DEFINED
#define _HRESULT_DEFINED
typedef int32_t HRESULT;
#endif // !_HRESULT_DEFINED

//HRESULT Codes
#define S_OK                             ((HRESULT)0L)
#define S_FALSE                          ((HRESULT)1L)
#define E_FAIL                           ((HRESULT)0x80004005L)
#define E_OUTOFMEMORY                    ((HRESULT)0x8007000EL)
#define E_INVALIDARG                     ((HRESULT)0x80070057L)
#define E_UNEXPECTED                     ((HRESULT)0x8000FFFFL)
#define E_ABORT                          ((HRESULT)0x80004004L)
#define E_POINTER                        ((HRESULT)0x80004003L)
#define ERROR_INVALID_DATA               13L
#define ERROR_ARITHMETIC_OVERFLOW        534L
#define ERROR_NOT_SUPPORTED              50L

#define SUCCEEDED(hr) (((HRESULT)(hr)) >= 0)
#define FAILED(hr) (((HRESULT)(hr)) < 0)
#define FACILITY_WIN32                   7
static HRESULT HRESULT_FROM_WIN32(unsigned long x)
{
    return (HRESULT)(x) <= 0 ?
           (HRESULT)(x) :
           (HRESULT)(((x) & 0x0000FFFF) | (FACILITY_WIN32 << 16) | 0x80000000);
}

//------------------------------------------------------------------------------

#define WINAPI __attribute__((stdcall))
#define STDMETHOD(method) virtual __attribute__((nothrow,stdcall)) HRESULT method
#define STDMETHODIMP HRESULT __attribute__((stdcall))
#define PURE = 0
#define UNREFERENCED_PARAMETER(P) (P)

#define __max(a,b) (((a) > (b)) ? (a) : (b))
#define __min(a,b) (((a) < (b)) ? (a) : (b))
static int swprintf_s(wchar_t* buff, const wchar_t* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vswprintf(buff, sizeof(buff) / sizeof(*buff), fmt, args);
};

typedef unsigned long DWORD;
typedef const char* LPCSTR;
typedef void* HANDLE;
typedef long long LONG_PTR;
#define INVALID_HANDLE_VALUE ((HANDLE)(LONG_PTR)-1)

//------------------------------------------------------------------------------

//DirectXMath Port

#define XM_CONST constexpr
#define XM_CONSTEXPR constexpr
#define XM_CALLCONV __attribute__((fastcall))

namespace DirectX
{

XM_CONST float XM_PI        = 3.141592654f;
XM_CONST float XM_2PI       = 6.283185307f;
XM_CONST float XM_1DIVPI    = 0.318309886f;
XM_CONST float XM_1DIV2PI   = 0.159154943f;
XM_CONST float XM_PIDIV2    = 1.570796327f;
XM_CONST float XM_PIDIV4    = 0.785398163f;

struct __vector4
{
    union
    {
        float vector4_f32[4];
        uint32_t vector4_u32[4];
    };
};
//------------------------------------------------------------------------------
// Vector intrinsic: Four 32 bit floating point components aligned on a 16 byte
// boundary and mapped to hardware vector registers
typedef __vector4 XMVECTOR;
typedef const XMVECTOR& FXMVECTOR;
typedef const XMVECTOR& CXMVECTOR;

//------------------------------------------------------------------------------
// Matrix type: Sixteen 32 bit floating point components aligned on a
// 16 byte boundary and mapped to four hardware vector registers
struct XMMATRIX;
typedef const XMMATRIX& FXMMATRIX;
typedef const XMMATRIX& CXMMATRIX;

//------------------------------------------------------------------------------
// Conversion types for constants
__attribute__((align(16))) struct XMVECTORF32
{
    union
    {
        float f[4];
        XMVECTOR v;
    };

    inline operator XMVECTOR() const
    {
        return v;
    }
    inline operator const float* () const
    {
        return f;
    }
};

__attribute((align(16))) struct XMVECTORU32
{
    union
    {
        uint32_t u[4];
        XMVECTOR v;
    };

    inline operator XMVECTOR() const
    {
        return v;
    }
};

//------------------------------------------------------------------------------
// 2D Vector; 32 bit floating point components
struct XMFLOAT2
{
    float x;
    float y;

    XMFLOAT2() = default;

    XMFLOAT2(const XMFLOAT2&) = default;
    XMFLOAT2& operator=(const XMFLOAT2&) = default;

    XMFLOAT2(XMFLOAT2&&) = default;
    XMFLOAT2& operator=(XMFLOAT2&&) = default;

    XM_CONSTEXPR XMFLOAT2(float _x, float _y) : x(_x), y(_y) {}
    explicit XMFLOAT2(_In_reads_(2) const float* pArray) : x(pArray[0]), y(pArray[1]) {}
};

//------------------------------------------------------------------------------
// 3D Vector; 32 bit floating point components
struct XMFLOAT3
{
    float x;
    float y;
    float z;

    XMFLOAT3() = default;

    XMFLOAT3(const XMFLOAT3&) = default;
    XMFLOAT3& operator=(const XMFLOAT3&) = default;

    XMFLOAT3(XMFLOAT3&&) = default;
    XMFLOAT3& operator=(XMFLOAT3&&) = default;

    XM_CONSTEXPR XMFLOAT3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    explicit XMFLOAT3(_In_reads_(3) const float* pArray) : x(pArray[0]), y(pArray[1]), z(pArray[2]) {}
};

//------------------------------------------------------------------------------
// 4D Vector; 32 bit floating point components
struct XMFLOAT4
{
    float x;
    float y;
    float z;
    float w;

    XMFLOAT4() = default;

    XMFLOAT4(const XMFLOAT4&) = default;
    XMFLOAT4& operator=(const XMFLOAT4&) = default;

    XMFLOAT4(XMFLOAT4&&) = default;
    XMFLOAT4& operator=(XMFLOAT4&&) = default;

    XM_CONSTEXPR XMFLOAT4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
    explicit XMFLOAT4(_In_reads_(4) const float* pArray) : x(pArray[0]), y(pArray[1]), z(pArray[2]), w(pArray[3]) {}
};

// 4D Vector; 32 bit floating point components aligned on a 16 byte boundary
__attribute__((align(16))) struct XMFLOAT4A : public XMFLOAT4
{
    XMFLOAT4A() = default;

    XMFLOAT4A(const XMFLOAT4A&) = default;
    XMFLOAT4A& operator=(const XMFLOAT4A&) = default;

    XMFLOAT4A(XMFLOAT4A&&) = default;
    XMFLOAT4A& operator=(XMFLOAT4A&&) = default;

    XM_CONSTEXPR XMFLOAT4A(float _x, float _y, float _z, float _w) : XMFLOAT4(_x, _y, _z, _w) {}
    explicit XMFLOAT4A(_In_reads_(4) const float* pArray) : XMFLOAT4(pArray) {}
};

struct XMMATRIX
{
    union
    {
        XMVECTOR r[4];
        struct
        {
            float _11, _12, _13, _14;
            float _21, _22, _23, _24;
            float _31, _32, _33, _34;
            float _41, _42, _43, _44;
        };
        float m[4][4];
    };

    XMMATRIX() = default;

    XMMATRIX(const XMMATRIX&) = default;

    XMMATRIX& operator=(const XMMATRIX&) = default;

    XMMATRIX(XMMATRIX&&) = default;
    XMMATRIX& operator=(XMMATRIX&&) = default;

    constexpr XMMATRIX(FXMVECTOR R0, FXMVECTOR R1, FXMVECTOR R2, CXMVECTOR R3) : r{ R0, R1, R2, R3 } {}
    XMMATRIX(float m00, float m01, float m02, float m03,
             float m10, float m11, float m12, float m13,
             float m20, float m21, float m22, float m23,
             float m30, float m31, float m32, float m33);
    explicit XMMATRIX(_In_reads_(16) const float* pArray);

    float       operator()(size_t Row, size_t Column) const
    {
        return m[Row][Column];
    }
    float&      operator()(size_t Row, size_t Column)
    {
        return m[Row][Column];
    }

    XMMATRIX    operator+ () const
    {
        return *this;
    }
    XMMATRIX    operator- () const;

    XMMATRIX&   XM_CALLCONV     operator+= (FXMMATRIX M);
    XMMATRIX&   XM_CALLCONV     operator-= (FXMMATRIX M);
    XMMATRIX&   XM_CALLCONV     operator*= (FXMMATRIX M);
    XMMATRIX&   operator*= (float S);
    XMMATRIX&   operator/= (float S);

    XMMATRIX    XM_CALLCONV     operator+ (FXMMATRIX M) const;
    XMMATRIX    XM_CALLCONV     operator- (FXMMATRIX M) const;
    XMMATRIX    XM_CALLCONV     operator* (FXMMATRIX M) const;
    XMMATRIX    operator* (float S) const;
    XMMATRIX    operator/ (float S) const;

    friend XMMATRIX     XM_CALLCONV     operator* (float S, FXMMATRIX M);
};

//------------------------------------------------------------------------------
// 4x4 Matrix: 32 bit floating point components
struct XMFLOAT4X4
{
    union
    {
        struct
        {
            float _11, _12, _13, _14;
            float _21, _22, _23, _24;
            float _31, _32, _33, _34;
            float _41, _42, _43, _44;
        };
        float m[4][4];
    };

    XMFLOAT4X4() = default;

    XMFLOAT4X4(const XMFLOAT4X4&) = default;
    XMFLOAT4X4& operator=(const XMFLOAT4X4&) = default;

    XMFLOAT4X4(XMFLOAT4X4&&) = default;
    XMFLOAT4X4& operator=(XMFLOAT4X4&&) = default;

    XM_CONSTEXPR XMFLOAT4X4(float m00, float m01, float m02, float m03,
                            float m10, float m11, float m12, float m13,
                            float m20, float m21, float m22, float m23,
                            float m30, float m31, float m32, float m33)
        : _11(m00), _12(m01), _13(m02), _14(m03),
          _21(m10), _22(m11), _23(m12), _24(m13),
          _31(m20), _32(m21), _33(m22), _34(m23),
          _41(m30), _42(m31), _43(m32), _44(m33) {}
    explicit XMFLOAT4X4(_In_reads_(16) const float* pArray);

    float       operator()(size_t Row, size_t Column) const
    {
        return m[Row][Column];
    }
    float&      operator()(size_t Row, size_t Column)
    {
        return m[Row][Column];
    }
};

#define XMGLOBALCONST const __attribute__((seletany))
XMGLOBALCONST XMVECTORF32 g_XMIdentityR0            = { { { 1.0f, 0.0f, 0.0f, 0.0f } } };
XMGLOBALCONST XMVECTORF32 g_XMIdentityR1            = { { { 0.0f, 1.0f, 0.0f, 0.0f } } };
XMGLOBALCONST XMVECTORF32 g_XMIdentityR2            = { { { 0.0f, 0.0f, 1.0f, 0.0f } } };
XMGLOBALCONST XMVECTORF32 g_XMIdentityR3            = { { { 0.0f, 0.0f, 0.0f, 1.0f } } };
XMGLOBALCONST XMVECTORF32 g_XMOne                   = { { { 1.0f, 1.0f, 1.0f, 1.0f } } };
XMGLOBALCONST XMVECTORF32 g_XMTwo                   = { { { 2.0f, 2.0f, 2.0f, 2.0f } } };
XMGLOBALCONST XMVECTORF32 g_XMZero                  = { { { 0.0f, 0.0f, 0.0f, 0.0f } } };
XMGLOBALCONST XMVECTORF32 g_XMNegativeOne           = { { { -1.0f, -1.0f, -1.0f, -1.0f } } };

//------------------------------------------------------------------------------
// Return a vector with all elements equaling zero
inline XMVECTOR XM_CALLCONV XMVectorZero()
{
    XMVECTORF32 vResult = { { { 0.0f, 0.0f, 0.0f, 0.0f } } };
    return vResult.v;
}

//------------------------------------------------------------------------------
// Initialize a vector with four floating point values
inline XMVECTOR XM_CALLCONV XMVectorSet
(
    float x,
    float y,
    float z,
    float w
)
{
    XMVECTORF32 vResult = { { { x, y, z, w } } };
    return vResult.v;
}

//------------------------------------------------------------------------------
// Initialize a vector with a replicated floating point value
inline XMVECTOR XM_CALLCONV XMVectorReplicate
(
    float Value
)
{
    XMVECTORF32 vResult;
    vResult.f[0] =
        vResult.f[1] =
            vResult.f[2] =
                vResult.f[3] = Value;
    return vResult.v;
}

//------------------------------------------------------------------------------
// Replicate the x component of the vector
inline XMVECTOR XM_CALLCONV XMVectorSplatX
(
    FXMVECTOR V
)
{
    XMVECTORF32 vResult;
    vResult.f[0] =
        vResult.f[1] =
            vResult.f[2] =
                vResult.f[3] = V.vector4_f32[0];
    return vResult.v;
}

//------------------------------------------------------------------------------
// Replicate the y component of the vector
inline XMVECTOR XM_CALLCONV XMVectorSplatY
(
    FXMVECTOR V
)
{
    XMVECTORF32 vResult;
    vResult.f[0] =
        vResult.f[1] =
            vResult.f[2] =
                vResult.f[3] = V.vector4_f32[1];
    return vResult.v;
}

//------------------------------------------------------------------------------
// Replicate the z component of the vector
inline XMVECTOR XM_CALLCONV XMVectorSplatZ
(
    FXMVECTOR V
)
{
    XMVECTORF32 vResult;
    vResult.f[0] =
        vResult.f[1] =
            vResult.f[2] =
                vResult.f[3] = V.vector4_f32[2];
    return vResult.v;
}

//------------------------------------------------------------------------------
// Replicate the w component of the vector
inline XMVECTOR XM_CALLCONV XMVectorSplatW
(
    FXMVECTOR V
)
{
    XMVECTORF32 vResult;
    vResult.f[0] =
        vResult.f[1] =
            vResult.f[2] =
                vResult.f[3] = V.vector4_f32[3];
    return vResult.v;
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMLoadFloat2
(
    const XMFLOAT2* pSource
)
{
    assert(pSource);
    XMVECTOR V;
    V.vector4_f32[0] = pSource->x;
    V.vector4_f32[1] = pSource->y;
    V.vector4_f32[2] = 0.f;
    V.vector4_f32[3] = 0.f;
    return V;
}

//------------------------------------------------------------------------------

inline void XM_CALLCONV XMStoreFloat2
(
    XMFLOAT2* pDestination,
    FXMVECTOR  V
)
{
    assert(pDestination);
    pDestination->x = V.vector4_f32[0];
    pDestination->y = V.vector4_f32[1];
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMLoadFloat3
(
    const XMFLOAT3* pSource
)
{
    assert(pSource);
    XMVECTOR V;
    V.vector4_f32[0] = pSource->x;
    V.vector4_f32[1] = pSource->y;
    V.vector4_f32[2] = pSource->z;
    V.vector4_f32[3] = 0.f;
    return V;
}

//------------------------------------------------------------------------------

inline void XM_CALLCONV XMStoreFloat3
(
    XMFLOAT3* pDestination,
    FXMVECTOR V
)
{
    assert(pDestination);
    pDestination->x = V.vector4_f32[0];
    pDestination->y = V.vector4_f32[1];
    pDestination->z = V.vector4_f32[2];
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMLoadFloat4
(
    const XMFLOAT4* pSource
)
{
    assert(pSource);
    XMVECTOR V;
    V.vector4_f32[0] = pSource->x;
    V.vector4_f32[1] = pSource->y;
    V.vector4_f32[2] = pSource->z;
    V.vector4_f32[3] = pSource->w;
    return V;
}

//------------------------------------------------------------------------------
inline void XM_CALLCONV XMStoreFloat4
(
    XMFLOAT4* pDestination,
    FXMVECTOR  V
)
{
    assert(pDestination);
    pDestination->x = V.vector4_f32[0];
    pDestination->y = V.vector4_f32[1];
    pDestination->z = V.vector4_f32[2];
    pDestination->w = V.vector4_f32[3];
}

//------------------------------------------------------------------------------
_Use_decl_annotations_
inline void XM_CALLCONV XMStoreFloat4A
(
    XMFLOAT4A*   pDestination,
    FXMVECTOR     V
)
{
    assert(pDestination);
    assert((reinterpret_cast<uintptr_t>(pDestination) & 0xF) == 0);

    pDestination->x = V.vector4_f32[0];
    pDestination->y = V.vector4_f32[1];
    pDestination->z = V.vector4_f32[2];
    pDestination->w = V.vector4_f32[3];
}
//------------------------------------------------------------------------------
// Return the X component in an FPU register.
inline float XM_CALLCONV XMVectorGetX(FXMVECTOR V)
{
    return V.vector4_f32[0];
}

// Return the Y component in an FPU register.
inline float XM_CALLCONV XMVectorGetY(FXMVECTOR V)
{
    return V.vector4_f32[1];
}

// Return the Z component in an FPU register.
inline float XM_CALLCONV XMVectorGetZ(FXMVECTOR V)
{
    return V.vector4_f32[2];
}

// Return the W component in an FPU register.
inline float XM_CALLCONV XMVectorGetW(FXMVECTOR V)
{
    return V.vector4_f32[3];
}

// Sets the X component of a vector to a passed floating point value
inline XMVECTOR XM_CALLCONV XMVectorSetX(FXMVECTOR V, float x)
{
    XMVECTORF32 U = { { {
                x,
                V.vector4_f32[1],
                V.vector4_f32[2],
                V.vector4_f32[3]
            }
        }
    };
    return U.v;
}
// Sets the Y component of a vector to a passed floating point value
inline XMVECTOR XM_CALLCONV XMVectorSetY(FXMVECTOR V, float y)
{
    XMVECTORF32 U = { { {
                V.vector4_f32[0],
                y,
                V.vector4_f32[2],
                V.vector4_f32[3]
            }
        }
    };
    return U.v;
}
// Sets the Z component of a vector to a passed floating point value
inline XMVECTOR XM_CALLCONV XMVectorSetZ(FXMVECTOR V, float z)
{
    XMVECTORF32 U = { { {
                V.vector4_f32[0],
                V.vector4_f32[1],
                z,
                V.vector4_f32[3]
            }
        }
    };
    return U.v;
}
// Sets the W component of a vector to a passed floating point value
inline XMVECTOR XM_CALLCONV XMVectorSetW(FXMVECTOR V, float w)
{
    XMVECTORF32 U = { { {
                V.vector4_f32[0],
                V.vector4_f32[1],
                V.vector4_f32[2],
                w
            }
        }
    };
    return U.v;
}
//------------------------------------------------------------------------------

inline bool XM_CALLCONV XMVector4LessOrEqual
(
    FXMVECTOR V1,
    FXMVECTOR V2
)
{
    return (((V1.vector4_f32[0] <= V2.vector4_f32[0]) && (V1.vector4_f32[1] <= V2.vector4_f32[1]) && (V1.vector4_f32[2] <= V2.vector4_f32[2]) && (V1.vector4_f32[3] <= V2.vector4_f32[3])) != 0);
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVectorMin
(
    FXMVECTOR V1,
    FXMVECTOR V2
)
{
    XMVECTORF32 Result = { { {
                (V1.vector4_f32[0] < V2.vector4_f32[0]) ? V1.vector4_f32[0] : V2.vector4_f32[0],
                (V1.vector4_f32[1] < V2.vector4_f32[1]) ? V1.vector4_f32[1] : V2.vector4_f32[1],
                (V1.vector4_f32[2] < V2.vector4_f32[2]) ? V1.vector4_f32[2] : V2.vector4_f32[2],
                (V1.vector4_f32[3] < V2.vector4_f32[3]) ? V1.vector4_f32[3] : V2.vector4_f32[3]
            }
        }
    };
    return Result.v;
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVectorMax
(
    FXMVECTOR V1,
    FXMVECTOR V2
)
{

    XMVECTORF32 Result = { { {
                (V1.vector4_f32[0] > V2.vector4_f32[0]) ? V1.vector4_f32[0] : V2.vector4_f32[0],
                (V1.vector4_f32[1] > V2.vector4_f32[1]) ? V1.vector4_f32[1] : V2.vector4_f32[1],
                (V1.vector4_f32[2] > V2.vector4_f32[2]) ? V1.vector4_f32[2] : V2.vector4_f32[2],
                (V1.vector4_f32[3] > V2.vector4_f32[3]) ? V1.vector4_f32[3] : V2.vector4_f32[3]
            }
        }
    };
    return Result.v;
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVectorClamp
(
    FXMVECTOR V,
    FXMVECTOR Min,
    FXMVECTOR Max
)
{
    assert(XMVector4LessOrEqual(Min, Max));

    XMVECTOR Result;
    Result = XMVectorMax(Min, V);
    Result = XMVectorMin(Max, Result);
    return Result;
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVectorNegate
(
    FXMVECTOR V
)
{
    XMVECTORF32 Result = { { {
                -V.vector4_f32[0],
                -V.vector4_f32[1],
                -V.vector4_f32[2],
                -V.vector4_f32[3]
            }
        }
    };
    return Result.v;
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVectorAdd
(
    FXMVECTOR V1,
    FXMVECTOR V2
)
{
    XMVECTORF32 Result = { { {
                V1.vector4_f32[0] + V2.vector4_f32[0],
                V1.vector4_f32[1] + V2.vector4_f32[1],
                V1.vector4_f32[2] + V2.vector4_f32[2],
                V1.vector4_f32[3] + V2.vector4_f32[3]
            }
        }
    };
    return Result.v;
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVectorSubtract
(
    FXMVECTOR V1,
    FXMVECTOR V2
)
{
    XMVECTORF32 Result = { { {
                V1.vector4_f32[0] - V2.vector4_f32[0],
                V1.vector4_f32[1] - V2.vector4_f32[1],
                V1.vector4_f32[2] - V2.vector4_f32[2],
                V1.vector4_f32[3] - V2.vector4_f32[3]
            }
        }
    };
    return Result.v;
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVectorMultiply
(
    FXMVECTOR V1,
    FXMVECTOR V2
)
{
    XMVECTORF32 Result = { { {
                V1.vector4_f32[0]* V2.vector4_f32[0],
                V1.vector4_f32[1]* V2.vector4_f32[1],
                V1.vector4_f32[2]* V2.vector4_f32[2],
                V1.vector4_f32[3]* V2.vector4_f32[3]
            }
        }
    };
    return Result.v;
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVectorDivide
(
    FXMVECTOR V1,
    FXMVECTOR V2
)
{
    XMVECTORF32 Result = { { {
                V1.vector4_f32[0] / V2.vector4_f32[0],
                V1.vector4_f32[1] / V2.vector4_f32[1],
                V1.vector4_f32[2] / V2.vector4_f32[2],
                V1.vector4_f32[3] / V2.vector4_f32[3]
            }
        }
    };
    return Result.v;
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVectorScale
(
    FXMVECTOR V,
    float    ScaleFactor
)
{
    XMVECTORF32 Result = { { {
                V.vector4_f32[0]* ScaleFactor,
                V.vector4_f32[1]* ScaleFactor,
                V.vector4_f32[2]* ScaleFactor,
                V.vector4_f32[3]* ScaleFactor
            }
        }
    };
    return Result.v;
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVectorSqrt
(
    FXMVECTOR V
)
{
    XMVECTORF32 Result = { { {
                sqrtf(V.vector4_f32[0]),
                sqrtf(V.vector4_f32[1]),
                sqrtf(V.vector4_f32[2]),
                sqrtf(V.vector4_f32[3])
            }
        }
    };
    return Result.v;
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVectorMultiplyAdd
(
    FXMVECTOR V1,
    FXMVECTOR V2,
    FXMVECTOR V3
)
{
    XMVECTORF32 Result = { { {
                V1.vector4_f32[0]* V2.vector4_f32[0] + V3.vector4_f32[0],
                V1.vector4_f32[1]* V2.vector4_f32[1] + V3.vector4_f32[1],
                V1.vector4_f32[2]* V2.vector4_f32[2] + V3.vector4_f32[2],
                V1.vector4_f32[3]* V2.vector4_f32[3] + V3.vector4_f32[3]
            }
        }
    };
    return Result.v;
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVectorACos
(
    FXMVECTOR V
)
{
    // 7-degree minimax approximation

    XMVECTORF32 Result = { { {
                acosf(V.vector4_f32[0]),
                acosf(V.vector4_f32[1]),
                acosf(V.vector4_f32[2]),
                acosf(V.vector4_f32[3])
            }
        }
    };
    return Result.v;
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVectorMergeXY
(
    FXMVECTOR V1,
    FXMVECTOR V2
)
{
    XMVECTORU32 Result = { { {
                V1.vector4_u32[0],
                V2.vector4_u32[0],
                V1.vector4_u32[1],
                V2.vector4_u32[1],
            }
        }
    };
    return Result.v;
}

//------------------------------------------------------------------------------

inline bool XM_CALLCONV XMVector2Less
(
    FXMVECTOR V1,
    FXMVECTOR V2
)
{
    return (((V1.vector4_f32[0] < V2.vector4_f32[0]) && (V1.vector4_f32[1] < V2.vector4_f32[1])) != 0);
}

//------------------------------------------------------------------------------

inline bool XM_CALLCONV XMVector3Less
(
    FXMVECTOR V1,
    FXMVECTOR V2
)
{
    return (((V1.vector4_f32[0] < V2.vector4_f32[0]) && (V1.vector4_f32[1] < V2.vector4_f32[1]) && (V1.vector4_f32[2] < V2.vector4_f32[2])) != 0);
}

//------------------------------------------------------------------------------

inline bool XM_CALLCONV XMVector3Equal
(
    FXMVECTOR V1,
    FXMVECTOR V2
)
{
    return (((V1.vector4_f32[0] == V2.vector4_f32[0]) && (V1.vector4_f32[1] == V2.vector4_f32[1]) && (V1.vector4_f32[2] == V2.vector4_f32[2])) != 0);
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVector3Dot
(
    FXMVECTOR V1,
    FXMVECTOR V2
)
{
    float fValue = V1.vector4_f32[0] * V2.vector4_f32[0] + V1.vector4_f32[1] * V2.vector4_f32[1] + V1.vector4_f32[2] * V2.vector4_f32[2];
    XMVECTORF32 vResult;
    vResult.f[0] =
        vResult.f[1] =
            vResult.f[2] =
                vResult.f[3] = fValue;
    return vResult.v;
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVector2Dot
(
    FXMVECTOR V1,
    FXMVECTOR V2
)
{
    XMVECTORF32 Result;
    Result.f[0] =
        Result.f[1] =
            Result.f[2] =
                Result.f[3] = V1.vector4_f32[0] * V2.vector4_f32[0] + V1.vector4_f32[1] * V2.vector4_f32[1];
    return Result.v;
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVector3Cross
(
    FXMVECTOR V1,
    FXMVECTOR V2
)
{
    // [ V1.y*V2.z - V1.z*V2.y, V1.z*V2.x - V1.x*V2.z, V1.x*V2.y - V1.y*V2.x ]

    XMVECTORF32 vResult = { { {
                (V1.vector4_f32[1] * V2.vector4_f32[2]) - (V1.vector4_f32[2] * V2.vector4_f32[1]),
                (V1.vector4_f32[2] * V2.vector4_f32[0]) - (V1.vector4_f32[0] * V2.vector4_f32[2]),
                (V1.vector4_f32[0] * V2.vector4_f32[1]) - (V1.vector4_f32[1] * V2.vector4_f32[0]),
                0.0f
            }
        }
    };
    return vResult.v;
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVector2LengthSq
(
    FXMVECTOR V
)
{
    return XMVector2Dot(V, V);
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVector2Length
(
    FXMVECTOR V
)
{
    XMVECTOR Result;
    Result = XMVector2LengthSq(V);
    Result = XMVectorSqrt(Result);
    return Result;
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVector3LengthSq
(
    FXMVECTOR V
)
{
    return XMVector3Dot(V, V);
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVector3Length
(
    FXMVECTOR V
)
{
    XMVECTOR Result;

    Result = XMVector3LengthSq(V);
    Result = XMVectorSqrt(Result);

    return Result;
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVector2Normalize
(
    FXMVECTOR V
)
{
    XMVECTOR vResult = XMVector2Length(V);
    float fLength = vResult.vector4_f32[0];

    // Prevent divide by zero
    if (fLength > 0)
    {
        fLength = 1.0f / fLength;
    }

    vResult.vector4_f32[0] = V.vector4_f32[0] * fLength;
    vResult.vector4_f32[1] = V.vector4_f32[1] * fLength;
    vResult.vector4_f32[2] = V.vector4_f32[2] * fLength;
    vResult.vector4_f32[3] = V.vector4_f32[3] * fLength;
    return vResult;
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVector3Normalize
(
    FXMVECTOR V
)
{
    float fLength;
    XMVECTOR vResult;

    vResult = XMVector3Length(V);
    fLength = vResult.vector4_f32[0];

    // Prevent divide by zero
    if (fLength > 0)
    {
        fLength = 1.0f / fLength;
    }

    vResult.vector4_f32[0] = V.vector4_f32[0] * fLength;
    vResult.vector4_f32[1] = V.vector4_f32[1] * fLength;
    vResult.vector4_f32[2] = V.vector4_f32[2] * fLength;
    vResult.vector4_f32[3] = V.vector4_f32[3] * fLength;
    return vResult;
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVector2TransformCoord
(
    FXMVECTOR V,
    FXMMATRIX M
)
{
    XMVECTOR Y = XMVectorSplatY(V);
    XMVECTOR X = XMVectorSplatX(V);

    XMVECTOR Result = XMVectorMultiplyAdd(Y, M.r[1], M.r[3]);
    Result = XMVectorMultiplyAdd(X, M.r[0], Result);

    XMVECTOR W = XMVectorSplatW(Result);
    return XMVectorDivide(Result, W);
}

//------------------------------------------------------------------------------
inline XMVECTOR XM_CALLCONV XMVectorPermute
(
    FXMVECTOR V1,
    FXMVECTOR V2,
    uint32_t PermuteX,
    uint32_t PermuteY,
    uint32_t PermuteZ,
    uint32_t PermuteW
)
{
    assert(PermuteX <= 7 && PermuteY <= 7 && PermuteZ <= 7 && PermuteW <= 7);
    _Analysis_assume_(PermuteX <= 7 && PermuteY <= 7 && PermuteZ <= 7 && PermuteW <= 7);

    const uint32_t* aPtr[2];
    aPtr[0] = reinterpret_cast<const uint32_t*>(&V1);
    aPtr[1] = reinterpret_cast<const uint32_t*>(&V2);

    XMVECTOR Result;
    auto pWork = reinterpret_cast<uint32_t*>(&Result);

    const uint32_t i0 = PermuteX & 3;
    const uint32_t vi0 = PermuteX >> 2;
    pWork[0] = aPtr[vi0][i0];

    const uint32_t i1 = PermuteY & 3;
    const uint32_t vi1 = PermuteY >> 2;
    pWork[1] = aPtr[vi1][i1];

    const uint32_t i2 = PermuteZ & 3;
    const uint32_t vi2 = PermuteZ >> 2;
    pWork[2] = aPtr[vi2][i2];

    const uint32_t i3 = PermuteW & 3;
    const uint32_t vi3 = PermuteW >> 2;
    pWork[3] = aPtr[vi3][i3];

    return Result;
}

//------------------------------------------------------------------------------

inline XMFLOAT2* XM_CALLCONV XMVector2TransformCoordStream
(
    XMFLOAT2*       pOutputStream,
    size_t          OutputStride,
    const XMFLOAT2* pInputStream,
    size_t          InputStride,
    size_t          VectorCount,
    FXMMATRIX       M
)
{
    assert(pOutputStream != nullptr);
    assert(pInputStream != nullptr);

    assert(InputStride >= sizeof(XMFLOAT2));
    _Analysis_assume_(InputStride >= sizeof(XMFLOAT2));

    assert(OutputStride >= sizeof(XMFLOAT2));
    _Analysis_assume_(OutputStride >= sizeof(XMFLOAT2));

    auto pInputVector = reinterpret_cast<const uint8_t*>(pInputStream);
    auto pOutputVector = reinterpret_cast<uint8_t*>(pOutputStream);

    const XMVECTOR row0 = M.r[0];
    const XMVECTOR row1 = M.r[1];
    const XMVECTOR row3 = M.r[3];

    for (size_t i = 0; i < VectorCount; i++)
    {
        XMVECTOR V = XMLoadFloat2(reinterpret_cast<const XMFLOAT2*>(pInputVector));
        XMVECTOR Y = XMVectorSplatY(V);
        XMVECTOR X = XMVectorSplatX(V);

        XMVECTOR Result = XMVectorMultiplyAdd(Y, row1, row3);
        Result = XMVectorMultiplyAdd(X, row0, Result);

        XMVECTOR W = XMVectorSplatW(Result);

        Result = XMVectorDivide(Result, W);

#ifdef _PREFAST_
#pragma prefast(push)
#pragma prefast(disable : 26015, "PREfast noise: Esp:1307" )
#endif

        XMStoreFloat2(reinterpret_cast<XMFLOAT2*>(pOutputVector), Result);

#ifdef _PREFAST_
#pragma prefast(pop)
#endif

        pInputVector += InputStride;
        pOutputVector += OutputStride;
    }

    return pOutputStream;
}

//------------------------------------------------------------------------------

inline XMMATRIX XM_CALLCONV XMLoadFloat4x4
(
    const XMFLOAT4X4* pSource
)
{
    assert(pSource);
    XMMATRIX M;
    M.r[0].vector4_f32[0] = pSource->m[0][0];
    M.r[0].vector4_f32[1] = pSource->m[0][1];
    M.r[0].vector4_f32[2] = pSource->m[0][2];
    M.r[0].vector4_f32[3] = pSource->m[0][3];

    M.r[1].vector4_f32[0] = pSource->m[1][0];
    M.r[1].vector4_f32[1] = pSource->m[1][1];
    M.r[1].vector4_f32[2] = pSource->m[1][2];
    M.r[1].vector4_f32[3] = pSource->m[1][3];

    M.r[2].vector4_f32[0] = pSource->m[2][0];
    M.r[2].vector4_f32[1] = pSource->m[2][1];
    M.r[2].vector4_f32[2] = pSource->m[2][2];
    M.r[2].vector4_f32[3] = pSource->m[2][3];

    M.r[3].vector4_f32[0] = pSource->m[3][0];
    M.r[3].vector4_f32[1] = pSource->m[3][1];
    M.r[3].vector4_f32[2] = pSource->m[3][2];
    M.r[3].vector4_f32[3] = pSource->m[3][3];
    return M;
}

//------------------------------------------------------------------------------
inline void XM_CALLCONV XMStoreFloat4x4
(
    XMFLOAT4X4* pDestination,
    FXMMATRIX M
)
{
    assert(pDestination);

    pDestination->m[0][0] = M.r[0].vector4_f32[0];
    pDestination->m[0][1] = M.r[0].vector4_f32[1];
    pDestination->m[0][2] = M.r[0].vector4_f32[2];
    pDestination->m[0][3] = M.r[0].vector4_f32[3];

    pDestination->m[1][0] = M.r[1].vector4_f32[0];
    pDestination->m[1][1] = M.r[1].vector4_f32[1];
    pDestination->m[1][2] = M.r[1].vector4_f32[2];
    pDestination->m[1][3] = M.r[1].vector4_f32[3];

    pDestination->m[2][0] = M.r[2].vector4_f32[0];
    pDestination->m[2][1] = M.r[2].vector4_f32[1];
    pDestination->m[2][2] = M.r[2].vector4_f32[2];
    pDestination->m[2][3] = M.r[2].vector4_f32[3];

    pDestination->m[3][0] = M.r[3].vector4_f32[0];
    pDestination->m[3][1] = M.r[3].vector4_f32[1];
    pDestination->m[3][2] = M.r[3].vector4_f32[2];
    pDestination->m[3][3] = M.r[3].vector4_f32[3];
}

//------------------------------------------------------------------------------

inline XMMATRIX XM_CALLCONV XMMatrixIdentity()
{
    XMMATRIX M;
    M.r[0] = g_XMIdentityR0.v;
    M.r[1] = g_XMIdentityR1.v;
    M.r[2] = g_XMIdentityR2.v;
    M.r[3] = g_XMIdentityR3.v;
    return M;
}

//------------------------------------------------------------------------------

inline XMMATRIX XM_CALLCONV XMMatrixScaling
(
    float ScaleX,
    float ScaleY,
    float ScaleZ
)
{
    XMMATRIX M;
    M.m[0][0] = ScaleX;
    M.m[0][1] = 0.0f;
    M.m[0][2] = 0.0f;
    M.m[0][3] = 0.0f;

    M.m[1][0] = 0.0f;
    M.m[1][1] = ScaleY;
    M.m[1][2] = 0.0f;
    M.m[1][3] = 0.0f;

    M.m[2][0] = 0.0f;
    M.m[2][1] = 0.0f;
    M.m[2][2] = ScaleZ;
    M.m[2][3] = 0.0f;

    M.m[3][0] = 0.0f;
    M.m[3][1] = 0.0f;
    M.m[3][2] = 0.0f;
    M.m[3][3] = 1.0f;
    return M;
}

//------------------------------------------------------------------------------

inline XMMATRIX XM_CALLCONV XMMatrixTranslation
(
    float OffsetX,
    float OffsetY,
    float OffsetZ
)
{
    XMMATRIX M;
    M.m[0][0] = 1.0f;
    M.m[0][1] = 0.0f;
    M.m[0][2] = 0.0f;
    M.m[0][3] = 0.0f;

    M.m[1][0] = 0.0f;
    M.m[1][1] = 1.0f;
    M.m[1][2] = 0.0f;
    M.m[1][3] = 0.0f;

    M.m[2][0] = 0.0f;
    M.m[2][1] = 0.0f;
    M.m[2][2] = 1.0f;
    M.m[2][3] = 0.0f;

    M.m[3][0] = OffsetX;
    M.m[3][1] = OffsetY;
    M.m[3][2] = OffsetZ;
    M.m[3][3] = 1.0f;
    return M;
}

//------------------------------------------------------------------------------

inline void XMScalarSinCos
(
    float* pSin,
    float* pCos,
    float  Value
)
{
    assert(pSin);
    assert(pCos);

    // Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
    float quotient = XM_1DIV2PI * Value;
    if (Value >= 0.0f)
    {
        quotient = static_cast<float>(static_cast<int>(quotient + 0.5f));
    }
    else
    {
        quotient = static_cast<float>(static_cast<int>(quotient - 0.5f));
    }
    float y = Value - XM_2PI * quotient;

    // Map y to [-pi/2,pi/2] with sin(y) = sin(Value).
    float sign;
    if (y > XM_PIDIV2)
    {
        y = XM_PI - y;
        sign = -1.0f;
    }
    else if (y < -XM_PIDIV2)
    {
        y = -XM_PI - y;
        sign = -1.0f;
    }
    else
    {
        sign = +1.0f;
    }

    float y2 = y * y;

    // 11-degree minimax approximation
    *pSin = (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 + 1.0f) * y;

    // 10-degree minimax approximation
    float p = ((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 + 0.041666638f) * y2 - 0.5f) * y2 + 1.0f;
    *pCos = sign * p;
}

//------------------------------------------------------------------------------

inline XMMATRIX XM_CALLCONV XMMatrixRotationZ
(
    float Angle
)
{
    float    fSinAngle;
    float    fCosAngle;
    XMScalarSinCos(&fSinAngle, &fCosAngle, Angle);

    XMMATRIX M;
    M.m[0][0] = fCosAngle;
    M.m[0][1] = fSinAngle;
    M.m[0][2] = 0.0f;
    M.m[0][3] = 0.0f;

    M.m[1][0] = -fSinAngle;
    M.m[1][1] = fCosAngle;
    M.m[1][2] = 0.0f;
    M.m[1][3] = 0.0f;

    M.m[2][0] = 0.0f;
    M.m[2][1] = 0.0f;
    M.m[2][2] = 1.0f;
    M.m[2][3] = 0.0f;

    M.m[3][0] = 0.0f;
    M.m[3][1] = 0.0f;
    M.m[3][2] = 0.0f;
    M.m[3][3] = 1.0f;
    return M;
}

//------------------------------------------------------------------------------
// Perform a 4x4 matrix multiply by a 4x4 matrix
inline XMMATRIX XM_CALLCONV XMMatrixMultiply
(
    FXMMATRIX M1,
    CXMMATRIX M2
)
{
    XMMATRIX mResult;
    // Cache the invariants in registers
    float x = M1.m[0][0];
    float y = M1.m[0][1];
    float z = M1.m[0][2];
    float w = M1.m[0][3];
    // Perform the operation on the first row
    mResult.m[0][0] = (M2.m[0][0] * x) + (M2.m[1][0] * y) + (M2.m[2][0] * z) + (M2.m[3][0] * w);
    mResult.m[0][1] = (M2.m[0][1] * x) + (M2.m[1][1] * y) + (M2.m[2][1] * z) + (M2.m[3][1] * w);
    mResult.m[0][2] = (M2.m[0][2] * x) + (M2.m[1][2] * y) + (M2.m[2][2] * z) + (M2.m[3][2] * w);
    mResult.m[0][3] = (M2.m[0][3] * x) + (M2.m[1][3] * y) + (M2.m[2][3] * z) + (M2.m[3][3] * w);
    // Repeat for all the other rows
    x = M1.m[1][0];
    y = M1.m[1][1];
    z = M1.m[1][2];
    w = M1.m[1][3];
    mResult.m[1][0] = (M2.m[0][0] * x) + (M2.m[1][0] * y) + (M2.m[2][0] * z) + (M2.m[3][0] * w);
    mResult.m[1][1] = (M2.m[0][1] * x) + (M2.m[1][1] * y) + (M2.m[2][1] * z) + (M2.m[3][1] * w);
    mResult.m[1][2] = (M2.m[0][2] * x) + (M2.m[1][2] * y) + (M2.m[2][2] * z) + (M2.m[3][2] * w);
    mResult.m[1][3] = (M2.m[0][3] * x) + (M2.m[1][3] * y) + (M2.m[2][3] * z) + (M2.m[3][3] * w);
    x = M1.m[2][0];
    y = M1.m[2][1];
    z = M1.m[2][2];
    w = M1.m[2][3];
    mResult.m[2][0] = (M2.m[0][0] * x) + (M2.m[1][0] * y) + (M2.m[2][0] * z) + (M2.m[3][0] * w);
    mResult.m[2][1] = (M2.m[0][1] * x) + (M2.m[1][1] * y) + (M2.m[2][1] * z) + (M2.m[3][1] * w);
    mResult.m[2][2] = (M2.m[0][2] * x) + (M2.m[1][2] * y) + (M2.m[2][2] * z) + (M2.m[3][2] * w);
    mResult.m[2][3] = (M2.m[0][3] * x) + (M2.m[1][3] * y) + (M2.m[2][3] * z) + (M2.m[3][3] * w);
    x = M1.m[3][0];
    y = M1.m[3][1];
    z = M1.m[3][2];
    w = M1.m[3][3];
    mResult.m[3][0] = (M2.m[0][0] * x) + (M2.m[1][0] * y) + (M2.m[2][0] * z) + (M2.m[3][0] * w);
    mResult.m[3][1] = (M2.m[0][1] * x) + (M2.m[1][1] * y) + (M2.m[2][1] * z) + (M2.m[3][1] * w);
    mResult.m[3][2] = (M2.m[0][2] * x) + (M2.m[1][2] * y) + (M2.m[2][2] * z) + (M2.m[3][2] * w);
    mResult.m[3][3] = (M2.m[0][3] * x) + (M2.m[1][3] * y) + (M2.m[2][3] * z) + (M2.m[3][3] * w);
    return mResult;
}

//------------------------------------------------------------------------------

inline XMMATRIX XM_CALLCONV XMMATRIX::operator*(FXMMATRIX M) const
{
    return XMMatrixMultiply(*this, M);
}

/****************************************************************************
 *
 * XMVECTOR operators
 *
 ****************************************************************************/

#ifndef _XM_NO_XMVECTOR_OVERLOADS_

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV operator+ (FXMVECTOR V)
{
    return V;
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV operator- (FXMVECTOR V)
{
    return XMVectorNegate(V);
}

//------------------------------------------------------------------------------

inline XMVECTOR& XM_CALLCONV operator+=
(
    XMVECTOR&       V1,
    FXMVECTOR       V2
)
{
    V1 = XMVectorAdd(V1, V2);
    return V1;
}

//------------------------------------------------------------------------------

inline XMVECTOR& XM_CALLCONV operator-=
(
    XMVECTOR&       V1,
    FXMVECTOR       V2
)
{
    V1 = XMVectorSubtract(V1, V2);
    return V1;
}

//------------------------------------------------------------------------------

inline XMVECTOR& XM_CALLCONV operator*=
(
    XMVECTOR&       V1,
    FXMVECTOR       V2
)
{
    V1 = XMVectorMultiply(V1, V2);
    return V1;
}

//------------------------------------------------------------------------------

inline XMVECTOR& XM_CALLCONV operator/=
(
    XMVECTOR&       V1,
    FXMVECTOR       V2
)
{
    V1 = XMVectorDivide(V1, V2);
    return V1;
}

//------------------------------------------------------------------------------

inline XMVECTOR& operator*=
(
    XMVECTOR&   V,
    const float S
)
{
    V = XMVectorScale(V, S);
    return V;
}

//------------------------------------------------------------------------------

inline XMVECTOR& operator/=
(
    XMVECTOR&   V,
    const float S
)
{
    XMVECTOR vS = XMVectorReplicate(S);
    V = XMVectorDivide(V, vS);
    return V;
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV operator+
(
    FXMVECTOR V1,
    FXMVECTOR V2
)
{
    return XMVectorAdd(V1, V2);
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV operator-
(
    FXMVECTOR V1,
    FXMVECTOR V2
)
{
    return XMVectorSubtract(V1, V2);
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV operator*
(
    FXMVECTOR V1,
    FXMVECTOR V2
)
{
    return XMVectorMultiply(V1, V2);
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV operator/
(
    FXMVECTOR V1,
    FXMVECTOR V2
)
{
    return XMVectorDivide(V1, V2);
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV operator*
(
    FXMVECTOR      V,
    const float    S
)
{
    return XMVectorScale(V, S);
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV operator/
(
    FXMVECTOR      V,
    const float    S
)
{
    XMVECTOR vS = XMVectorReplicate(S);
    return XMVectorDivide(V, vS);
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV operator*
(
    float           S,
    FXMVECTOR       V
)
{
    return XMVectorScale(V, S);
}

#endif /* !_XM_NO_XMVECTOR_OVERLOADS_ */

// General permute template
template<uint32_t PermuteX, uint32_t PermuteY, uint32_t PermuteZ, uint32_t PermuteW>
inline XMVECTOR     XM_CALLCONV     XMVectorPermute(FXMVECTOR V1, FXMVECTOR V2)
{
    static_assert(PermuteX <= 7, "PermuteX template parameter out of range");
    static_assert(PermuteY <= 7, "PermuteY template parameter out of range");
    static_assert(PermuteZ <= 7, "PermuteZ template parameter out of range");
    static_assert(PermuteW <= 7, "PermuteW template parameter out of range");

    return XMVectorPermute(V1, V2, PermuteX, PermuteY, PermuteZ, PermuteW);
}

} /* namespace DirectX */

#define HRESULT_FROM_32BIT(x) HRESULT_FROM_WIN32(x)

#endif //JNT_LINUX_TYPES_H