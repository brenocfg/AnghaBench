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
 int WNAF_SIZE (int) ; 
 int /*<<< orphan*/  secp256k1_scalar_set_int (int /*<<< orphan*/ *,int) ; 
 int secp256k1_wnaf_fixed (int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_fixed_wnaf_small_helper (int*,int*,int) ; 

void test_fixed_wnaf_small(void) {
    int w = 4;
    int wnaf[256] = {0};
    int i;
    int skew;
    secp256k1_scalar num;

    secp256k1_scalar_set_int(&num, 0);
    skew = secp256k1_wnaf_fixed(wnaf, &num, w);
    for (i = WNAF_SIZE(w)-1; i >= 0; --i) {
        int v = wnaf[i];
        CHECK(v == 0);
    }
    CHECK(skew == 0);

    secp256k1_scalar_set_int(&num, 1);
    skew = secp256k1_wnaf_fixed(wnaf, &num, w);
    for (i = WNAF_SIZE(w)-1; i >= 1; --i) {
        int v = wnaf[i];
        CHECK(v == 0);
    }
    CHECK(wnaf[0] == 1);
    CHECK(skew == 0);

    {
        int wnaf_expected[8] = { 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf };
        secp256k1_scalar_set_int(&num, 0xffffffff);
        skew = secp256k1_wnaf_fixed(wnaf, &num, w);
        test_fixed_wnaf_small_helper(wnaf, wnaf_expected, w);
        CHECK(skew == 0);
    }
    {
        int wnaf_expected[8] = { -1, -1, -1, -1, -1, -1, -1, 0xf };
        secp256k1_scalar_set_int(&num, 0xeeeeeeee);
        skew = secp256k1_wnaf_fixed(wnaf, &num, w);
        test_fixed_wnaf_small_helper(wnaf, wnaf_expected, w);
        CHECK(skew == 1);
    }
    {
        int wnaf_expected[8] = { 1, 0, 1, 0, 1, 0, 1, 0 };
        secp256k1_scalar_set_int(&num, 0x01010101);
        skew = secp256k1_wnaf_fixed(wnaf, &num, w);
        test_fixed_wnaf_small_helper(wnaf, wnaf_expected, w);
        CHECK(skew == 0);
    }
    {
        int wnaf_expected[8] = { -0xf, 0, 0xf, -0xf, 0, 0xf, 1, 0 };
        secp256k1_scalar_set_int(&num, 0x01ef1ef1);
        skew = secp256k1_wnaf_fixed(wnaf, &num, w);
        test_fixed_wnaf_small_helper(wnaf, wnaf_expected, w);
        CHECK(skew == 0);
    }
}