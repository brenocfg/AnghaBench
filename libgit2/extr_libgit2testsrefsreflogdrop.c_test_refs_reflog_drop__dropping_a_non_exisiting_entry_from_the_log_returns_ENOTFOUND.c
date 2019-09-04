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
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_sz (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entrycount ; 
 int /*<<< orphan*/  g_reflog ; 
 int /*<<< orphan*/  git_reflog_drop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reflog_entrycount (int /*<<< orphan*/ ) ; 

void test_refs_reflog_drop__dropping_a_non_exisiting_entry_from_the_log_returns_ENOTFOUND(void)
{
	cl_assert_equal_i(GIT_ENOTFOUND, git_reflog_drop(g_reflog, entrycount, 0));

	cl_assert_equal_sz(entrycount, git_reflog_entrycount(g_reflog));
}