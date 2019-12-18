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
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_F_BN_MOD_INVERSE ; 
 int /*<<< orphan*/  BN_R_NO_INVERSE ; 
 int /*<<< orphan*/  BNerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * int_bn_mod_inverse (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int*) ; 

BIGNUM *BN_mod_inverse(BIGNUM *in,
                       const BIGNUM *a, const BIGNUM *n, BN_CTX *ctx)
{
    BIGNUM *rv;
    int noinv;
    rv = int_bn_mod_inverse(in, a, n, ctx, &noinv);
    if (noinv)
        BNerr(BN_F_BN_MOD_INVERSE, BN_R_NO_INVERSE);
    return rv;
}