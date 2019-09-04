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
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_reference_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  refs_foreach_cancel_cb ; 
 int /*<<< orphan*/  repo ; 

void test_refs_iterator__foreach_can_cancel(void)
{
	int cancel_after = 3;
	cl_git_fail_with(
		git_reference_foreach(repo, refs_foreach_cancel_cb, &cancel_after),
		-333);
	cl_assert_equal_i(0, cancel_after);
}