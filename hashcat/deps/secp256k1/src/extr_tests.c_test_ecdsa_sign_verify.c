#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  secp256k1_scalar ;
typedef  int /*<<< orphan*/  secp256k1_gej ;
typedef  int /*<<< orphan*/  secp256k1_ge ;
struct TYPE_2__ {int /*<<< orphan*/  ecmult_ctx; int /*<<< orphan*/  ecmult_gen_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int) ; 
 TYPE_1__* ctx ; 
 int /*<<< orphan*/  random_scalar_order_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  random_sign (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int secp256k1_ecdsa_sig_verify (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_ecmult_gen (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_ge_set_gej (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int secp256k1_rand_bits (int) ; 
 int /*<<< orphan*/  secp256k1_scalar_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_scalar_set_int (int /*<<< orphan*/ *,int) ; 

void test_ecdsa_sign_verify(void) {
    secp256k1_gej pubj;
    secp256k1_ge pub;
    secp256k1_scalar one;
    secp256k1_scalar msg, key;
    secp256k1_scalar sigr, sigs;
    int recid;
    int getrec;
    random_scalar_order_test(&msg);
    random_scalar_order_test(&key);
    secp256k1_ecmult_gen(&ctx->ecmult_gen_ctx, &pubj, &key);
    secp256k1_ge_set_gej(&pub, &pubj);
    getrec = secp256k1_rand_bits(1);
    random_sign(&sigr, &sigs, &key, &msg, getrec?&recid:NULL);
    if (getrec) {
        CHECK(recid >= 0 && recid < 4);
    }
    CHECK(secp256k1_ecdsa_sig_verify(&ctx->ecmult_ctx, &sigr, &sigs, &pub, &msg));
    secp256k1_scalar_set_int(&one, 1);
    secp256k1_scalar_add(&msg, &msg, &one);
    CHECK(!secp256k1_ecdsa_sig_verify(&ctx->ecmult_ctx, &sigr, &sigs, &pub, &msg));
}