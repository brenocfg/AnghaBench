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
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_worktree_prune_options ;
typedef  int /*<<< orphan*/  git_worktree ;
typedef  int /*<<< orphan*/  git_reference ;
struct TYPE_6__ {int /*<<< orphan*/  repo; int /*<<< orphan*/  worktreename; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BRANCH_LOCAL ; 
 TYPE_1__ GIT_WORKTREE_PRUNE_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_WORKTREE_PRUNE_VALID ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_3__ fixture ; 
 int /*<<< orphan*/  git_branch_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_branch_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_worktree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_worktree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_worktree_prune (int /*<<< orphan*/ *,TYPE_1__*) ; 

void test_worktree_refs__delete_succeeds_after_pruning_worktree(void)
{
	git_worktree_prune_options opts = GIT_WORKTREE_PRUNE_OPTIONS_INIT;
	git_reference *branch;
	git_worktree *worktree;

	opts.flags = GIT_WORKTREE_PRUNE_VALID;

	cl_git_pass(git_worktree_lookup(&worktree, fixture.repo, fixture.worktreename));
	cl_git_pass(git_worktree_prune(worktree, &opts));
	git_worktree_free(worktree);

	cl_git_pass(git_branch_lookup(&branch, fixture.repo,
		    "testrepo-worktree", GIT_BRANCH_LOCAL));
	cl_git_pass(git_branch_delete(branch));
	git_reference_free(branch);
}