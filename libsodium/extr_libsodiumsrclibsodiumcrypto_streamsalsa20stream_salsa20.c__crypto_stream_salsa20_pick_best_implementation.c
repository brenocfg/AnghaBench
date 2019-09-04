#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  crypto_stream_salsa20_ref_implementation ; 
 int /*<<< orphan*/ * implementation ; 

int
_crypto_stream_salsa20_pick_best_implementation(void)
{
#ifdef HAVE_AMD64_ASM
    implementation = &crypto_stream_salsa20_xmm6_implementation;
#else
    implementation = &crypto_stream_salsa20_ref_implementation;
#endif

#if defined(HAVE_AVX2INTRIN_H) && defined(HAVE_EMMINTRIN_H) && \
    defined(HAVE_TMMINTRIN_H) && defined(HAVE_SMMINTRIN_H)
    if (sodium_runtime_has_avx2()) {
        implementation = &crypto_stream_salsa20_xmm6int_avx2_implementation;
        return 0;
    }
#endif
#if !defined(HAVE_AMD64_ASM) && defined(HAVE_EMMINTRIN_H)
    if (sodium_runtime_has_sse2()) {
        implementation = &crypto_stream_salsa20_xmm6int_sse2_implementation;
        return 0;
    }
#endif
    return 0; /* LCOV_EXCL_LINE */
}