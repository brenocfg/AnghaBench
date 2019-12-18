#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int lock; } ;
typedef  TYPE_1__ git_worktree_add_options ;
typedef  int /*<<< orphan*/  git_worktree ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference ;
struct TYPE_11__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;
struct TYPE_13__ {TYPE_3__* repo; } ;
struct TYPE_12__ {int /*<<< orphan*/  workdir; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BRANCH_LOCAL ; 
 TYPE_2__ GIT_BUF_INIT ; 
 TYPE_1__ GIT_WORKTREE_ADD_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_7__ fixture ; 
 scalar_t__ git__suffixcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_branch_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_worktree_add (int /*<<< orphan*/ **,TYPE_3__*,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  git_worktree_free (int /*<<< orphan*/ *) ; 
 int git_worktree_is_locked (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void test_worktree_worktree__add_locked(void)
{
	git_worktree *wt;
	git_repository *repo;
	git_reference *branch;
	git_buf path = GIT_BUF_INIT;
	git_worktree_add_options opts = GIT_WORKTREE_ADD_OPTIONS_INIT;

	opts.lock = 1;

	cl_git_pass(git_buf_joinpath(&path, fixture.repo->workdir, "../worktree-locked"));
	cl_git_pass(git_worktree_add(&wt, fixture.repo, "worktree-locked", path.ptr, &opts));

	/* Open and verify created repo */
	cl_assert(git_worktree_is_locked(NULL, wt));
	cl_git_pass(git_repository_open(&repo, path.ptr));
	cl_assert(git__suffixcmp(git_repository_workdir(repo), "worktree-locked/") == 0);
	cl_git_pass(git_branch_lookup(&branch, repo, "worktree-locked", GIT_BRANCH_LOCAL));

	git_buf_dispose(&path);
	git_worktree_free(wt);
	git_reference_free(branch);
	git_repository_free(repo);
}