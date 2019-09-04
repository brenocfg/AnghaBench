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
typedef  int /*<<< orphan*/  git_annotated_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_RESET_SOFT ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_annotated_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_annotated_commit_from_revspec (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reset_from_annotated (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  reflog_check (int /*<<< orphan*/ ,char*,int,char*,char const*) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  target ; 

void test_reset_soft__reflog_is_correct(void)
{
	git_annotated_commit *annotated;
	const char *exp_msg = "checkout: moving from br2 to master";
	const char *master_msg = "commit: checking in";

	reflog_check(repo, "HEAD", 7, "yoram.harmelin@gmail.com", exp_msg);
	reflog_check(repo, "refs/heads/master", 2, "yoram.harmelin@gmail.com", master_msg);

	/* Branch not moving, no reflog entry */
	cl_git_pass(git_revparse_single(&target, repo, "HEAD^{commit}"));
	cl_git_pass(git_reset(repo, target, GIT_RESET_SOFT, NULL));
	reflog_check(repo, "HEAD", 7, "yoram.harmelin@gmail.com", exp_msg);
	reflog_check(repo, "refs/heads/master", 2, "yoram.harmelin@gmail.com", master_msg);
	git_object_free(target);

	/* Moved branch, expect id in message */
	exp_msg = "reset: moving to be3563ae3f795b2b4353bcce3a527ad0a4f7f644";
	cl_git_pass(git_revparse_single(&target, repo, "HEAD~^{commit}"));
	cl_git_pass(git_reset(repo, target, GIT_RESET_SOFT, NULL));
	reflog_check(repo, "HEAD", 8, "yoram.harmelin@gmail.com", exp_msg);
	reflog_check(repo, "refs/heads/master", 3, NULL, exp_msg);

	/* Moved branch, expect message with annotated string */
	exp_msg = "reset: moving to HEAD~^{commit}";
	cl_git_pass(git_annotated_commit_from_revspec(&annotated, repo, "HEAD~^{commit}"));
	cl_git_pass(git_reset_from_annotated(repo, annotated, GIT_RESET_SOFT, NULL));
	reflog_check(repo, "HEAD", 9, "yoram.harmelin@gmail.com", exp_msg);
	reflog_check(repo, "refs/heads/master", 4, NULL, exp_msg);

	git_annotated_commit_free(annotated);
}