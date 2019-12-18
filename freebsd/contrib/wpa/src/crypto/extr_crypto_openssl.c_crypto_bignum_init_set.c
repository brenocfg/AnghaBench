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
typedef  int /*<<< orphan*/  u8 ;
struct crypto_bignum {int dummy; } ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/ * BN_bin2bn (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ TEST_FAIL () ; 

struct crypto_bignum * crypto_bignum_init_set(const u8 *buf, size_t len)
{
	BIGNUM *bn;

	if (TEST_FAIL())
		return NULL;

	bn = BN_bin2bn(buf, len, NULL);
	return (struct crypto_bignum *) bn;
}