#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;

/* Type definitions */
struct TYPE_32__ {int /*<<< orphan*/  field; TYPE_1__* meth; int /*<<< orphan*/ * a; int /*<<< orphan*/  b; } ;
struct TYPE_31__ {int /*<<< orphan*/ * Z; int /*<<< orphan*/ * X; } ;
struct TYPE_30__ {int /*<<< orphan*/  (* field_mul ) (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* field_sqr ) (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ EC_POINT ;
typedef  TYPE_3__ EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_add_quick (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_mod_lshift1_quick (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_mod_lshift_quick (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_mod_sub_quick (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub10 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub11 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub12 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub13 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub14 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub15 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub16 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub17 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub18 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub19 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub20 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub21 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub22 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub6 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub7 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub8 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub9 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int ec_GFp_simple_ladder_step(const EC_GROUP *group,
                              EC_POINT *r, EC_POINT *s,
                              EC_POINT *p, BN_CTX *ctx)
{
    int ret = 0;
    BIGNUM *t0, *t1, *t2, *t3, *t4, *t5, *t6, *t7 = NULL;

    BN_CTX_start(ctx);
    t0 = BN_CTX_get(ctx);
    t1 = BN_CTX_get(ctx);
    t2 = BN_CTX_get(ctx);
    t3 = BN_CTX_get(ctx);
    t4 = BN_CTX_get(ctx);
    t5 = BN_CTX_get(ctx);
    t6 = BN_CTX_get(ctx);
    t7 = BN_CTX_get(ctx);

    if (t7 == NULL
        || !group->meth->field_mul(group, t0, r->X, s->X, ctx)
        || !group->meth->field_mul(group, t1, r->Z, s->Z, ctx)
        || !group->meth->field_mul(group, t2, r->X, s->Z, ctx)
        || !group->meth->field_mul(group, t3, r->Z, s->X, ctx)
        || !group->meth->field_mul(group, t4, group->a, t1, ctx)
        || !BN_mod_add_quick(t0, t0, t4, group->field)
        || !BN_mod_add_quick(t4, t3, t2, group->field)
        || !group->meth->field_mul(group, t0, t4, t0, ctx)
        || !group->meth->field_sqr(group, t1, t1, ctx)
        || !BN_mod_lshift_quick(t7, group->b, 2, group->field)
        || !group->meth->field_mul(group, t1, t7, t1, ctx)
        || !BN_mod_lshift1_quick(t0, t0, group->field)
        || !BN_mod_add_quick(t0, t1, t0, group->field)
        || !BN_mod_sub_quick(t1, t2, t3, group->field)
        || !group->meth->field_sqr(group, t1, t1, ctx)
        || !group->meth->field_mul(group, t3, t1, p->X, ctx)
        || !group->meth->field_mul(group, t0, p->Z, t0, ctx)
        /* s->X coord output */
        || !BN_mod_sub_quick(s->X, t0, t3, group->field)
        /* s->Z coord output */
        || !group->meth->field_mul(group, s->Z, p->Z, t1, ctx)
        || !group->meth->field_sqr(group, t3, r->X, ctx)
        || !group->meth->field_sqr(group, t2, r->Z, ctx)
        || !group->meth->field_mul(group, t4, t2, group->a, ctx)
        || !BN_mod_add_quick(t5, r->X, r->Z, group->field)
        || !group->meth->field_sqr(group, t5, t5, ctx)
        || !BN_mod_sub_quick(t5, t5, t3, group->field)
        || !BN_mod_sub_quick(t5, t5, t2, group->field)
        || !BN_mod_sub_quick(t6, t3, t4, group->field)
        || !group->meth->field_sqr(group, t6, t6, ctx)
        || !group->meth->field_mul(group, t0, t2, t5, ctx)
        || !group->meth->field_mul(group, t0, t7, t0, ctx)
        /* r->X coord output */
        || !BN_mod_sub_quick(r->X, t6, t0, group->field)
        || !BN_mod_add_quick(t6, t3, t4, group->field)
        || !group->meth->field_sqr(group, t3, t2, ctx)
        || !group->meth->field_mul(group, t7, t3, t7, ctx)
        || !group->meth->field_mul(group, t5, t5, t6, ctx)
        || !BN_mod_lshift1_quick(t5, t5, group->field)
        /* r->Z coord output */
        || !BN_mod_add_quick(r->Z, t7, t5, group->field))
        goto err;

    ret = 1;

 err:
    BN_CTX_end(ctx);
    return ret;
}