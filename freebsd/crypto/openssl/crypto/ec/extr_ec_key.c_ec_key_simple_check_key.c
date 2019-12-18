#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * order; } ;
struct TYPE_8__ {int /*<<< orphan*/ * pub_key; TYPE_3__* group; int /*<<< orphan*/ * priv_key; } ;
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  TYPE_1__ EC_KEY ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 scalar_t__ BN_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_F_EC_KEY_SIMPLE_CHECK_KEY ; 
 scalar_t__ EC_POINT_cmp (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_free (int /*<<< orphan*/ *) ; 
 scalar_t__ EC_POINT_is_at_infinity (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ EC_POINT_is_on_curve (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_mul (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_POINT_new (TYPE_3__*) ; 
 int /*<<< orphan*/  EC_R_INVALID_GROUP_ORDER ; 
 int /*<<< orphan*/  EC_R_INVALID_PRIVATE_KEY ; 
 int /*<<< orphan*/  EC_R_POINT_AT_INFINITY ; 
 int /*<<< orphan*/  EC_R_POINT_IS_NOT_ON_CURVE ; 
 int /*<<< orphan*/  EC_R_WRONG_ORDER ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_EC_LIB ; 
 int /*<<< orphan*/  ERR_R_PASSED_NULL_PARAMETER ; 

int ec_key_simple_check_key(const EC_KEY *eckey)
{
    int ok = 0;
    BN_CTX *ctx = NULL;
    const BIGNUM *order = NULL;
    EC_POINT *point = NULL;

    if (eckey == NULL || eckey->group == NULL || eckey->pub_key == NULL) {
        ECerr(EC_F_EC_KEY_SIMPLE_CHECK_KEY, ERR_R_PASSED_NULL_PARAMETER);
        return 0;
    }

    if (EC_POINT_is_at_infinity(eckey->group, eckey->pub_key)) {
        ECerr(EC_F_EC_KEY_SIMPLE_CHECK_KEY, EC_R_POINT_AT_INFINITY);
        goto err;
    }

    if ((ctx = BN_CTX_new()) == NULL)
        goto err;
    if ((point = EC_POINT_new(eckey->group)) == NULL)
        goto err;

    /* testing whether the pub_key is on the elliptic curve */
    if (EC_POINT_is_on_curve(eckey->group, eckey->pub_key, ctx) <= 0) {
        ECerr(EC_F_EC_KEY_SIMPLE_CHECK_KEY, EC_R_POINT_IS_NOT_ON_CURVE);
        goto err;
    }
    /* testing whether pub_key * order is the point at infinity */
    order = eckey->group->order;
    if (BN_is_zero(order)) {
        ECerr(EC_F_EC_KEY_SIMPLE_CHECK_KEY, EC_R_INVALID_GROUP_ORDER);
        goto err;
    }
    if (!EC_POINT_mul(eckey->group, point, NULL, eckey->pub_key, order, ctx)) {
        ECerr(EC_F_EC_KEY_SIMPLE_CHECK_KEY, ERR_R_EC_LIB);
        goto err;
    }
    if (!EC_POINT_is_at_infinity(eckey->group, point)) {
        ECerr(EC_F_EC_KEY_SIMPLE_CHECK_KEY, EC_R_WRONG_ORDER);
        goto err;
    }
    /*
     * in case the priv_key is present : check if generator * priv_key ==
     * pub_key
     */
    if (eckey->priv_key != NULL) {
        if (BN_cmp(eckey->priv_key, order) >= 0) {
            ECerr(EC_F_EC_KEY_SIMPLE_CHECK_KEY, EC_R_WRONG_ORDER);
            goto err;
        }
        if (!EC_POINT_mul(eckey->group, point, eckey->priv_key,
                          NULL, NULL, ctx)) {
            ECerr(EC_F_EC_KEY_SIMPLE_CHECK_KEY, ERR_R_EC_LIB);
            goto err;
        }
        if (EC_POINT_cmp(eckey->group, point, eckey->pub_key, ctx) != 0) {
            ECerr(EC_F_EC_KEY_SIMPLE_CHECK_KEY, EC_R_INVALID_PRIVATE_KEY);
            goto err;
        }
    }
    ok = 1;
 err:
    BN_CTX_free(ctx);
    EC_POINT_free(point);
    return ok;
}