#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_reference ;
struct TYPE_8__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;
struct TYPE_9__ {int bare; } ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_set_cleanup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cleanup_repository ; 
 TYPE_2__ g_options ; 
 int /*<<< orphan*/  g_repo_cloned ; 
 int /*<<< orphan*/  git_branch_remote_name (TYPE_1__*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_branch_upstream_name (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_clone (int /*<<< orphan*/ *,char*,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*) ; 

void test_clone_empty__can_clone_an_empty_local_repo_barely(void)
{
	char *local_name = "refs/heads/master";
	const char *expected_tracked_branch_name = "refs/remotes/origin/master";
	const char *expected_remote_name = "origin";
	git_buf buf = GIT_BUF_INIT;
	git_reference *ref;

	cl_set_cleanup(&cleanup_repository, "./empty");

	g_options.bare = true;
	cl_git_pass(git_clone(&g_repo_cloned, "./empty_bare.git", "./empty", &g_options));

	/* Although the HEAD is unborn... */
	cl_assert_equal_i(GIT_ENOTFOUND, git_reference_lookup(&ref, g_repo_cloned, local_name));

	/* ...one can still retrieve the name of the remote tracking reference */
	cl_git_pass(git_branch_upstream_name(&buf, g_repo_cloned, local_name));

	cl_assert_equal_s(expected_tracked_branch_name, buf.ptr);
	git_buf_dispose(&buf);

	/* ...and the name of the remote... */
	cl_git_pass(git_branch_remote_name(&buf, g_repo_cloned, expected_tracked_branch_name));

	cl_assert_equal_s(expected_remote_name, buf.ptr);
	git_buf_dispose(&buf);

	/* ...even when the remote HEAD is unborn as well */
	cl_assert_equal_i(GIT_ENOTFOUND, git_reference_lookup(&ref, g_repo_cloned,
		expected_tracked_branch_name));
}