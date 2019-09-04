#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_worktree ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference ;
struct TYPE_7__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;
struct TYPE_9__ {TYPE_2__* repo; } ;
struct TYPE_8__ {int /*<<< orphan*/  workdir; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BRANCH_LOCAL ; 
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_5__ fixture ; 
 scalar_t__ git__suffixcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_branch_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_worktree_add (int /*<<< orphan*/ **,TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_worktree_free (int /*<<< orphan*/ *) ; 

void test_worktree_worktree__init(void)
{
	git_worktree *wt;
	git_repository *repo;
	git_reference *branch;
	git_buf path = GIT_BUF_INIT;

	cl_git_pass(git_buf_joinpath(&path, fixture.repo->workdir, "../worktree-new"));
	cl_git_pass(git_worktree_add(&wt, fixture.repo, "worktree-new", path.ptr, NULL));

	/* Open and verify created repo */
	cl_git_pass(git_repository_open(&repo, path.ptr));
	cl_assert(git__suffixcmp(git_repository_workdir(repo), "worktree-new/") == 0);
	cl_git_pass(git_branch_lookup(&branch, repo, "worktree-new", GIT_BRANCH_LOCAL));

	git_buf_dispose(&path);
	git_worktree_free(wt);
	git_reference_free(branch);
	git_repository_free(repo);
}