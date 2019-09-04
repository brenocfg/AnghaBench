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
 int /*<<< orphan*/  crypto_scalarmult_curve25519_ref10_implementation ; 
 int /*<<< orphan*/ * implementation ; 

int
_crypto_scalarmult_curve25519_pick_best_implementation(void)
{
    implementation = &crypto_scalarmult_curve25519_ref10_implementation;

#ifdef HAVE_AVX_ASM
    if (sodium_runtime_has_avx()) {
        implementation = &crypto_scalarmult_curve25519_sandy2x_implementation;
    }
#endif
    return 0;
}