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
 int /*<<< orphan*/  GIT_EUNMERGED ; 
 int /*<<< orphan*/  GIT_RESET_SOFT ; 
 int /*<<< orphan*/  KNOWN_COMMIT_IN_BARE_REPO ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_joinpath (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_repository_detach_head (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_unlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  target ; 

void test_reset_soft__fails_when_merging(void)
{
	git_buf merge_head_path = GIT_BUF_INIT;

	cl_git_pass(git_repository_detach_head(repo));
	cl_git_pass(git_buf_joinpath(&merge_head_path, git_repository_path(repo), "MERGE_HEAD"));
	cl_git_mkfile(git_buf_cstr(&merge_head_path), "beefbeefbeefbeefbeefbeefbeefbeefbeefbeef\n");

	cl_git_pass(git_revparse_single(&target, repo, KNOWN_COMMIT_IN_BARE_REPO));

	cl_assert_equal_i(GIT_EUNMERGED, git_reset(repo, target, GIT_RESET_SOFT, NULL));
	cl_git_pass(p_unlink(git_buf_cstr(&merge_head_path)));

	git_buf_dispose(&merge_head_path);
}