#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int top; int /*<<< orphan*/ * d; } ;
typedef  int /*<<< orphan*/  BN_ULONG ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  TYPE_1__ const BIGNUM ;

/* Variables and functions */
 scalar_t__ BN_is_odd (TYPE_1__ const*) ; 
 int BN_mod_exp_mont (TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int BN_mod_exp_mont_word (TYPE_1__ const*,int /*<<< orphan*/ ,TYPE_1__ const*,TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int BN_mod_exp_recp (TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int BN_mod_exp_simple (TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bn_check_top (TYPE_1__ const*) ; 

int BN_mod_exp(BIGNUM *r, BIGNUM *a, const BIGNUM *p, const BIGNUM *m,
	       BN_CTX *ctx)
	{
	int ret;

	bn_check_top(a);
	bn_check_top(p);
	bn_check_top(m);

#ifdef MONT_MUL_MOD
	/* I have finally been able to take out this pre-condition of
	 * the top bit being set.  It was caused by an error in BN_div
	 * with negatives.  There was also another problem when for a^b%m
	 * a >= m.  eay 07-May-97 */
/*      if ((m->d[m->top-1]&BN_TBIT) && BN_is_odd(m)) */

	if (BN_is_odd(m))
		{
		if (a->top == 1)
			{
			BN_ULONG A = a->d[0];
			ret=BN_mod_exp_mont_word(r,A,p,m,ctx,NULL);
			}
		else
			ret=BN_mod_exp_mont(r,a,p,m,ctx,NULL);
		}
	else
#endif
#ifdef RECP_MUL_MOD
		{ ret=BN_mod_exp_recp(r,a,p,m,ctx); }
#else
		{ ret=BN_mod_exp_simple(r,a,p,m,ctx); }
#endif

	return(ret);
	}