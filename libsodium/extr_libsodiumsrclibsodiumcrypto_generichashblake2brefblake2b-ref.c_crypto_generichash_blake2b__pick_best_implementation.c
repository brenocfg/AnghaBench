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
 int /*<<< orphan*/  blake2b_compress ; 
 int /*<<< orphan*/  blake2b_compress_ref ; 

int
blake2b_pick_best_implementation(void)
{
/* LCOV_EXCL_START */
#if defined(HAVE_AVX2INTRIN_H) && defined(HAVE_TMMINTRIN_H) && \
    defined(HAVE_SMMINTRIN_H)
    if (sodium_runtime_has_avx2()) {
        blake2b_compress = blake2b_compress_avx2;
        return 0;
    }
#endif
#if defined(HAVE_EMMINTRIN_H) && defined(HAVE_TMMINTRIN_H) && \
    defined(HAVE_SMMINTRIN_H)
    if (sodium_runtime_has_sse41()) {
        blake2b_compress = blake2b_compress_sse41;
        return 0;
    }
#endif
#if defined(HAVE_EMMINTRIN_H) && defined(HAVE_TMMINTRIN_H)
    if (sodium_runtime_has_ssse3()) {
        blake2b_compress = blake2b_compress_ssse3;
        return 0;
    }
#endif
    blake2b_compress = blake2b_compress_ref;

    return 0;
    /* LCOV_EXCL_STOP */
}