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

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SECP256K1_GE_CONST (int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  SECP256K1_SCALAR_CONST (int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  ge_equals_gej (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_ecmult_const (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  secp256k1_ge_is_valid_var (int /*<<< orphan*/ *) ; 

void ecmult_const_random_mult(void) {
    /* random starting point A (on the curve) */
    secp256k1_ge a = SECP256K1_GE_CONST(
        0x6d986544, 0x57ff52b8, 0xcf1b8126, 0x5b802a5b,
        0xa97f9263, 0xb1e88044, 0x93351325, 0x91bc450a,
        0x535c59f7, 0x325e5d2b, 0xc391fbe8, 0x3c12787c,
        0x337e4a98, 0xe82a9011, 0x0123ba37, 0xdd769c7d
    );
    /* random initial factor xn */
    secp256k1_scalar xn = SECP256K1_SCALAR_CONST(
        0x649d4f77, 0xc4242df7, 0x7f2079c9, 0x14530327,
        0xa31b876a, 0xd2d8ce2a, 0x2236d5c6, 0xd7b2029b
    );
    /* expected xn * A (from sage) */
    secp256k1_ge expected_b = SECP256K1_GE_CONST(
        0x23773684, 0x4d209dc7, 0x098a786f, 0x20d06fcd,
        0x070a38bf, 0xc11ac651, 0x03004319, 0x1e2a8786,
        0xed8c3b8e, 0xc06dd57b, 0xd06ea66e, 0x45492b0f,
        0xb84e4e1b, 0xfb77e21f, 0x96baae2a, 0x63dec956
    );
    secp256k1_gej b;
    secp256k1_ecmult_const(&b, &a, &xn, 256);

    CHECK(secp256k1_ge_is_valid_var(&a));
    ge_equals_gej(&expected_b, &b);
}