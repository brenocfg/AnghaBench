#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  secp256k1_scalar ;
typedef  int /*<<< orphan*/  secp256k1_gej ;
typedef  int /*<<< orphan*/  secp256k1_ge ;
typedef  int /*<<< orphan*/  (* secp256k1_ecmult_multi_callback ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,void*) ;
typedef  int /*<<< orphan*/  secp256k1_ecmult_context ;

/* Variables and functions */
 int /*<<< orphan*/  secp256k1_ecmult (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  secp256k1_gej_add_var (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_gej_set_ge (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_gej_set_infinity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_scalar_set_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int secp256k1_ecmult_multi_simple_var(const secp256k1_ecmult_context *ctx, secp256k1_gej *r, const secp256k1_scalar *inp_g_sc, secp256k1_ecmult_multi_callback cb, void *cbdata, size_t n_points) {
    size_t point_idx;
    secp256k1_scalar szero;
    secp256k1_gej tmpj;

    secp256k1_scalar_set_int(&szero, 0);
    secp256k1_gej_set_infinity(r);
    secp256k1_gej_set_infinity(&tmpj);
    /* r = inp_g_sc*G */
    secp256k1_ecmult(ctx, r, &tmpj, &szero, inp_g_sc);
    for (point_idx = 0; point_idx < n_points; point_idx++) {
        secp256k1_ge point;
        secp256k1_gej pointj;
        secp256k1_scalar scalar;
        if (!cb(&scalar, &point, point_idx, cbdata)) {
            return 0;
        }
        /* r += scalar*point */
        secp256k1_gej_set_ge(&pointj, &point);
        secp256k1_ecmult(ctx, &tmpj, &pointj, &scalar, NULL);
        secp256k1_gej_add_var(r, r, &tmpj, NULL);
    }
    return 1;
}