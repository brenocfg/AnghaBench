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

void test_ignore_status__filename_with_cr(void)
{
	int ignored;

	g_repo = cl_git_sandbox_init("empty_standard_repo");
	cl_git_mkfile("empty_standard_repo/.gitignore", "Icon\r\r\n");

	cl_git_pass(git_ignore_path_is_ignored(&ignored, g_repo, "Icon\r"));
	cl_assert_equal_i(1, ignored);

	cl_git_mkfile("empty_standard_repo/.gitignore", "Ico\rn\n");
	cl_git_pass(git_ignore_path_is_ignored(&ignored, g_repo, "Ico\rn"));
	cl_assert_equal_i(1, ignored);

	cl_git_mkfile("empty_standard_repo/.gitignore", "Ico\rn\r\n");
	cl_git_pass(git_ignore_path_is_ignored(&ignored, g_repo, "Ico\rn"));
	cl_assert_equal_i(1, ignored);
	cl_git_pass(git_ignore_path_is_ignored(&ignored, g_repo, "Ico\rn\r"));
	cl_assert_equal_i(0, ignored);

	cl_git_mkfile("empty_standard_repo/.gitignore", "Ico\rn\r\r\n");
	cl_git_pass(git_ignore_path_is_ignored(&ignored, g_repo, "Ico\rn\r"));
	cl_assert_equal_i(1, ignored);
	cl_git_pass(git_ignore_path_is_ignored(&ignored, g_repo, "Icon\r"));
	cl_assert_equal_i(0, ignored);

	cl_git_mkfile("empty_standard_repo/.gitignore", "Icon\r\n");
	cl_git_pass(git_ignore_path_is_ignored(&ignored, g_repo, "Icon\r"));
	cl_assert_equal_i(0, ignored);
	cl_git_pass(git_ignore_path_is_ignored(&ignored, g_repo, "Icon"));
	cl_assert_equal_i(1, ignored);
}