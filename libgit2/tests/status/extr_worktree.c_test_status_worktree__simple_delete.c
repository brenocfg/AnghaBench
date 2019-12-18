#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; } ;
typedef  TYPE_1__ git_status_options ;
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 TYPE_1__ GIT_STATUS_OPTIONS_INIT ; 
 int GIT_STATUS_OPT_DISABLE_PATHSPEC_MATCH ; 
 int GIT_STATUS_OPT_EXCLUDE_SUBMODULES ; 
 int GIT_STATUS_OPT_INCLUDE_UNTRACKED ; 
 int GIT_STATUS_OPT_RECURSE_UNTRACKED_DIRS ; 
 int /*<<< orphan*/  cb_status__count ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_status_foreach_ext (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  p_unlink (char*) ; 

void test_status_worktree__simple_delete(void)
{
    git_repository *repo = cl_git_sandbox_init("renames");
	git_status_options opts = GIT_STATUS_OPTIONS_INIT;
	int count;

	opts.flags = GIT_STATUS_OPT_INCLUDE_UNTRACKED |
		GIT_STATUS_OPT_DISABLE_PATHSPEC_MATCH |
		GIT_STATUS_OPT_EXCLUDE_SUBMODULES |
		GIT_STATUS_OPT_RECURSE_UNTRACKED_DIRS;

	count = 0;
	cl_git_pass(
		git_status_foreach_ext(repo, &opts, cb_status__count, &count) );
	cl_assert_equal_i(0, count);

	cl_must_pass(p_unlink("renames/untimely.txt"));

	count = 0;
	cl_git_pass(
		git_status_foreach_ext(repo, &opts, cb_status__count, &count) );
	cl_assert_equal_i(1, count);
}