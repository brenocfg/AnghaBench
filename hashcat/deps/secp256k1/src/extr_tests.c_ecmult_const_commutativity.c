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
 int /*<<< orphan*/  ge_equals_ge (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  random_scalar_order_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_ecmult_const (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  secp256k1_ge_const_g ; 
 int /*<<< orphan*/  secp256k1_ge_set_gej (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ecmult_const_commutativity(void) {
    secp256k1_scalar a;
    secp256k1_scalar b;
    secp256k1_gej res1;
    secp256k1_gej res2;
    secp256k1_ge mid1;
    secp256k1_ge mid2;
    random_scalar_order_test(&a);
    random_scalar_order_test(&b);

    secp256k1_ecmult_const(&res1, &secp256k1_ge_const_g, &a, 256);
    secp256k1_ecmult_const(&res2, &secp256k1_ge_const_g, &b, 256);
    secp256k1_ge_set_gej(&mid1, &res1);
    secp256k1_ge_set_gej(&mid2, &res2);
    secp256k1_ecmult_const(&res1, &mid1, &b, 256);
    secp256k1_ecmult_const(&res2, &mid2, &a, 256);
    secp256k1_ge_set_gej(&mid1, &res1);
    secp256k1_ge_set_gej(&mid2, &res2);
    ge_equals_ge(&mid1, &mid2);
}