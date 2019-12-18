#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * mont_data; int /*<<< orphan*/  order; int /*<<< orphan*/  cofactor; int /*<<< orphan*/ * generator; int /*<<< orphan*/  const* field; } ;
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  TYPE_1__ EC_GROUP ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_MONT_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 scalar_t__ BN_is_negative (int /*<<< orphan*/  const*) ; 
 scalar_t__ BN_is_odd (int /*<<< orphan*/ ) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/  const*) ; 
 scalar_t__ BN_num_bits (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_F_EC_GROUP_SET_GENERATOR ; 
 int /*<<< orphan*/  EC_POINT_copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EC_POINT_new (TYPE_1__*) ; 
 int /*<<< orphan*/  EC_R_INVALID_FIELD ; 
 int /*<<< orphan*/  EC_R_INVALID_GROUP_ORDER ; 
 int /*<<< orphan*/  EC_R_UNKNOWN_COFACTOR ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_PASSED_NULL_PARAMETER ; 
 int /*<<< orphan*/  ec_guess_cofactor (TYPE_1__*) ; 
 int ec_precompute_mont_data (TYPE_1__*) ; 

int EC_GROUP_set_generator(EC_GROUP *group, const EC_POINT *generator,
                           const BIGNUM *order, const BIGNUM *cofactor)
{
    if (generator == NULL) {
        ECerr(EC_F_EC_GROUP_SET_GENERATOR, ERR_R_PASSED_NULL_PARAMETER);
        return 0;
    }

    /* require group->field >= 1 */
    if (group->field == NULL || BN_is_zero(group->field)
        || BN_is_negative(group->field)) {
        ECerr(EC_F_EC_GROUP_SET_GENERATOR, EC_R_INVALID_FIELD);
        return 0;
    }

    /*-
     * - require order >= 1
     * - enforce upper bound due to Hasse thm: order can be no more than one bit
     *   longer than field cardinality
     */
    if (order == NULL || BN_is_zero(order) || BN_is_negative(order)
        || BN_num_bits(order) > BN_num_bits(group->field) + 1) {
        ECerr(EC_F_EC_GROUP_SET_GENERATOR, EC_R_INVALID_GROUP_ORDER);
        return 0;
    }

    /*-
     * Unfortunately the cofactor is an optional field in many standards.
     * Internally, the lib uses 0 cofactor as a marker for "unknown cofactor".
     * So accept cofactor == NULL or cofactor >= 0.
     */
    if (cofactor != NULL && BN_is_negative(cofactor)) {
        ECerr(EC_F_EC_GROUP_SET_GENERATOR, EC_R_UNKNOWN_COFACTOR);
        return 0;
    }

    if (group->generator == NULL) {
        group->generator = EC_POINT_new(group);
        if (group->generator == NULL)
            return 0;
    }
    if (!EC_POINT_copy(group->generator, generator))
        return 0;

    if (!BN_copy(group->order, order))
        return 0;

    /* Either take the provided positive cofactor, or try to compute it */
    if (cofactor != NULL && !BN_is_zero(cofactor)) {
        if (!BN_copy(group->cofactor, cofactor))
            return 0;
    } else if (!ec_guess_cofactor(group)) {
        BN_zero(group->cofactor);
        return 0;
    }

    /*
     * Some groups have an order with
     * factors of two, which makes the Montgomery setup fail.
     * |group->mont_data| will be NULL in this case.
     */
    if (BN_is_odd(group->order)) {
        return ec_precompute_mont_data(group);
    }

    BN_MONT_CTX_free(group->mont_data);
    group->mont_data = NULL;
    return 1;
}