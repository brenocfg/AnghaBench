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
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int git_config_get_bool (int*,int /*<<< orphan*/ *,char*) ; 
 int git_ignore_path_is_ignored (int*,int /*<<< orphan*/ ,char*) ; 
 int git_repository_config_snapshot (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int p_mkdir (char*,int) ; 

void test_ignore_status__subdir_doesnt_match_above(void)
{
	int ignored, icase = 0, error;
	git_config *cfg;

	g_repo = cl_git_sandbox_init("empty_standard_repo");

	cl_git_pass(git_repository_config_snapshot(&cfg, g_repo));
	error = git_config_get_bool(&icase, cfg, "core.ignorecase");
	git_config_free(cfg);
	if (error == GIT_ENOTFOUND)
		error = 0;

	cl_git_pass(error);

	cl_git_pass(p_mkdir("empty_standard_repo/src", 0777));
	cl_git_pass(p_mkdir("empty_standard_repo/src/src", 0777));
	cl_git_mkfile("empty_standard_repo/src/.gitignore", "src\n");
	cl_git_mkfile("empty_standard_repo/.gitignore", "");

	cl_git_pass(git_ignore_path_is_ignored(&ignored, g_repo, "src/test.txt"));
	cl_assert_equal_i(0, ignored);
	cl_git_pass(git_ignore_path_is_ignored(&ignored, g_repo, "src/src/test.txt"));
	cl_assert_equal_i(1, ignored);
	cl_git_pass(git_ignore_path_is_ignored(&ignored, g_repo, "src/foo/test.txt"));
	cl_assert_equal_i(0, ignored);

	cl_git_pass(git_ignore_path_is_ignored(&ignored, g_repo, "SRC/src/test.txt"));
	cl_assert_equal_i(icase, ignored);
	cl_git_pass(git_ignore_path_is_ignored(&ignored, g_repo, "src/SRC/test.txt"));
	cl_assert_equal_i(icase, ignored);
}