#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * field_data1; int /*<<< orphan*/  field; } ;
typedef  TYPE_1__ EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_secure_new () ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_exp_mont (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_set_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_F_EC_GFP_MONT_FIELD_INV ; 
 int /*<<< orphan*/  EC_R_CANNOT_INVERT ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ec_GFp_mont_field_inv(const EC_GROUP *group, BIGNUM *r, const BIGNUM *a,
                            BN_CTX *ctx)
{
    BIGNUM *e = NULL;
    BN_CTX *new_ctx = NULL;
    int ret = 0;

    if (group->field_data1 == NULL)
        return 0;

    if (ctx == NULL && (ctx = new_ctx = BN_CTX_secure_new()) == NULL)
        return 0;

    BN_CTX_start(ctx);
    if ((e = BN_CTX_get(ctx)) == NULL)
        goto err;

    /* Inverse in constant time with Fermats Little Theorem */
    if (!BN_set_word(e, 2))
        goto err;
    if (!BN_sub(e, group->field, e))
        goto err;
    /*-
     * Exponent e is public.
     * No need for scatter-gather or BN_FLG_CONSTTIME.
     */
    if (!BN_mod_exp_mont(r, a, e, group->field, ctx, group->field_data1))
        goto err;

    /* throw an error on zero */
    if (BN_is_zero(r)) {
        ECerr(EC_F_EC_GFP_MONT_FIELD_INV, EC_R_CANNOT_INVERT);
        goto err;
    }

    ret = 1;

  err:
    BN_CTX_end(ctx);
    BN_CTX_free(new_ctx);
    return ret;
}