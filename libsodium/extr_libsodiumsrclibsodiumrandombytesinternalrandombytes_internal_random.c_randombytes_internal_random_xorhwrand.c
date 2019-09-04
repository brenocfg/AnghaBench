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

__attribute__((used)) static void
randombytes_internal_random_xorhwrand(void)
{
/* LCOV_EXCL_START */
#ifdef HAVE_RDRAND
    unsigned int r;

    if (global.rdrand_available == 0) {
        return;
    }
    (void) _rdrand32_step(&r);
    * (uint32_t *) (void *)
        &stream.key[crypto_stream_chacha20_KEYBYTES - 4] ^= (uint32_t) r;
#endif
/* LCOV_EXCL_STOP */
}