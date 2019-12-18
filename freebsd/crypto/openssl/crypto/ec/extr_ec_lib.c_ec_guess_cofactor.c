#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  order; int /*<<< orphan*/ * cofactor; int /*<<< orphan*/  field; TYPE_1__* meth; } ;
struct TYPE_4__ {scalar_t__ field_type; } ;
typedef  TYPE_2__ EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_div (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int BN_num_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_rshift1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_set_bit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * BN_value_one () ; 
 int /*<<< orphan*/  BN_zero (int /*<<< orphan*/ *) ; 
 scalar_t__ NID_X9_62_characteristic_two_field ; 

__attribute__((used)) static int ec_guess_cofactor(EC_GROUP *group) {
    int ret = 0;
    BN_CTX *ctx = NULL;
    BIGNUM *q = NULL;

    /*-
     * If the cofactor is too large, we cannot guess it.
     * The RHS of below is a strict overestimate of lg(4 * sqrt(q))
     */
    if (BN_num_bits(group->order) <= (BN_num_bits(group->field) + 1) / 2 + 3) {
        /* default to 0 */
        BN_zero(group->cofactor);
        /* return success */
        return 1;
    }

    if ((ctx = BN_CTX_new()) == NULL)
        return 0;

    BN_CTX_start(ctx);
    if ((q = BN_CTX_get(ctx)) == NULL)
        goto err;

    /* set q = 2**m for binary fields; q = p otherwise */
    if (group->meth->field_type == NID_X9_62_characteristic_two_field) {
        BN_zero(q);
        if (!BN_set_bit(q, BN_num_bits(group->field) - 1))
            goto err;
    } else {
        if (!BN_copy(q, group->field))
            goto err;
    }

    /* compute h = \lfloor (q + 1)/n \rceil = \lfloor (q + 1 + n/2)/n \rfloor */
    if (!BN_rshift1(group->cofactor, group->order) /* n/2 */
        || !BN_add(group->cofactor, group->cofactor, q) /* q + n/2 */
        /* q + 1 + n/2 */
        || !BN_add(group->cofactor, group->cofactor, BN_value_one())
        /* (q + 1 + n/2)/n */
        || !BN_div(group->cofactor, NULL, group->cofactor, group->order, ctx))
        goto err;
    ret = 1;
 err:
    BN_CTX_end(ctx);
    BN_CTX_free(ctx);
    return ret;
}