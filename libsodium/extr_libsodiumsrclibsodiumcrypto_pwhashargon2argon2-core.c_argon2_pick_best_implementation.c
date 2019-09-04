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
 int /*<<< orphan*/  fill_segment ; 
 int /*<<< orphan*/  fill_segment_ref ; 

int
argon2_pick_best_implementation(void)
{
/* LCOV_EXCL_START */
#if defined(HAVE_AVX512FINTRIN_H) && defined(HAVE_AVX2INTRIN_H) && \
    defined(HAVE_TMMINTRIN_H) && defined(HAVE_SMMINTRIN_H)
    if (sodium_runtime_has_avx512f()) {
        fill_segment = fill_segment_avx512f;
        return 0;
    }
#endif
#if defined(HAVE_AVX2INTRIN_H) && defined(HAVE_TMMINTRIN_H) && \
    defined(HAVE_SMMINTRIN_H)
    if (sodium_runtime_has_avx2()) {
        fill_segment = fill_segment_avx2;
        return 0;
    }
#endif
#if defined(HAVE_EMMINTRIN_H) && defined(HAVE_TMMINTRIN_H)
    if (sodium_runtime_has_ssse3()) {
        fill_segment = fill_segment_ssse3;
        return 0;
    }
#endif
    fill_segment = fill_segment_ref;

    return 0;
    /* LCOV_EXCL_STOP */
}