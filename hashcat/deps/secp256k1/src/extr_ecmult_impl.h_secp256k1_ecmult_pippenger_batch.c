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
struct secp256k1_pippenger_state {int* wnaf_na; struct secp256k1_pippenger_point_state* ps; } ;
struct secp256k1_pippenger_point_state {scalar_t__ skew_na; } ;
typedef  int /*<<< orphan*/  secp256k1_scratch ;
typedef  int /*<<< orphan*/  secp256k1_scalar ;
typedef  int /*<<< orphan*/  secp256k1_gej ;
typedef  int /*<<< orphan*/  secp256k1_ge ;
typedef  int /*<<< orphan*/  (* secp256k1_ecmult_multi_callback ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,void*) ;
typedef  int /*<<< orphan*/  secp256k1_ecmult_context ;
typedef  int /*<<< orphan*/  secp256k1_callback ;

/* Variables and functions */
 int WNAF_SIZE (int) ; 
 int /*<<< orphan*/  secp256k1_ecmult_endo_split (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_ecmult_pippenger_wnaf (int /*<<< orphan*/ *,int,struct secp256k1_pippenger_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  secp256k1_ge_const_g ; 
 int /*<<< orphan*/  secp256k1_gej_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_gej_set_infinity (int /*<<< orphan*/ *) ; 
 int secp256k1_pippenger_bucket_window (size_t) ; 
 int /*<<< orphan*/  secp256k1_scalar_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ secp256k1_scratch_alloc (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  secp256k1_scratch_apply_checkpoint (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,size_t const) ; 
 size_t secp256k1_scratch_checkpoint (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int secp256k1_ecmult_pippenger_batch(const secp256k1_callback* error_callback, const secp256k1_ecmult_context *ctx, secp256k1_scratch *scratch, secp256k1_gej *r, const secp256k1_scalar *inp_g_sc, secp256k1_ecmult_multi_callback cb, void *cbdata, size_t n_points, size_t cb_offset) {
    const size_t scratch_checkpoint = secp256k1_scratch_checkpoint(error_callback, scratch);
    /* Use 2(n+1) with the endomorphism, n+1 without, when calculating batch
     * sizes. The reason for +1 is that we add the G scalar to the list of
     * other scalars. */
#ifdef USE_ENDOMORPHISM
    size_t entries = 2*n_points + 2;
#else
    size_t entries = n_points + 1;
#endif
    secp256k1_ge *points;
    secp256k1_scalar *scalars;
    secp256k1_gej *buckets;
    struct secp256k1_pippenger_state *state_space;
    size_t idx = 0;
    size_t point_idx = 0;
    int i, j;
    int bucket_window;

    (void)ctx;
    secp256k1_gej_set_infinity(r);
    if (inp_g_sc == NULL && n_points == 0) {
        return 1;
    }

    bucket_window = secp256k1_pippenger_bucket_window(n_points);
    points = (secp256k1_ge *) secp256k1_scratch_alloc(error_callback, scratch, entries * sizeof(*points));
    scalars = (secp256k1_scalar *) secp256k1_scratch_alloc(error_callback, scratch, entries * sizeof(*scalars));
    state_space = (struct secp256k1_pippenger_state *) secp256k1_scratch_alloc(error_callback, scratch, sizeof(*state_space));
    if (points == NULL || scalars == NULL || state_space == NULL) {
        secp256k1_scratch_apply_checkpoint(error_callback, scratch, scratch_checkpoint);
        return 0;
    }

    state_space->ps = (struct secp256k1_pippenger_point_state *) secp256k1_scratch_alloc(error_callback, scratch, entries * sizeof(*state_space->ps));
    state_space->wnaf_na = (int *) secp256k1_scratch_alloc(error_callback, scratch, entries*(WNAF_SIZE(bucket_window+1)) * sizeof(int));
    buckets = (secp256k1_gej *) secp256k1_scratch_alloc(error_callback, scratch, (1<<bucket_window) * sizeof(*buckets));
    if (state_space->ps == NULL || state_space->wnaf_na == NULL || buckets == NULL) {
        secp256k1_scratch_apply_checkpoint(error_callback, scratch, scratch_checkpoint);
        return 0;
    }

    if (inp_g_sc != NULL) {
        scalars[0] = *inp_g_sc;
        points[0] = secp256k1_ge_const_g;
        idx++;
#ifdef USE_ENDOMORPHISM
        secp256k1_ecmult_endo_split(&scalars[0], &scalars[1], &points[0], &points[1]);
        idx++;
#endif
    }

    while (point_idx < n_points) {
        if (!cb(&scalars[idx], &points[idx], point_idx + cb_offset, cbdata)) {
            secp256k1_scratch_apply_checkpoint(error_callback, scratch, scratch_checkpoint);
            return 0;
        }
        idx++;
#ifdef USE_ENDOMORPHISM
        secp256k1_ecmult_endo_split(&scalars[idx - 1], &scalars[idx], &points[idx - 1], &points[idx]);
        idx++;
#endif
        point_idx++;
    }

    secp256k1_ecmult_pippenger_wnaf(buckets, bucket_window, state_space, r, scalars, points, idx);

    /* Clear data */
    for(i = 0; (size_t)i < idx; i++) {
        secp256k1_scalar_clear(&scalars[i]);
        state_space->ps[i].skew_na = 0;
        for(j = 0; j < WNAF_SIZE(bucket_window+1); j++) {
            state_space->wnaf_na[i * WNAF_SIZE(bucket_window+1) + j] = 0;
        }
    }
    for(i = 0; i < 1<<bucket_window; i++) {
        secp256k1_gej_clear(&buckets[i]);
    }
    secp256k1_scratch_apply_checkpoint(error_callback, scratch, scratch_checkpoint);
    return 1;
}