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
typedef  int /*<<< orphan*/  secp256k1_fe ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int) ; 
 int /*<<< orphan*/  secp256k1_fe_add (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ secp256k1_fe_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_fe_negate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  secp256k1_fe_normalize (int /*<<< orphan*/ *) ; 
 int secp256k1_fe_sqrt (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

void test_sqrt(const secp256k1_fe *a, const secp256k1_fe *k) {
    secp256k1_fe r1, r2;
    int v = secp256k1_fe_sqrt(&r1, a);
    CHECK((v == 0) == (k == NULL));

    if (k != NULL) {
        /* Check that the returned root is +/- the given known answer */
        secp256k1_fe_negate(&r2, &r1, 1);
        secp256k1_fe_add(&r1, k); secp256k1_fe_add(&r2, k);
        secp256k1_fe_normalize(&r1); secp256k1_fe_normalize(&r2);
        CHECK(secp256k1_fe_is_zero(&r1) || secp256k1_fe_is_zero(&r2));
    }
}