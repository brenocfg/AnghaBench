#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  cofactor; int /*<<< orphan*/  order; } ;
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  TYPE_1__ EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 scalar_t__ BN_is_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_F_EC_GF2M_SIMPLE_POINTS_MUL ; 
 int /*<<< orphan*/  EC_POINT_add (TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_POINT_new (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int ec_scalar_mul_ladder (TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int ec_wNAF_mul (TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
int ec_GF2m_simple_points_mul(const EC_GROUP *group, EC_POINT *r,
                              const BIGNUM *scalar, size_t num,
                              const EC_POINT *points[],
                              const BIGNUM *scalars[],
                              BN_CTX *ctx)
{
    int ret = 0;
    EC_POINT *t = NULL;

    /*-
     * We limit use of the ladder only to the following cases:
     * - r := scalar * G
     *   Fixed point mul: scalar != NULL && num == 0;
     * - r := scalars[0] * points[0]
     *   Variable point mul: scalar == NULL && num == 1;
     * - r := scalar * G + scalars[0] * points[0]
     *   used, e.g., in ECDSA verification: scalar != NULL && num == 1
     *
     * In any other case (num > 1) we use the default wNAF implementation.
     *
     * We also let the default implementation handle degenerate cases like group
     * order or cofactor set to 0.
     */
    if (num > 1 || BN_is_zero(group->order) || BN_is_zero(group->cofactor))
        return ec_wNAF_mul(group, r, scalar, num, points, scalars, ctx);

    if (scalar != NULL && num == 0)
        /* Fixed point multiplication */
        return ec_scalar_mul_ladder(group, r, scalar, NULL, ctx);

    if (scalar == NULL && num == 1)
        /* Variable point multiplication */
        return ec_scalar_mul_ladder(group, r, scalars[0], points[0], ctx);

    /*-
     * Double point multiplication:
     *  r := scalar * G + scalars[0] * points[0]
     */

    if ((t = EC_POINT_new(group)) == NULL) {
        ECerr(EC_F_EC_GF2M_SIMPLE_POINTS_MUL, ERR_R_MALLOC_FAILURE);
        return 0;
    }

    if (!ec_scalar_mul_ladder(group, t, scalar, NULL, ctx)
        || !ec_scalar_mul_ladder(group, r, scalars[0], points[0], ctx)
        || !EC_POINT_add(group, r, t, r, ctx))
        goto err;

    ret = 1;

 err:
    EC_POINT_free(t);
    return ret;
}