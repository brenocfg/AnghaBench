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
 int /*<<< orphan*/  crypto_onetimeauth_poly1305_donna_implementation ; 
 int /*<<< orphan*/ * implementation ; 

int
_crypto_onetimeauth_poly1305_pick_best_implementation(void)
{
    implementation = &crypto_onetimeauth_poly1305_donna_implementation;
#if defined(HAVE_TI_MODE) && defined(HAVE_EMMINTRIN_H)
    if (sodium_runtime_has_sse2()) {
        implementation = &crypto_onetimeauth_poly1305_sse2_implementation;
    }
#endif
    return 0;
}