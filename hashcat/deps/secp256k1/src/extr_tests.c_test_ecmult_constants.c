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
struct TYPE_2__ {int /*<<< orphan*/  ecmult_gen_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ) ; 
 TYPE_1__* ctx ; 
 int /*<<< orphan*/  ge_equals_gej (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_ecmult_gen (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_ge_const_g ; 
 int /*<<< orphan*/  secp256k1_ge_neg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_gej_add_ge (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_gej_is_infinity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_scalar_negate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_scalar_set_int (int /*<<< orphan*/ *,int) ; 

void test_ecmult_constants(void) {
    /* Test ecmult_gen() for [0..36) and [order-36..0). */
    secp256k1_scalar x;
    secp256k1_gej r;
    secp256k1_ge ng;
    int i;
    int j;
    secp256k1_ge_neg(&ng, &secp256k1_ge_const_g);
    for (i = 0; i < 36; i++ ) {
        secp256k1_scalar_set_int(&x, i);
        secp256k1_ecmult_gen(&ctx->ecmult_gen_ctx, &r, &x);
        for (j = 0; j < i; j++) {
            if (j == i - 1) {
                ge_equals_gej(&secp256k1_ge_const_g, &r);
            }
            secp256k1_gej_add_ge(&r, &r, &ng);
        }
        CHECK(secp256k1_gej_is_infinity(&r));
    }
    for (i = 1; i <= 36; i++ ) {
        secp256k1_scalar_set_int(&x, i);
        secp256k1_scalar_negate(&x, &x);
        secp256k1_ecmult_gen(&ctx->ecmult_gen_ctx, &r, &x);
        for (j = 0; j < i; j++) {
            if (j == i - 1) {
                ge_equals_gej(&ng, &r);
            }
            secp256k1_gej_add_ge(&r, &r, &secp256k1_ge_const_g);
        }
        CHECK(secp256k1_gej_is_infinity(&r));
    }
}