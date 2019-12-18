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
 int count ; 
 int /*<<< orphan*/  test_num_add_sub () ; 
 int /*<<< orphan*/  test_num_jacobi () ; 
 int /*<<< orphan*/  test_num_mod () ; 
 int /*<<< orphan*/  test_num_negate () ; 

void run_num_smalltests(void) {
    int i;
    for (i = 0; i < 100*count; i++) {
        test_num_negate();
        test_num_add_sub();
        test_num_mod();
        test_num_jacobi();
    }
}