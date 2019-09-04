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
typedef  int /*<<< orphan*/  git_remote ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_EAMBIGUOUS ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_branch_remote_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/ * git_error_last () ; 
 int /*<<< orphan*/  git_remote_create_with_fetchspec (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  remote_tracking_branch_name ; 

void test_refs_branches_remote__ambiguous_remote_returns_error(void)
{
	git_remote *remote;
	git_buf buf;

	/* Create the remote */
	cl_git_pass(git_remote_create_with_fetchspec(&remote, g_repo, "addtest", "http://github.com/libgit2/libgit2", "refs/heads/*:refs/remotes/test/*"));

	git_remote_free(remote);

	git_error_clear();
	memset(&buf, 0, sizeof(git_buf));
	cl_git_fail_with(git_branch_remote_name(&buf, g_repo, remote_tracking_branch_name), GIT_EAMBIGUOUS);
	cl_assert(git_error_last() != NULL);
}