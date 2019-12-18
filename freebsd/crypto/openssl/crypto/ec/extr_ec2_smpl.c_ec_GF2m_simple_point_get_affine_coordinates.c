#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  Y; int /*<<< orphan*/  X; int /*<<< orphan*/  Z; } ;
typedef  TYPE_1__ EC_POINT ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 scalar_t__ BN_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_set_negative (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_value_one () ; 
 int /*<<< orphan*/  EC_F_EC_GF2M_SIMPLE_POINT_GET_AFFINE_COORDINATES ; 
 scalar_t__ EC_POINT_is_at_infinity (int /*<<< orphan*/  const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  EC_R_POINT_AT_INFINITY ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED ; 

int ec_GF2m_simple_point_get_affine_coordinates(const EC_GROUP *group,
                                                const EC_POINT *point,
                                                BIGNUM *x, BIGNUM *y,
                                                BN_CTX *ctx)
{
    int ret = 0;

    if (EC_POINT_is_at_infinity(group, point)) {
        ECerr(EC_F_EC_GF2M_SIMPLE_POINT_GET_AFFINE_COORDINATES,
              EC_R_POINT_AT_INFINITY);
        return 0;
    }

    if (BN_cmp(point->Z, BN_value_one())) {
        ECerr(EC_F_EC_GF2M_SIMPLE_POINT_GET_AFFINE_COORDINATES,
              ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED);
        return 0;
    }
    if (x != NULL) {
        if (!BN_copy(x, point->X))
            goto err;
        BN_set_negative(x, 0);
    }
    if (y != NULL) {
        if (!BN_copy(y, point->Y))
            goto err;
        BN_set_negative(y, 0);
    }
    ret = 1;

 err:
    return ret;
}