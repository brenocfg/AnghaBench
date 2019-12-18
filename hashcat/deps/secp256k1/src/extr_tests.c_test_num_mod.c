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
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  random_scalar_order_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_num_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_num_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_num_mod (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_scalar_get_num (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_scalar_set_int (int /*<<< orphan*/ *,int) ; 

void test_num_mod(void) {
    int i;
    secp256k1_scalar s;
    secp256k1_num order, n;

    /* check that 0 mod anything is 0 */
    random_scalar_order_test(&s);
    secp256k1_scalar_get_num(&order, &s);
    secp256k1_scalar_set_int(&s, 0);
    secp256k1_scalar_get_num(&n, &s);
    secp256k1_num_mod(&n, &order);
    CHECK(secp256k1_num_is_zero(&n));

    /* check that anything mod 1 is 0 */
    secp256k1_scalar_set_int(&s, 1);
    secp256k1_scalar_get_num(&order, &s);
    secp256k1_scalar_get_num(&n, &s);
    secp256k1_num_mod(&n, &order);
    CHECK(secp256k1_num_is_zero(&n));

    /* check that increasing the number past 2^256 does not break this */
    random_scalar_order_test(&s);
    secp256k1_scalar_get_num(&n, &s);
    /* multiply by 2^8, which'll test this case with high probability */
    for (i = 0; i < 8; ++i) {
        secp256k1_num_add(&n, &n, &n);
    }
    secp256k1_num_mod(&n, &order);
    CHECK(secp256k1_num_is_zero(&n));
}