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
 scalar_t__ ristretto255_frombytes (int /*<<< orphan*/ *,unsigned char const*) ; 

int
crypto_core_ristretto255_is_valid_point(const unsigned char *p)
{
    ge25519_p3 p_p3;

    if (ristretto255_frombytes(&p_p3, p) != 0) {
        return 0;
    }
    return 1;
}