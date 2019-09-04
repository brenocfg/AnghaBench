#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint32_t ;
struct TYPE_3__ {scalar_t__ has_rdrand; scalar_t__ has_aesni; scalar_t__ has_pclmul; scalar_t__ has_avx512f; scalar_t__ has_avx2; scalar_t__ has_avx; scalar_t__ has_sse41; scalar_t__ has_ssse3; scalar_t__ has_sse3; scalar_t__ has_sse2; } ;
typedef  TYPE_1__ CPUFeatures ;

/* Variables and functions */
 int /*<<< orphan*/  _cpuid (unsigned int*,int) ; 

__attribute__((used)) static int
_sodium_runtime_intel_cpu_features(CPUFeatures * const cpu_features)
{
    unsigned int cpu_info[4];
    unsigned int id;
    uint32_t     xcr0 = 0U;

    _cpuid(cpu_info, 0x0);
    if ((id = cpu_info[0]) == 0U) {
        return -1; /* LCOV_EXCL_LINE */
    }
    _cpuid(cpu_info, 0x00000001);
#ifdef HAVE_EMMINTRIN_H
    cpu_features->has_sse2 = ((cpu_info[3] & CPUID_EDX_SSE2) != 0x0);
#else
    cpu_features->has_sse2   = 0;
#endif

#ifdef HAVE_PMMINTRIN_H
    cpu_features->has_sse3 = ((cpu_info[2] & CPUID_ECX_SSE3) != 0x0);
#else
    cpu_features->has_sse3   = 0;
#endif

#ifdef HAVE_TMMINTRIN_H
    cpu_features->has_ssse3 = ((cpu_info[2] & CPUID_ECX_SSSE3) != 0x0);
#else
    cpu_features->has_ssse3  = 0;
#endif

#ifdef HAVE_SMMINTRIN_H
    cpu_features->has_sse41 = ((cpu_info[2] & CPUID_ECX_SSE41) != 0x0);
#else
    cpu_features->has_sse41  = 0;
#endif

    cpu_features->has_avx = 0;

    (void) xcr0;
#ifdef HAVE_AVXINTRIN_H
    if ((cpu_info[2] & (CPUID_ECX_AVX | CPUID_ECX_XSAVE | CPUID_ECX_OSXSAVE)) ==
        (CPUID_ECX_AVX | CPUID_ECX_XSAVE | CPUID_ECX_OSXSAVE)) {
        xcr0 = 0U;
# if defined(HAVE__XGETBV) || \
        (defined(_MSC_VER) && defined(_XCR_XFEATURE_ENABLED_MASK) && _MSC_FULL_VER >= 160040219)
        xcr0 = (uint32_t) _xgetbv(0);
# elif defined(_MSC_VER) && defined(_M_IX86)
        /*
         * Visual Studio documentation states that eax/ecx/edx don't need to
         * be preserved in inline assembly code. But that doesn't seem to
         * always hold true on Visual Studio 2010.
         */
        __asm {
            push eax
            push ecx
            push edx
            xor ecx, ecx
            _asm _emit 0x0f _asm _emit 0x01 _asm _emit 0xd0
            mov xcr0, eax
            pop edx
            pop ecx
            pop eax
        }
# elif defined(HAVE_AVX_ASM)
        __asm__ __volatile__(".byte 0x0f, 0x01, 0xd0" /* XGETBV */
                             : "=a"(xcr0)
                             : "c"((uint32_t) 0U)
                             : "%edx");
# endif
        if ((xcr0 & (XCR0_SSE | XCR0_AVX)) == (XCR0_SSE | XCR0_AVX)) {
            cpu_features->has_avx = 1;
        }
    }
#endif

    cpu_features->has_avx2 = 0;
#ifdef HAVE_AVX2INTRIN_H
    if (cpu_features->has_avx) {
        unsigned int cpu_info7[4];

        _cpuid(cpu_info7, 0x00000007);
        cpu_features->has_avx2 = ((cpu_info7[1] & CPUID_EBX_AVX2) != 0x0);
    }
#endif

    cpu_features->has_avx512f = 0;
#ifdef HAVE_AVX512FINTRIN_H
    if (cpu_features->has_avx2) {
        unsigned int cpu_info7[4];

        _cpuid(cpu_info7, 0x00000007);
        /* LCOV_EXCL_START */
        if ((cpu_info7[1] & CPUID_EBX_AVX512F) == CPUID_EBX_AVX512F &&
            (xcr0 & (XCR0_OPMASK | XCR0_ZMM_HI256 | XCR0_HI16_ZMM))
            == (XCR0_OPMASK | XCR0_ZMM_HI256 | XCR0_HI16_ZMM)) {
            cpu_features->has_avx512f = 1;
        }
        /* LCOV_EXCL_STOP */
    }
#endif

#ifdef HAVE_WMMINTRIN_H
    cpu_features->has_pclmul = ((cpu_info[2] & CPUID_ECX_PCLMUL) != 0x0);
    cpu_features->has_aesni  = ((cpu_info[2] & CPUID_ECX_AESNI) != 0x0);
#else
    cpu_features->has_pclmul = 0;
    cpu_features->has_aesni  = 0;
#endif

#ifdef HAVE_RDRAND
    cpu_features->has_rdrand = ((cpu_info[2] & CPUID_ECX_RDRAND) != 0x0);
#else
    cpu_features->has_rdrand = 0;
#endif

    return 0;
}