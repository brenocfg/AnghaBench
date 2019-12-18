#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* meth; int /*<<< orphan*/  poly; int /*<<< orphan*/ * a; int /*<<< orphan*/  b; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* field_mul ) (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* field_div ) (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* field_sqr ) (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  TYPE_2__ EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_GF2m_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_GF2m_mod_arr (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_GF2m_mod_solve_quad_arr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_GF2m_mod_sqrt_arr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_R_NO_SOLUTION ; 
 scalar_t__ BN_is_odd (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_F_EC_GF2M_SIMPLE_SET_COMPRESSED_COORDINATES ; 
 int /*<<< orphan*/  EC_POINT_set_affine_coordinates (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_R_INVALID_COMPRESSED_POINT ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ERR_GET_LIB (unsigned long) ; 
 scalar_t__ ERR_GET_REASON (unsigned long) ; 
 scalar_t__ ERR_LIB_BN ; 
 int /*<<< orphan*/  ERR_R_BN_LIB ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 unsigned long ERR_peek_last_error () ; 
 int /*<<< orphan*/  stub1 (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int ec_GF2m_simple_set_compressed_coordinates(const EC_GROUP *group,
                                              EC_POINT *point,
                                              const BIGNUM *x_, int y_bit,
                                              BN_CTX *ctx)
{
    BN_CTX *new_ctx = NULL;
    BIGNUM *tmp, *x, *y, *z;
    int ret = 0, z0;

    /* clear error queue */
    ERR_clear_error();

    if (ctx == NULL) {
        ctx = new_ctx = BN_CTX_new();
        if (ctx == NULL)
            return 0;
    }

    y_bit = (y_bit != 0) ? 1 : 0;

    BN_CTX_start(ctx);
    tmp = BN_CTX_get(ctx);
    x = BN_CTX_get(ctx);
    y = BN_CTX_get(ctx);
    z = BN_CTX_get(ctx);
    if (z == NULL)
        goto err;

    if (!BN_GF2m_mod_arr(x, x_, group->poly))
        goto err;
    if (BN_is_zero(x)) {
        if (!BN_GF2m_mod_sqrt_arr(y, group->b, group->poly, ctx))
            goto err;
    } else {
        if (!group->meth->field_sqr(group, tmp, x, ctx))
            goto err;
        if (!group->meth->field_div(group, tmp, group->b, tmp, ctx))
            goto err;
        if (!BN_GF2m_add(tmp, group->a, tmp))
            goto err;
        if (!BN_GF2m_add(tmp, x, tmp))
            goto err;
        if (!BN_GF2m_mod_solve_quad_arr(z, tmp, group->poly, ctx)) {
            unsigned long err = ERR_peek_last_error();

            if (ERR_GET_LIB(err) == ERR_LIB_BN
                && ERR_GET_REASON(err) == BN_R_NO_SOLUTION) {
                ERR_clear_error();
                ECerr(EC_F_EC_GF2M_SIMPLE_SET_COMPRESSED_COORDINATES,
                      EC_R_INVALID_COMPRESSED_POINT);
            } else
                ECerr(EC_F_EC_GF2M_SIMPLE_SET_COMPRESSED_COORDINATES,
                      ERR_R_BN_LIB);
            goto err;
        }
        z0 = (BN_is_odd(z)) ? 1 : 0;
        if (!group->meth->field_mul(group, y, x, z, ctx))
            goto err;
        if (z0 != y_bit) {
            if (!BN_GF2m_add(y, y, x))
                goto err;
        }
    }

    if (!EC_POINT_set_affine_coordinates(group, point, x, y, ctx))
        goto err;

    ret = 1;

 err:
    BN_CTX_end(ctx);
    BN_CTX_free(new_ctx);
    return ret;
}