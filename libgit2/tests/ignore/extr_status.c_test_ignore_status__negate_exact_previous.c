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
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_ignore_path_is_ignored (int*,int /*<<< orphan*/ ,char*) ; 

void test_ignore_status__negate_exact_previous(void)
{
	int ignored;

	g_repo = cl_git_sandbox_init("empty_standard_repo");

	cl_git_mkfile("empty_standard_repo/.gitignore", "*.com\ntags\n!tags/\n.buildpath");
	cl_git_mkfile("empty_standard_repo/.buildpath", "");
	cl_git_pass(git_ignore_path_is_ignored(&ignored, g_repo, ".buildpath"));
	cl_assert_equal_i(1, ignored);
}