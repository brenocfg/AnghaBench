#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; } ;
typedef  TYPE_1__ git_status_options ;
typedef  int /*<<< orphan*/  git_status_list ;
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_6__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 TYPE_1__ GIT_STATUS_OPTIONS_INIT ; 
 int GIT_STATUS_OPT_DISABLE_PATHSPEC_MATCH ; 
 int GIT_STATUS_OPT_EXCLUDE_SUBMODULES ; 
 int GIT_STATUS_OPT_INCLUDE_UNTRACKED ; 
 int GIT_STATUS_OPT_RECURSE_UNTRACKED_DIRS ; 
 int /*<<< orphan*/  GIT_STATUS_WT_DELETED ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_sz (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 TYPE_3__* git_status_byindex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_status_list_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_status_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_status_list_new (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  p_unlink (char*) ; 

void test_status_worktree__simple_delete_indexed(void)
{
	git_repository *repo = cl_git_sandbox_init("renames");
	git_status_options opts = GIT_STATUS_OPTIONS_INIT;
	git_status_list *status;

	opts.flags = GIT_STATUS_OPT_INCLUDE_UNTRACKED |
		GIT_STATUS_OPT_DISABLE_PATHSPEC_MATCH |
		GIT_STATUS_OPT_EXCLUDE_SUBMODULES |
		GIT_STATUS_OPT_RECURSE_UNTRACKED_DIRS;

	cl_git_pass(git_status_list_new(&status, repo, &opts));
	cl_assert_equal_sz(0, git_status_list_entrycount(status));
	git_status_list_free(status);

	cl_must_pass(p_unlink("renames/untimely.txt"));

	cl_git_pass(git_status_list_new(&status, repo, &opts));
	cl_assert_equal_sz(1, git_status_list_entrycount(status));
	cl_assert_equal_i(
		GIT_STATUS_WT_DELETED, git_status_byindex(status, 0)->status);
	git_status_list_free(status);
}