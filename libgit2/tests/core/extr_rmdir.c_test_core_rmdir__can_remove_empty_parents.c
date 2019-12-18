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
 int GIT_RMDIR_EMPTY_HIERARCHY ; 
 int GIT_RMDIR_EMPTY_PARENTS ; 
 int GIT_RMDIR_REMOVE_FILES ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 char* empty_tmp_dir ; 
 char* git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_joinpath (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  git_buf_rtruncate_at_char (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  git_futils_rmdir_r (char*,char*,int) ; 
 int git_path_exists (char*) ; 
 int git_path_isfile (char*) ; 

void test_core_rmdir__can_remove_empty_parents(void)
{
	git_buf file = GIT_BUF_INIT;

	cl_git_pass(
		git_buf_joinpath(&file, empty_tmp_dir, "/one/two_two/three/file.txt"));
	cl_git_mkfile(git_buf_cstr(&file), "dummy");
	cl_assert(git_path_isfile(git_buf_cstr(&file)));

	cl_git_pass(git_futils_rmdir_r("one/two_two/three/file.txt", empty_tmp_dir,
		GIT_RMDIR_REMOVE_FILES | GIT_RMDIR_EMPTY_PARENTS));

	cl_assert(!git_path_exists(git_buf_cstr(&file)));

	git_buf_rtruncate_at_char(&file, '/'); /* three (only contained file.txt) */
	cl_assert(!git_path_exists(git_buf_cstr(&file)));

	git_buf_rtruncate_at_char(&file, '/'); /* two_two (only contained three) */
	cl_assert(!git_path_exists(git_buf_cstr(&file)));

	git_buf_rtruncate_at_char(&file, '/'); /* one (contained two_one also) */
	cl_assert(git_path_exists(git_buf_cstr(&file)));

	cl_assert(git_path_exists(empty_tmp_dir) == true);

	git_buf_dispose(&file);

	cl_git_pass(git_futils_rmdir_r(empty_tmp_dir, NULL, GIT_RMDIR_EMPTY_HIERARCHY));
}