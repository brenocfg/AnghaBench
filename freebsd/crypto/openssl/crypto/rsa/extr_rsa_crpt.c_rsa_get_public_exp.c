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
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_mod_inverse (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_sub (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_value_one () ; 

__attribute__((used)) static BIGNUM *rsa_get_public_exp(const BIGNUM *d, const BIGNUM *p,
                                  const BIGNUM *q, BN_CTX *ctx)
{
    BIGNUM *ret = NULL, *r0, *r1, *r2;

    if (d == NULL || p == NULL || q == NULL)
        return NULL;

    BN_CTX_start(ctx);
    r0 = BN_CTX_get(ctx);
    r1 = BN_CTX_get(ctx);
    r2 = BN_CTX_get(ctx);
    if (r2 == NULL)
        goto err;

    if (!BN_sub(r1, p, BN_value_one()))
        goto err;
    if (!BN_sub(r2, q, BN_value_one()))
        goto err;
    if (!BN_mul(r0, r1, r2, ctx))
        goto err;

    ret = BN_mod_inverse(NULL, d, r0, ctx);
 err:
    BN_CTX_end(ctx);
    return ret;
}