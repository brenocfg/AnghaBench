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
 int crypto_core_ed25519_scalar_invert (unsigned char*,unsigned char const*) ; 

int
crypto_core_ristretto255_scalar_invert(unsigned char *recip,
                                       const unsigned char *s)
{
    return crypto_core_ed25519_scalar_invert(recip, s);
}