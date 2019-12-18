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
 int /*<<< orphan*/  test_rand_bits (int,size_t) ; 

void run_rand_bits(void) {
    size_t b;
    test_rand_bits(1, 32);
    for (b = 1; b <= 32; b++) {
        test_rand_bits(0, b);
    }
}