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
 int /*<<< orphan*/  malloc_printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reentrancy ; 
 int /*<<< orphan*/  reentrancy_t_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * test_counts ; 
 int /*<<< orphan*/  test_name ; 
 size_t test_status ; 
 int /*<<< orphan*/  test_status_string (size_t) ; 

void
p_test_fini(void) {
	test_counts[test_status]++;
	malloc_printf("%s (%s): %s\n", test_name, reentrancy_t_str(reentrancy),
	    test_status_string(test_status));
}