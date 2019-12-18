#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* meth; } ;
struct TYPE_7__ {int (* point_get_affine_coordinates ) (TYPE_2__ const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  TYPE_2__ EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  EC_F_EC_POINT_GET_AFFINE_COORDINATES ; 
 scalar_t__ EC_POINT_is_at_infinity (TYPE_2__ const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_R_INCOMPATIBLE_OBJECTS ; 
 int /*<<< orphan*/  EC_R_POINT_AT_INFINITY ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED ; 
 int /*<<< orphan*/  ec_point_is_compat (int /*<<< orphan*/  const*,TYPE_2__ const*) ; 
 int stub1 (TYPE_2__ const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int EC_POINT_get_affine_coordinates(const EC_GROUP *group,
                                    const EC_POINT *point, BIGNUM *x, BIGNUM *y,
                                    BN_CTX *ctx)
{
    if (group->meth->point_get_affine_coordinates == NULL) {
        ECerr(EC_F_EC_POINT_GET_AFFINE_COORDINATES,
              ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED);
        return 0;
    }
    if (!ec_point_is_compat(point, group)) {
        ECerr(EC_F_EC_POINT_GET_AFFINE_COORDINATES, EC_R_INCOMPATIBLE_OBJECTS);
        return 0;
    }
    if (EC_POINT_is_at_infinity(group, point)) {
        ECerr(EC_F_EC_POINT_GET_AFFINE_COORDINATES, EC_R_POINT_AT_INFINITY);
        return 0;
    }
    return group->meth->point_get_affine_coordinates(group, point, x, y, ctx);
}