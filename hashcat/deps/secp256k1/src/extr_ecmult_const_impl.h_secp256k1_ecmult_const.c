#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const secp256k1_scalar ;
struct TYPE_26__ {int /*<<< orphan*/  z; } ;
typedef  TYPE_1__ secp256k1_gej ;
typedef  int /*<<< orphan*/  secp256k1_ge_storage ;
struct TYPE_27__ {int /*<<< orphan*/  y; } ;
typedef  TYPE_2__ const secp256k1_ge ;
typedef  int /*<<< orphan*/  secp256k1_fe ;

/* Variables and functions */
 int /*<<< orphan*/  ECMULT_CONST_TABLE_GET_GE (TYPE_2__ const*,TYPE_2__ const*,int,int) ; 
 int ECMULT_TABLE_SIZE (int) ; 
 int /*<<< orphan*/  VERIFY_CHECK (int) ; 
 int WINDOW_A ; 
 int /*<<< orphan*/  WNAF_SIZE (int) ; 
 int WNAF_SIZE_BITS (int,int) ; 
 int /*<<< orphan*/  secp256k1_ecmult_odd_multiples_table_globalz_windowa (TYPE_2__ const*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  secp256k1_fe_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_fe_normalize_weak (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_ge_from_storage (TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_ge_mul_lambda (TYPE_2__ const*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  secp256k1_ge_neg (TYPE_2__ const*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  secp256k1_ge_set_gej (TYPE_2__ const*,TYPE_1__*) ; 
 int /*<<< orphan*/  secp256k1_ge_storage_cmov (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  secp256k1_ge_to_storage (int /*<<< orphan*/ *,TYPE_2__ const*) ; 
 int /*<<< orphan*/  secp256k1_gej_add_ge (TYPE_1__*,TYPE_1__*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  secp256k1_gej_double_nonzero (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_gej_double_var (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_gej_set_ge (TYPE_1__*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  secp256k1_scalar_split_lambda (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int secp256k1_wnaf_const (int*,int /*<<< orphan*/  const*,int,int) ; 

__attribute__((used)) static void secp256k1_ecmult_const(secp256k1_gej *r, const secp256k1_ge *a, const secp256k1_scalar *scalar, int size) {
    secp256k1_ge pre_a[ECMULT_TABLE_SIZE(WINDOW_A)];
    secp256k1_ge tmpa;
    secp256k1_fe Z;

    int skew_1;
#ifdef USE_ENDOMORPHISM
    secp256k1_ge pre_a_lam[ECMULT_TABLE_SIZE(WINDOW_A)];
    int wnaf_lam[1 + WNAF_SIZE(WINDOW_A - 1)];
    int skew_lam;
    secp256k1_scalar q_1, q_lam;
#endif
    int wnaf_1[1 + WNAF_SIZE(WINDOW_A - 1)];

    int i;

    /* build wnaf representation for q. */
    int rsize = size;
#ifdef USE_ENDOMORPHISM
    if (size > 128) {
        rsize = 128;
        /* split q into q_1 and q_lam (where q = q_1 + q_lam*lambda, and q_1 and q_lam are ~128 bit) */
        secp256k1_scalar_split_lambda(&q_1, &q_lam, scalar);
        skew_1   = secp256k1_wnaf_const(wnaf_1,   &q_1,   WINDOW_A - 1, 128);
        skew_lam = secp256k1_wnaf_const(wnaf_lam, &q_lam, WINDOW_A - 1, 128);
    } else
#endif
    {
        skew_1   = secp256k1_wnaf_const(wnaf_1, scalar, WINDOW_A - 1, size);
#ifdef USE_ENDOMORPHISM
        skew_lam = 0;
#endif
    }

    /* Calculate odd multiples of a.
     * All multiples are brought to the same Z 'denominator', which is stored
     * in Z. Due to secp256k1' isomorphism we can do all operations pretending
     * that the Z coordinate was 1, use affine addition formulae, and correct
     * the Z coordinate of the result once at the end.
     */
    secp256k1_gej_set_ge(r, a);
    secp256k1_ecmult_odd_multiples_table_globalz_windowa(pre_a, &Z, r);
    for (i = 0; i < ECMULT_TABLE_SIZE(WINDOW_A); i++) {
        secp256k1_fe_normalize_weak(&pre_a[i].y);
    }
#ifdef USE_ENDOMORPHISM
    if (size > 128) {
        for (i = 0; i < ECMULT_TABLE_SIZE(WINDOW_A); i++) {
            secp256k1_ge_mul_lambda(&pre_a_lam[i], &pre_a[i]);
        }
    }
#endif

    /* first loop iteration (separated out so we can directly set r, rather
     * than having it start at infinity, get doubled several times, then have
     * its new value added to it) */
    i = wnaf_1[WNAF_SIZE_BITS(rsize, WINDOW_A - 1)];
    VERIFY_CHECK(i != 0);
    ECMULT_CONST_TABLE_GET_GE(&tmpa, pre_a, i, WINDOW_A);
    secp256k1_gej_set_ge(r, &tmpa);
#ifdef USE_ENDOMORPHISM
    if (size > 128) {
        i = wnaf_lam[WNAF_SIZE_BITS(rsize, WINDOW_A - 1)];
        VERIFY_CHECK(i != 0);
        ECMULT_CONST_TABLE_GET_GE(&tmpa, pre_a_lam, i, WINDOW_A);
        secp256k1_gej_add_ge(r, r, &tmpa);
    }
#endif
    /* remaining loop iterations */
    for (i = WNAF_SIZE_BITS(rsize, WINDOW_A - 1) - 1; i >= 0; i--) {
        int n;
        int j;
        for (j = 0; j < WINDOW_A - 1; ++j) {
            secp256k1_gej_double_nonzero(r, r, NULL);
        }

        n = wnaf_1[i];
        ECMULT_CONST_TABLE_GET_GE(&tmpa, pre_a, n, WINDOW_A);
        VERIFY_CHECK(n != 0);
        secp256k1_gej_add_ge(r, r, &tmpa);
#ifdef USE_ENDOMORPHISM
        if (size > 128) {
            n = wnaf_lam[i];
            ECMULT_CONST_TABLE_GET_GE(&tmpa, pre_a_lam, n, WINDOW_A);
            VERIFY_CHECK(n != 0);
            secp256k1_gej_add_ge(r, r, &tmpa);
        }
#endif
    }

    secp256k1_fe_mul(&r->z, &r->z, &Z);

    {
        /* Correct for wNAF skew */
        secp256k1_ge correction = *a;
        secp256k1_ge_storage correction_1_stor;
#ifdef USE_ENDOMORPHISM
        secp256k1_ge_storage correction_lam_stor;
#endif
        secp256k1_ge_storage a2_stor;
        secp256k1_gej tmpj;
        secp256k1_gej_set_ge(&tmpj, &correction);
        secp256k1_gej_double_var(&tmpj, &tmpj, NULL);
        secp256k1_ge_set_gej(&correction, &tmpj);
        secp256k1_ge_to_storage(&correction_1_stor, a);
#ifdef USE_ENDOMORPHISM
        if (size > 128) {
            secp256k1_ge_to_storage(&correction_lam_stor, a);
        }
#endif
        secp256k1_ge_to_storage(&a2_stor, &correction);

        /* For odd numbers this is 2a (so replace it), for even ones a (so no-op) */
        secp256k1_ge_storage_cmov(&correction_1_stor, &a2_stor, skew_1 == 2);
#ifdef USE_ENDOMORPHISM
        if (size > 128) {
            secp256k1_ge_storage_cmov(&correction_lam_stor, &a2_stor, skew_lam == 2);
        }
#endif

        /* Apply the correction */
        secp256k1_ge_from_storage(&correction, &correction_1_stor);
        secp256k1_ge_neg(&correction, &correction);
        secp256k1_gej_add_ge(r, r, &correction);

#ifdef USE_ENDOMORPHISM
        if (size > 128) {
            secp256k1_ge_from_storage(&correction, &correction_lam_stor);
            secp256k1_ge_neg(&correction, &correction);
            secp256k1_ge_mul_lambda(&correction, &correction);
            secp256k1_gej_add_ge(r, r, &correction);
        }
#endif
    }
}