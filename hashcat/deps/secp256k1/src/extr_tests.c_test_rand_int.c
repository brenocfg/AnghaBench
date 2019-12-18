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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int) ; 
 int secp256k1_rand_int (int) ; 

void test_rand_int(uint32_t range, uint32_t subrange) {
    /* (1-1/subrange)^rounds < 1/10^9 */
    int rounds = (subrange * 2073) / 100;
    int i;
    uint64_t x = 0;
    CHECK((range % subrange) == 0);
    for (i = 0; i < rounds; i++) {
        uint32_t r = secp256k1_rand_int(range);
        CHECK(r < range);
        r = r % subrange;
        x |= (((uint64_t)1) << r);
    }
    /* Test that the lower subrange bits of x are 1. */
    CHECK(((~x) << (64 - subrange)) == 0);
}