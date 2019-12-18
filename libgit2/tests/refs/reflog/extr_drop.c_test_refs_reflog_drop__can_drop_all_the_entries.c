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
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 scalar_t__ entrycount ; 
 int /*<<< orphan*/  g_reflog ; 
 int /*<<< orphan*/  git_reflog_drop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ git_reflog_entrycount (int /*<<< orphan*/ ) ; 

void test_refs_reflog_drop__can_drop_all_the_entries(void)
{
	cl_assert(--entrycount > 0);

	do 	{
		cl_git_pass(git_reflog_drop(g_reflog, 0, 1));
	} while (--entrycount > 0);

	cl_git_pass(git_reflog_drop(g_reflog, 0, 1));

	cl_assert_equal_i(0, (int)git_reflog_entrycount(g_reflog));
}