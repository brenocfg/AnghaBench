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
struct crypto_bignum {int dummy; } ;

/* Variables and functions */
 scalar_t__ BN_new () ; 
 scalar_t__ TEST_FAIL () ; 

struct crypto_bignum * crypto_bignum_init(void)
{
	if (TEST_FAIL())
		return NULL;
	return (struct crypto_bignum *) BN_new();
}