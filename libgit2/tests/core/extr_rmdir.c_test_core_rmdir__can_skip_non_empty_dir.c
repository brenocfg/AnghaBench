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
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_RMDIR_REMOVE_FILES ; 
 int /*<<< orphan*/  GIT_RMDIR_SKIP_NONEMPTY ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_mkfile (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  empty_tmp_dir ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_joinpath (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_futils_rmdir_r (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_path_exists (int /*<<< orphan*/ ) ; 

void test_core_rmdir__can_skip_non_empty_dir(void)
{
	git_buf file = GIT_BUF_INIT;

	cl_git_pass(git_buf_joinpath(&file, empty_tmp_dir, "/two/file.txt"));

	cl_git_mkfile(git_buf_cstr(&file), "dummy");

	cl_git_pass(git_futils_rmdir_r(empty_tmp_dir, NULL, GIT_RMDIR_SKIP_NONEMPTY));
	cl_assert(git_path_exists(git_buf_cstr(&file)) == true);

	cl_git_pass(git_futils_rmdir_r(empty_tmp_dir, NULL, GIT_RMDIR_REMOVE_FILES));
	cl_assert(git_path_exists(empty_tmp_dir) == false);

	git_buf_dispose(&file);
}