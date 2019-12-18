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
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_FLG_CONSTTIME ; 
 int BN_div (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_FAIL () ; 

int crypto_bignum_div(const struct crypto_bignum *a,
		      const struct crypto_bignum *b,
		      struct crypto_bignum *c)
{
	int res;

	BN_CTX *bnctx;

	if (TEST_FAIL())
		return -1;

	bnctx = BN_CTX_new();
	if (bnctx == NULL)
		return -1;
#ifndef OPENSSL_IS_BORINGSSL
	BN_set_flags((BIGNUM *) a, BN_FLG_CONSTTIME);
#endif /* OPENSSL_IS_BORINGSSL */
	res = BN_div((BIGNUM *) c, NULL, (const BIGNUM *) a,
		     (const BIGNUM *) b, bnctx);
	BN_CTX_free(bnctx);

	return res ? 0 : -1;
}