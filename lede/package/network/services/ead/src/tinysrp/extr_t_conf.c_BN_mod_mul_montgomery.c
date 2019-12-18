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
typedef  int /*<<< orphan*/  BN_MONT_CTX ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_from_montgomery (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_sqr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bn_check_top (int /*<<< orphan*/ *) ; 

int BN_mod_mul_montgomery(BIGNUM *r, BIGNUM *a, BIGNUM *b,
			  BN_MONT_CTX *mont, BN_CTX *ctx)
	{
	BIGNUM *tmp,*tmp2;
	int ret=0;

	BN_CTX_start(ctx);
	tmp = BN_CTX_get(ctx);
	tmp2 = BN_CTX_get(ctx);
	if (tmp == NULL || tmp2 == NULL) goto err;

	bn_check_top(tmp);
	bn_check_top(tmp2);

	if (a == b)
		{
		if (!BN_sqr(tmp,a,ctx)) goto err;
		}
	else
		{
		if (!BN_mul(tmp,a,b,ctx)) goto err;
		}
	/* reduce from aRR to aR */
	if (!BN_from_montgomery(r,tmp,mont,ctx)) goto err;
	ret=1;
err:
	BN_CTX_end(ctx);
	return(ret);
	}