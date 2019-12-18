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
 int /*<<< orphan*/  assert_is_ignored (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_ignore_add_rule (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_ignore_clear_internal_rules (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refute_is_ignored (char*) ; 

void test_ignore_status__automatically_ignore_bad_files(void)
{
	g_repo = cl_git_sandbox_init("empty_standard_repo");

	assert_is_ignored(".git");
	assert_is_ignored("this/file/.");
	assert_is_ignored("path/../funky");
	refute_is_ignored("path/whatever.c");

	cl_git_pass(git_ignore_add_rule(g_repo, "*.c\n"));

	assert_is_ignored(".git");
	assert_is_ignored("this/file/.");
	assert_is_ignored("path/../funky");
	assert_is_ignored("path/whatever.c");

	cl_git_pass(git_ignore_clear_internal_rules(g_repo));

	assert_is_ignored(".git");
	assert_is_ignored("this/file/.");
	assert_is_ignored("path/../funky");
	refute_is_ignored("path/whatever.c");
}