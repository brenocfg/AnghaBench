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

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int) ; 
 int secp256k1_scalar_cond_negate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int secp256k1_scalar_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_scalar_get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  secp256k1_scalar_is_even (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_scalar_negate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void test_constant_wnaf_negate(const secp256k1_scalar *number) {
    secp256k1_scalar neg1 = *number;
    secp256k1_scalar neg2 = *number;
    int sign1 = 1;
    int sign2 = 1;

    if (!secp256k1_scalar_get_bits(&neg1, 0, 1)) {
        secp256k1_scalar_negate(&neg1, &neg1);
        sign1 = -1;
    }
    sign2 = secp256k1_scalar_cond_negate(&neg2, secp256k1_scalar_is_even(&neg2));
    CHECK(sign1 == sign2);
    CHECK(secp256k1_scalar_eq(&neg1, &neg2));
}