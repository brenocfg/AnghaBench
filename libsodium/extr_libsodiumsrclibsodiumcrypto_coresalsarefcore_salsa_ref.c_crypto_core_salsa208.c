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
 int /*<<< orphan*/  crypto_core_salsa (unsigned char*,unsigned char const*,unsigned char const*,unsigned char const*,int) ; 

int
crypto_core_salsa208(unsigned char *out, const unsigned char *in,
                     const unsigned char *k, const unsigned char *c)
{
    crypto_core_salsa(out, in, k, c, 8);
    return 0;
}