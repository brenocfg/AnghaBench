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
 int crypto_scalarmult_curve25519_base (unsigned char*,unsigned char const*) ; 

int
crypto_scalarmult_base(unsigned char *q, const unsigned char *n)
{
    return crypto_scalarmult_curve25519_base(q, n);
}