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
 int /*<<< orphan*/  SECP256K1_SCALAR_CONST (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ge_equals_ge (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  random_group_element_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_ecmult_const (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  secp256k1_ge_is_infinity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_ge_set_gej (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_gej_neg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_scalar_negate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ecmult_const_mult_zero_one(void) {
    secp256k1_scalar zero = SECP256K1_SCALAR_CONST(0, 0, 0, 0, 0, 0, 0, 0);
    secp256k1_scalar one = SECP256K1_SCALAR_CONST(0, 0, 0, 0, 0, 0, 0, 1);
    secp256k1_scalar negone;
    secp256k1_gej res1;
    secp256k1_ge res2;
    secp256k1_ge point;
    secp256k1_scalar_negate(&negone, &one);

    random_group_element_test(&point);
    secp256k1_ecmult_const(&res1, &point, &zero, 3);
    secp256k1_ge_set_gej(&res2, &res1);
    CHECK(secp256k1_ge_is_infinity(&res2));
    secp256k1_ecmult_const(&res1, &point, &one, 2);
    secp256k1_ge_set_gej(&res2, &res1);
    ge_equals_ge(&res2, &point);
    secp256k1_ecmult_const(&res1, &point, &negone, 256);
    secp256k1_gej_neg(&res1, &res1);
    secp256k1_ge_set_gej(&res2, &res1);
    ge_equals_ge(&res2, &point);
}