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
typedef  int u_int ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_one (int /*<<< orphan*/ *) ; 
 int BN_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_sub (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  bn_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bn_checkp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
bsqrt_stop(const BIGNUM *x, const BIGNUM *y, u_int *onecount)
{
	BIGNUM *r;
	bool ret;

	r = BN_new();
	bn_checkp(r);
	bn_check(BN_sub(r, x, y));
	if (BN_is_one(r))
		(*onecount)++;
	ret = BN_is_zero(r);
	BN_free(r);
	return (ret || *onecount > 1);
}