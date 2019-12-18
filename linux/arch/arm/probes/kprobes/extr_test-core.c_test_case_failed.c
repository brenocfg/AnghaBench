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
 int current_title ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  test_case_cleanup () ; 
 int test_case_run_count ; 

__attribute__((used)) static void test_case_failed(const char *message)
{
	test_case_cleanup();

	pr_err("FAIL: %s\n", message);
	pr_err("FAIL: Test %s\n", current_title);
	pr_err("FAIL: Scenario %d\n", test_case_run_count >> 1);
}