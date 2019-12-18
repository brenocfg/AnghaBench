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
 int /*<<< orphan*/  random_num_negate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  random_num_order_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_num_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int secp256k1_num_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int secp256k1_num_is_one (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_num_negate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_num_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ secp256k1_rand_bits (int) ; 
 int /*<<< orphan*/  secp256k1_scalar_get_num (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_scalar_set_int (int /*<<< orphan*/ *,int) ; 

void test_num_add_sub(void) {
    int i;
    secp256k1_scalar s;
    secp256k1_num n1;
    secp256k1_num n2;
    secp256k1_num n1p2, n2p1, n1m2, n2m1;
    random_num_order_test(&n1); /* n1 = R1 */
    if (secp256k1_rand_bits(1)) {
        random_num_negate(&n1);
    }
    random_num_order_test(&n2); /* n2 = R2 */
    if (secp256k1_rand_bits(1)) {
        random_num_negate(&n2);
    }
    secp256k1_num_add(&n1p2, &n1, &n2); /* n1p2 = R1 + R2 */
    secp256k1_num_add(&n2p1, &n2, &n1); /* n2p1 = R2 + R1 */
    secp256k1_num_sub(&n1m2, &n1, &n2); /* n1m2 = R1 - R2 */
    secp256k1_num_sub(&n2m1, &n2, &n1); /* n2m1 = R2 - R1 */
    CHECK(secp256k1_num_eq(&n1p2, &n2p1));
    CHECK(!secp256k1_num_eq(&n1p2, &n1m2));
    secp256k1_num_negate(&n2m1); /* n2m1 = -R2 + R1 */
    CHECK(secp256k1_num_eq(&n2m1, &n1m2));
    CHECK(!secp256k1_num_eq(&n2m1, &n1));
    secp256k1_num_add(&n2m1, &n2m1, &n2); /* n2m1 = -R2 + R1 + R2 = R1 */
    CHECK(secp256k1_num_eq(&n2m1, &n1));
    CHECK(!secp256k1_num_eq(&n2p1, &n1));
    secp256k1_num_sub(&n2p1, &n2p1, &n2); /* n2p1 = R2 + R1 - R2 = R1 */
    CHECK(secp256k1_num_eq(&n2p1, &n1));

    /* check is_one */
    secp256k1_scalar_set_int(&s, 1);
    secp256k1_scalar_get_num(&n1, &s);
    CHECK(secp256k1_num_is_one(&n1));
    /* check that 2^n + 1 is never 1 */
    secp256k1_scalar_get_num(&n2, &s);
    for (i = 0; i < 250; ++i) {
        secp256k1_num_add(&n1, &n1, &n1);    /* n1 *= 2 */
        secp256k1_num_add(&n1p2, &n1, &n2);  /* n1p2 = n1 + 1 */
        CHECK(!secp256k1_num_is_one(&n1p2));
    }
}