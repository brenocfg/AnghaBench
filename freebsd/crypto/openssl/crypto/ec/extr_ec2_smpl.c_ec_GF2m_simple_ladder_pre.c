#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_1__* meth; int /*<<< orphan*/  b; int /*<<< orphan*/  field; } ;
struct TYPE_16__ {scalar_t__ Z_is_one; int /*<<< orphan*/  Y; int /*<<< orphan*/  X; int /*<<< orphan*/  Z; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* field_mul ) (TYPE_3__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* field_sqr ) (TYPE_3__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* field_encode ) (TYPE_3__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ EC_POINT ;
typedef  TYPE_3__ EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  BN_GF2m_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_RAND_BOTTOM_ANY ; 
 int /*<<< orphan*/  BN_RAND_TOP_ANY ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/ ) ; 
 scalar_t__ BN_num_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_priv_rand (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_F_EC_GF2M_SIMPLE_LADDER_PRE ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_BN_LIB ; 
 int /*<<< orphan*/  stub1 (TYPE_3__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (TYPE_3__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (TYPE_3__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub6 (TYPE_3__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub7 (TYPE_3__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
int ec_GF2m_simple_ladder_pre(const EC_GROUP *group,
                              EC_POINT *r, EC_POINT *s,
                              EC_POINT *p, BN_CTX *ctx)
{
    /* if p is not affine, something is wrong */
    if (p->Z_is_one == 0)
        return 0;

    /* s blinding: make sure lambda (s->Z here) is not zero */
    do {
        if (!BN_priv_rand(s->Z, BN_num_bits(group->field) - 1,
                          BN_RAND_TOP_ANY, BN_RAND_BOTTOM_ANY)) {
            ECerr(EC_F_EC_GF2M_SIMPLE_LADDER_PRE, ERR_R_BN_LIB);
            return 0;
        }
    } while (BN_is_zero(s->Z));

    /* if field_encode defined convert between representations */
    if ((group->meth->field_encode != NULL
         && !group->meth->field_encode(group, s->Z, s->Z, ctx))
        || !group->meth->field_mul(group, s->X, p->X, s->Z, ctx))
        return 0;

    /* r blinding: make sure lambda (r->Y here for storage) is not zero */
    do {
        if (!BN_priv_rand(r->Y, BN_num_bits(group->field) - 1,
                          BN_RAND_TOP_ANY, BN_RAND_BOTTOM_ANY)) {
            ECerr(EC_F_EC_GF2M_SIMPLE_LADDER_PRE, ERR_R_BN_LIB);
            return 0;
        }
    } while (BN_is_zero(r->Y));

    if ((group->meth->field_encode != NULL
         && !group->meth->field_encode(group, r->Y, r->Y, ctx))
        || !group->meth->field_sqr(group, r->Z, p->X, ctx)
        || !group->meth->field_sqr(group, r->X, r->Z, ctx)
        || !BN_GF2m_add(r->X, r->X, group->b)
        || !group->meth->field_mul(group, r->Z, r->Z, r->Y, ctx)
        || !group->meth->field_mul(group, r->X, r->X, r->Y, ctx))
        return 0;

    s->Z_is_one = 0;
    r->Z_is_one = 0;

    return 1;
}