#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  COMMON_REPO ; 
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  WORKTREE_REPO ; 
 int /*<<< orphan*/  assert_worktree_valid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void test_worktree_open__repository_through_gitdir(void)
{
	git_buf gitdir_path = GIT_BUF_INIT;
	git_repository *wt;

	cl_git_pass(git_buf_joinpath(&gitdir_path, COMMON_REPO, ".git"));
	cl_git_pass(git_buf_joinpath(&gitdir_path, gitdir_path.ptr, "worktrees"));
	cl_git_pass(git_buf_joinpath(&gitdir_path, gitdir_path.ptr, "testrepo-worktree"));

	cl_git_pass(git_repository_open(&wt, gitdir_path.ptr));
	assert_worktree_valid(wt, COMMON_REPO, WORKTREE_REPO);

	git_buf_dispose(&gitdir_path);
	git_repository_free(wt);
}