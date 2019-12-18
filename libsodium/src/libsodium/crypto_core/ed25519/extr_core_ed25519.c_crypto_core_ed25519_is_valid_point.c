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
typedef  int /*<<< orphan*/  ge25519_p3 ;

/* Variables and functions */
 scalar_t__ ge25519_frombytes (int /*<<< orphan*/ *,unsigned char const*) ; 
 scalar_t__ ge25519_has_small_order (unsigned char const*) ; 
 scalar_t__ ge25519_is_canonical (unsigned char const*) ; 
 scalar_t__ ge25519_is_on_curve (int /*<<< orphan*/ *) ; 
 scalar_t__ ge25519_is_on_main_subgroup (int /*<<< orphan*/ *) ; 

int
crypto_core_ed25519_is_valid_point(const unsigned char *p)
{
    ge25519_p3 p_p3;

    if (ge25519_is_canonical(p) == 0 ||
        ge25519_has_small_order(p) != 0 ||
        ge25519_frombytes(&p_p3, p) != 0 ||
        ge25519_is_on_curve(&p_p3) == 0 ||
        ge25519_is_on_main_subgroup(&p_p3) == 0) {
        return 0;
    }
    return 1;
}