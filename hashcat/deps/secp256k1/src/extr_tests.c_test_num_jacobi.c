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
typedef  int /*<<< orphan*/  secp256k1_num ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int) ; 
 int /*<<< orphan*/  random_scalar_order_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_num_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ secp256k1_num_is_zero (int /*<<< orphan*/ *) ; 
 int secp256k1_num_jacobi (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_num_mod (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_num_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_scalar_get_num (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_scalar_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_scalar_order_get_num (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_scalar_set_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  secp256k1_scalar_sqr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void test_num_jacobi(void) {
    secp256k1_scalar sqr;
    secp256k1_scalar small;
    secp256k1_scalar five;  /* five is not a quadratic residue */
    secp256k1_num order, n;
    int i;
    /* squares mod 5 are 1, 4 */
    const int jacobi5[10] = { 0, 1, -1, -1, 1, 0, 1, -1, -1, 1 };

    /* check some small values with 5 as the order */
    secp256k1_scalar_set_int(&five, 5);
    secp256k1_scalar_get_num(&order, &five);
    for (i = 0; i < 10; ++i) {
        secp256k1_scalar_set_int(&small, i);
        secp256k1_scalar_get_num(&n, &small);
        CHECK(secp256k1_num_jacobi(&n, &order) == jacobi5[i]);
    }

    /** test large values with 5 as group order */
    secp256k1_scalar_get_num(&order, &five);
    /* we first need a scalar which is not a multiple of 5 */
    do {
        secp256k1_num fiven;
        random_scalar_order_test(&sqr);
        secp256k1_scalar_get_num(&fiven, &five);
        secp256k1_scalar_get_num(&n, &sqr);
        secp256k1_num_mod(&n, &fiven);
    } while (secp256k1_num_is_zero(&n));
    /* next force it to be a residue. 2 is a nonresidue mod 5 so we can
     * just multiply by two, i.e. add the number to itself */
    if (secp256k1_num_jacobi(&n, &order) == -1) {
        secp256k1_num_add(&n, &n, &n);
    }

    /* test residue */
    CHECK(secp256k1_num_jacobi(&n, &order) == 1);
    /* test nonresidue */
    secp256k1_num_add(&n, &n, &n);
    CHECK(secp256k1_num_jacobi(&n, &order) == -1);

    /** test with secp group order as order */
    secp256k1_scalar_order_get_num(&order);
    random_scalar_order_test(&sqr);
    secp256k1_scalar_sqr(&sqr, &sqr);
    /* test residue */
    secp256k1_scalar_get_num(&n, &sqr);
    CHECK(secp256k1_num_jacobi(&n, &order) == 1);
    /* test nonresidue */
    secp256k1_scalar_mul(&sqr, &sqr, &five);
    secp256k1_scalar_get_num(&n, &sqr);
    CHECK(secp256k1_num_jacobi(&n, &order) == -1);
    /* test multiple of the order*/
    CHECK(secp256k1_num_jacobi(&order, &order) == 0);

    /* check one less than the order */
    secp256k1_scalar_set_int(&small, 1);
    secp256k1_scalar_get_num(&n, &small);
    secp256k1_num_sub(&n, &order, &n);
    CHECK(secp256k1_num_jacobi(&n, &order) == 1);  /* sage confirms this is 1 */
}