#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_1__* meth; } ;
struct TYPE_13__ {int flags; int /*<<< orphan*/  (* group_get_curve ) (TYPE_2__ const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  const BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int EC_FLAGS_CUSTOM_CURVE ; 
 int /*<<< orphan*/  const* EC_GROUP_get0_cofactor (TYPE_2__ const*) ; 
 int /*<<< orphan*/  EC_GROUP_get0_generator (TYPE_2__ const*) ; 
 int /*<<< orphan*/  const* EC_GROUP_get0_order (TYPE_2__ const*) ; 
 scalar_t__ EC_GROUP_get_curve_name (TYPE_2__ const*) ; 
 int /*<<< orphan*/  EC_GROUP_method_of (TYPE_2__ const*) ; 
 scalar_t__ EC_METHOD_get_field_type (int /*<<< orphan*/ ) ; 
 scalar_t__ EC_POINT_cmp (TYPE_2__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__ const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__ const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int EC_GROUP_cmp(const EC_GROUP *a, const EC_GROUP *b, BN_CTX *ctx)
{
    int r = 0;
    BIGNUM *a1, *a2, *a3, *b1, *b2, *b3;
    BN_CTX *ctx_new = NULL;

    /* compare the field types */
    if (EC_METHOD_get_field_type(EC_GROUP_method_of(a)) !=
        EC_METHOD_get_field_type(EC_GROUP_method_of(b)))
        return 1;
    /* compare the curve name (if present in both) */
    if (EC_GROUP_get_curve_name(a) && EC_GROUP_get_curve_name(b) &&
        EC_GROUP_get_curve_name(a) != EC_GROUP_get_curve_name(b))
        return 1;
    if (a->meth->flags & EC_FLAGS_CUSTOM_CURVE)
        return 0;

    if (ctx == NULL)
        ctx_new = ctx = BN_CTX_new();
    if (ctx == NULL)
        return -1;

    BN_CTX_start(ctx);
    a1 = BN_CTX_get(ctx);
    a2 = BN_CTX_get(ctx);
    a3 = BN_CTX_get(ctx);
    b1 = BN_CTX_get(ctx);
    b2 = BN_CTX_get(ctx);
    b3 = BN_CTX_get(ctx);
    if (b3 == NULL) {
        BN_CTX_end(ctx);
        BN_CTX_free(ctx_new);
        return -1;
    }

    /*
     * XXX This approach assumes that the external representation of curves
     * over the same field type is the same.
     */
    if (!a->meth->group_get_curve(a, a1, a2, a3, ctx) ||
        !b->meth->group_get_curve(b, b1, b2, b3, ctx))
        r = 1;

    if (r || BN_cmp(a1, b1) || BN_cmp(a2, b2) || BN_cmp(a3, b3))
        r = 1;

    /* XXX EC_POINT_cmp() assumes that the methods are equal */
    if (r || EC_POINT_cmp(a, EC_GROUP_get0_generator(a),
                          EC_GROUP_get0_generator(b), ctx))
        r = 1;

    if (!r) {
        const BIGNUM *ao, *bo, *ac, *bc;
        /* compare the order and cofactor */
        ao = EC_GROUP_get0_order(a);
        bo = EC_GROUP_get0_order(b);
        ac = EC_GROUP_get0_cofactor(a);
        bc = EC_GROUP_get0_cofactor(b);
        if (ao == NULL || bo == NULL) {
            BN_CTX_end(ctx);
            BN_CTX_free(ctx_new);
            return -1;
        }
        if (BN_cmp(ao, bo) || BN_cmp(ac, bc))
            r = 1;
    }

    BN_CTX_end(ctx);
    BN_CTX_free(ctx_new);

    return r;
}