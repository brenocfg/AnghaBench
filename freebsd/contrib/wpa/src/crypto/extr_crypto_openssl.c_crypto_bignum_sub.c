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
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 scalar_t__ BN_sub (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ TEST_FAIL () ; 

int crypto_bignum_sub(const struct crypto_bignum *a,
		      const struct crypto_bignum *b,
		      struct crypto_bignum *c)
{
	if (TEST_FAIL())
		return -1;
	return BN_sub((BIGNUM *) c, (const BIGNUM *) a, (const BIGNUM *) b) ?
		0 : -1;
}