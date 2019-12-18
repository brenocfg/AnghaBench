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
 int /*<<< orphan*/  crypto_verify_16_BYTES ; 
 int crypto_verify_n (unsigned char const*,unsigned char const*,int /*<<< orphan*/ ) ; 

int
crypto_verify_16(const unsigned char *x, const unsigned char *y)
{
    return crypto_verify_n(x, y, crypto_verify_16_BYTES);
}