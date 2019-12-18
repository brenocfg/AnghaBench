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
 int /*<<< orphan*/  GIT_RESET_HARD ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_mkfile (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_joinpath (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int git_path_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  p_unlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  target ; 

void test_reset_hard__cleans_up_merge(void)
{
	git_buf merge_head_path = GIT_BUF_INIT,
		merge_msg_path = GIT_BUF_INIT,
		merge_mode_path = GIT_BUF_INIT,
		orig_head_path = GIT_BUF_INIT;

	cl_git_pass(git_buf_joinpath(&merge_head_path, git_repository_path(repo), "MERGE_HEAD"));
	cl_git_mkfile(git_buf_cstr(&merge_head_path), "beefbeefbeefbeefbeefbeefbeefbeefbeefbeef\n");

	cl_git_pass(git_buf_joinpath(&merge_msg_path, git_repository_path(repo), "MERGE_MSG"));
	cl_git_mkfile(git_buf_cstr(&merge_msg_path), "Merge commit 0017bd4ab1ec30440b17bae1680cff124ab5f1f6\n");

	cl_git_pass(git_buf_joinpath(&merge_mode_path, git_repository_path(repo), "MERGE_MODE"));
	cl_git_mkfile(git_buf_cstr(&merge_mode_path), "");

	cl_git_pass(git_buf_joinpath(&orig_head_path, git_repository_path(repo), "ORIG_HEAD"));
	cl_git_mkfile(git_buf_cstr(&orig_head_path), "0017bd4ab1ec30440b17bae1680cff124ab5f1f6");

	cl_git_pass(git_revparse_single(&target, repo, "0017bd4"));
	cl_git_pass(git_reset(repo, target, GIT_RESET_HARD, NULL));

	cl_assert(!git_path_exists(git_buf_cstr(&merge_head_path)));
	cl_assert(!git_path_exists(git_buf_cstr(&merge_msg_path)));
	cl_assert(!git_path_exists(git_buf_cstr(&merge_mode_path)));

	cl_assert(git_path_exists(git_buf_cstr(&orig_head_path)));
	cl_git_pass(p_unlink(git_buf_cstr(&orig_head_path)));

	git_buf_dispose(&merge_head_path);
	git_buf_dispose(&merge_msg_path);
	git_buf_dispose(&merge_mode_path);
	git_buf_dispose(&orig_head_path);
}