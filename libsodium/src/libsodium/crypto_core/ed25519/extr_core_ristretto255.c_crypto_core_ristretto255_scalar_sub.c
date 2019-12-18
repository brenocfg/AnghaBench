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
 int /*<<< orphan*/  crypto_core_ed25519_scalar_sub (unsigned char*,unsigned char const*,unsigned char const*) ; 

void
crypto_core_ristretto255_scalar_sub(unsigned char *z, const unsigned char *x,
                                    const unsigned char *y)
{
    crypto_core_ed25519_scalar_sub(z, x, y);
}