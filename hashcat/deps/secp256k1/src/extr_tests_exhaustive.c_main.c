#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  secp256k1_scalar ;
typedef  int /*<<< orphan*/  secp256k1_gej ;
struct TYPE_20__ {scalar_t__ infinity; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ secp256k1_ge ;
typedef  int /*<<< orphan*/  secp256k1_fe ;
struct TYPE_21__ {int /*<<< orphan*/  ecmult_gen_ctx; } ;
typedef  TYPE_2__ secp256k1_context ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int) ; 
 int EXHAUSTIVE_TEST_ORDER ; 
 int SECP256K1_CONTEXT_SIGN ; 
 int SECP256K1_CONTEXT_VERIFY ; 
 int /*<<< orphan*/  random_fe (int /*<<< orphan*/ *) ; 
 TYPE_2__* secp256k1_context_create (int) ; 
 int /*<<< orphan*/  secp256k1_context_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  secp256k1_ecmult_gen (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int secp256k1_fe_equal_var (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_ge_const_g ; 
 int /*<<< orphan*/  secp256k1_ge_set_gej (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_gej_add_ge (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_gej_rescale (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_gej_set_infinity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_scalar_set_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_exhaustive_addition (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_exhaustive_ecmult (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_exhaustive_ecmult_multi (TYPE_2__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  test_exhaustive_endomorphism (TYPE_1__*,int) ; 
 int /*<<< orphan*/  test_exhaustive_recovery_sign (TYPE_2__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  test_exhaustive_recovery_verify (TYPE_2__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  test_exhaustive_sign (TYPE_2__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  test_exhaustive_verify (TYPE_2__*,TYPE_1__*,int) ; 

int main(void) {
    int i;
    secp256k1_gej groupj[EXHAUSTIVE_TEST_ORDER];
    secp256k1_ge group[EXHAUSTIVE_TEST_ORDER];

    /* Build context */
    secp256k1_context *ctx = secp256k1_context_create(SECP256K1_CONTEXT_SIGN | SECP256K1_CONTEXT_VERIFY);

    /* TODO set z = 1, then do num_tests runs with random z values */

    /* Generate the entire group */
    secp256k1_gej_set_infinity(&groupj[0]);
    secp256k1_ge_set_gej(&group[0], &groupj[0]);
    for (i = 1; i < EXHAUSTIVE_TEST_ORDER; i++) {
        /* Set a different random z-value for each Jacobian point */
        secp256k1_fe z;
        random_fe(&z);

        secp256k1_gej_add_ge(&groupj[i], &groupj[i - 1], &secp256k1_ge_const_g);
        secp256k1_ge_set_gej(&group[i], &groupj[i]);
        secp256k1_gej_rescale(&groupj[i], &z);

        /* Verify against ecmult_gen */
        {
            secp256k1_scalar scalar_i;
            secp256k1_gej generatedj;
            secp256k1_ge generated;

            secp256k1_scalar_set_int(&scalar_i, i);
            secp256k1_ecmult_gen(&ctx->ecmult_gen_ctx, &generatedj, &scalar_i);
            secp256k1_ge_set_gej(&generated, &generatedj);

            CHECK(group[i].infinity == 0);
            CHECK(generated.infinity == 0);
            CHECK(secp256k1_fe_equal_var(&generated.x, &group[i].x));
            CHECK(secp256k1_fe_equal_var(&generated.y, &group[i].y));
        }
    }

    /* Run the tests */
#ifdef USE_ENDOMORPHISM
    test_exhaustive_endomorphism(group, EXHAUSTIVE_TEST_ORDER);
#endif
    test_exhaustive_addition(group, groupj, EXHAUSTIVE_TEST_ORDER);
    test_exhaustive_ecmult(ctx, group, groupj, EXHAUSTIVE_TEST_ORDER);
    test_exhaustive_ecmult_multi(ctx, group, EXHAUSTIVE_TEST_ORDER);
    test_exhaustive_sign(ctx, group, EXHAUSTIVE_TEST_ORDER);
    test_exhaustive_verify(ctx, group, EXHAUSTIVE_TEST_ORDER);

#ifdef ENABLE_MODULE_RECOVERY
    test_exhaustive_recovery_sign(ctx, group, EXHAUSTIVE_TEST_ORDER);
    test_exhaustive_recovery_verify(ctx, group, EXHAUSTIVE_TEST_ORDER);
#endif

    secp256k1_context_destroy(ctx);
    return 0;
}