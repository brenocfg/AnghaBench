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
typedef  int /*<<< orphan*/  secp256k1_num ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int) ; 
 int /*<<< orphan*/  random_num_negate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  random_num_order_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_num_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_num_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int secp256k1_num_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ secp256k1_num_is_neg (int /*<<< orphan*/ *) ; 
 int secp256k1_num_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_num_negate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_num_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void test_num_negate(void) {
    secp256k1_num n1;
    secp256k1_num n2;
    random_num_order_test(&n1); /* n1 = R */
    random_num_negate(&n1);
    secp256k1_num_copy(&n2, &n1); /* n2 = R */
    secp256k1_num_sub(&n1, &n2, &n1); /* n1 = n2-n1 = 0 */
    CHECK(secp256k1_num_is_zero(&n1));
    secp256k1_num_copy(&n1, &n2); /* n1 = R */
    secp256k1_num_negate(&n1); /* n1 = -R */
    CHECK(!secp256k1_num_is_zero(&n1));
    secp256k1_num_add(&n1, &n2, &n1); /* n1 = n2+n1 = 0 */
    CHECK(secp256k1_num_is_zero(&n1));
    secp256k1_num_copy(&n1, &n2); /* n1 = R */
    secp256k1_num_negate(&n1); /* n1 = -R */
    CHECK(secp256k1_num_is_neg(&n1) != secp256k1_num_is_neg(&n2));
    secp256k1_num_negate(&n1); /* n1 = R */
    CHECK(secp256k1_num_eq(&n1, &n2));
}