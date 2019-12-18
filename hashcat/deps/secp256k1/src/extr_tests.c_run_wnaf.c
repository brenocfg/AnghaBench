#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_12__ {int* d; TYPE_1__ member_0; } ;
typedef  TYPE_2__ secp256k1_scalar ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int) ; 
 int count ; 
 int /*<<< orphan*/  random_scalar_order (TYPE_2__*) ; 
 int secp256k1_scalar_cond_negate (TYPE_2__*,int) ; 
 int secp256k1_scalar_is_zero (TYPE_2__*) ; 
 int /*<<< orphan*/  secp256k1_scalar_set_int (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_constant_wnaf (TYPE_2__*,int) ; 
 int /*<<< orphan*/  test_constant_wnaf_negate (TYPE_2__*) ; 
 int /*<<< orphan*/  test_fixed_wnaf (TYPE_2__*,int) ; 
 int /*<<< orphan*/  test_fixed_wnaf_small () ; 
 int /*<<< orphan*/  test_wnaf (TYPE_2__*,int) ; 

void run_wnaf(void) {
    int i;
    secp256k1_scalar n = {{0}};

    /* Sanity check: 1 and 2 are the smallest odd and even numbers and should
     *               have easier-to-diagnose failure modes  */
    n.d[0] = 1;
    test_constant_wnaf(&n, 4);
    n.d[0] = 2;
    test_constant_wnaf(&n, 4);
    /* Test 0 */
    test_fixed_wnaf_small();
    /* Random tests */
    for (i = 0; i < count; i++) {
        random_scalar_order(&n);
        test_wnaf(&n, 4+(i%10));
        test_constant_wnaf_negate(&n);
        test_constant_wnaf(&n, 4 + (i % 10));
        test_fixed_wnaf(&n, 4 + (i % 10));
    }
    secp256k1_scalar_set_int(&n, 0);
    CHECK(secp256k1_scalar_cond_negate(&n, 1) == -1);
    CHECK(secp256k1_scalar_is_zero(&n));
    CHECK(secp256k1_scalar_cond_negate(&n, 0) == 1);
    CHECK(secp256k1_scalar_is_zero(&n));
}