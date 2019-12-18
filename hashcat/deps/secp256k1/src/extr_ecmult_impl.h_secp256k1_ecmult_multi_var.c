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
typedef  int /*<<< orphan*/  secp256k1_scratch ;
typedef  int /*<<< orphan*/  secp256k1_scalar ;
typedef  int /*<<< orphan*/  secp256k1_gej ;
typedef  int /*<<< orphan*/  secp256k1_ecmult_multi_callback ;
typedef  int /*<<< orphan*/  secp256k1_ecmult_context ;
typedef  int /*<<< orphan*/  secp256k1_callback ;

/* Variables and functions */
 size_t ECMULT_PIPPENGER_THRESHOLD ; 
 int /*<<< orphan*/  secp256k1_ecmult (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  secp256k1_ecmult_multi_batch_size_helper (size_t*,size_t*,int /*<<< orphan*/ ,size_t) ; 
 int secp256k1_ecmult_multi_simple_var (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,void*,size_t) ; 
 int secp256k1_ecmult_pippenger_batch (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,void*,size_t,size_t) ; 
 int secp256k1_ecmult_strauss_batch (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,void*,size_t,size_t) ; 
 int /*<<< orphan*/  secp256k1_gej_add_var (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_gej_set_infinity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_pippenger_max_points (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_scalar_set_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  secp256k1_strauss_max_points (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int secp256k1_ecmult_multi_var(const secp256k1_callback* error_callback, const secp256k1_ecmult_context *ctx, secp256k1_scratch *scratch, secp256k1_gej *r, const secp256k1_scalar *inp_g_sc, secp256k1_ecmult_multi_callback cb, void *cbdata, size_t n) {
    size_t i;

    int (*f)(const secp256k1_callback* error_callback, const secp256k1_ecmult_context*, secp256k1_scratch*, secp256k1_gej*, const secp256k1_scalar*, secp256k1_ecmult_multi_callback cb, void*, size_t, size_t);
    size_t n_batches;
    size_t n_batch_points;

    secp256k1_gej_set_infinity(r);
    if (inp_g_sc == NULL && n == 0) {
        return 1;
    } else if (n == 0) {
        secp256k1_scalar szero;
        secp256k1_scalar_set_int(&szero, 0);
        secp256k1_ecmult(ctx, r, r, &szero, inp_g_sc);
        return 1;
    }
    if (scratch == NULL) {
        return secp256k1_ecmult_multi_simple_var(ctx, r, inp_g_sc, cb, cbdata, n);
    }

    /* Compute the batch sizes for Pippenger's algorithm given a scratch space. If it's greater than
     * a threshold use Pippenger's algorithm. Otherwise use Strauss' algorithm.
     * As a first step check if there's enough space for Pippenger's algo (which requires less space
     * than Strauss' algo) and if not, use the simple algorithm. */
    if (!secp256k1_ecmult_multi_batch_size_helper(&n_batches, &n_batch_points, secp256k1_pippenger_max_points(error_callback, scratch), n)) {
        return secp256k1_ecmult_multi_simple_var(ctx, r, inp_g_sc, cb, cbdata, n);
    }
    if (n_batch_points >= ECMULT_PIPPENGER_THRESHOLD) {
        f = secp256k1_ecmult_pippenger_batch;
    } else {
        if (!secp256k1_ecmult_multi_batch_size_helper(&n_batches, &n_batch_points, secp256k1_strauss_max_points(error_callback, scratch), n)) {
            return secp256k1_ecmult_multi_simple_var(ctx, r, inp_g_sc, cb, cbdata, n);
        }
        f = secp256k1_ecmult_strauss_batch;
    }
    for(i = 0; i < n_batches; i++) {
        size_t nbp = n < n_batch_points ? n : n_batch_points;
        size_t offset = n_batch_points*i;
        secp256k1_gej tmp;
        if (!f(error_callback, ctx, scratch, &tmp, i == 0 ? inp_g_sc : NULL, cb, cbdata, nbp, offset)) {
            return 0;
        }
        secp256k1_gej_add_var(r, r, &tmp, NULL);
        n -= nbp;
    }
    return 1;
}