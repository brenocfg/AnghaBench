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
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_is_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_exp_mont_consttime (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_rshift1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_sub (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_value_one () ; 
 scalar_t__ TEST_FAIL () ; 
 unsigned int const_time_eq (int /*<<< orphan*/ ,int) ; 
 int const_time_select_int (unsigned int,int,int) ; 

int crypto_bignum_legendre(const struct crypto_bignum *a,
			   const struct crypto_bignum *p)
{
	BN_CTX *bnctx;
	BIGNUM *exp = NULL, *tmp = NULL;
	int res = -2;
	unsigned int mask;

	if (TEST_FAIL())
		return -2;

	bnctx = BN_CTX_new();
	if (bnctx == NULL)
		return -2;

	exp = BN_new();
	tmp = BN_new();
	if (!exp || !tmp ||
	    /* exp = (p-1) / 2 */
	    !BN_sub(exp, (const BIGNUM *) p, BN_value_one()) ||
	    !BN_rshift1(exp, exp) ||
	    !BN_mod_exp_mont_consttime(tmp, (const BIGNUM *) a, exp,
				       (const BIGNUM *) p, bnctx, NULL))
		goto fail;

	/* Return 1 if tmp == 1, 0 if tmp == 0, or -1 otherwise. Need to use
	 * constant time selection to avoid branches here. */
	res = -1;
	mask = const_time_eq(BN_is_word(tmp, 1), 1);
	res = const_time_select_int(mask, 1, res);
	mask = const_time_eq(BN_is_zero(tmp), 1);
	res = const_time_select_int(mask, 0, res);

fail:
	BN_clear_free(tmp);
	BN_clear_free(exp);
	BN_CTX_free(bnctx);
	return res;
}