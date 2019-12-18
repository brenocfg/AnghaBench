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

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int) ; 
 int WNAF_SIZE (int) ; 

void test_fixed_wnaf_small_helper(int *wnaf, int *wnaf_expected, int w) {
    int i;
    for (i = WNAF_SIZE(w)-1; i >= 8; --i) {
        CHECK(wnaf[i] == 0);
    }
    for (i = 7; i >= 0; --i) {
        CHECK(wnaf[i] == wnaf_expected[i]);
    }
}