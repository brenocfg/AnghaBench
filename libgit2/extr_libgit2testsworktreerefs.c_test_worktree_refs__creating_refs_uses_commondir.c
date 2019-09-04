#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_commit ;
struct TYPE_6__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;
struct TYPE_7__ {int /*<<< orphan*/  worktree; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BRANCH_LOCAL ; 
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_4__ fixture ; 
 int /*<<< orphan*/  git_branch_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_branch_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_path_exists (int /*<<< orphan*/ ) ; 
 scalar_t__ git_reference_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_commondir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_head (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void test_worktree_refs__creating_refs_uses_commondir(void)
{
	   git_reference *head, *branch, *lookup;
	   git_commit *commit;
	   git_buf refpath = GIT_BUF_INIT;

	   cl_git_pass(git_buf_joinpath(&refpath,
		       git_repository_commondir(fixture.worktree), "refs/heads/testbranch"));
	   cl_assert(!git_path_exists(refpath.ptr));

	   cl_git_pass(git_repository_head(&head, fixture.worktree));
	   cl_git_pass(git_commit_lookup(&commit, fixture.worktree, git_reference_target(head)));
	   cl_git_pass(git_branch_create(&branch, fixture.worktree, "testbranch", commit, 0));
	   cl_git_pass(git_branch_lookup(&lookup, fixture.worktree, "testbranch", GIT_BRANCH_LOCAL));
	   cl_assert(git_reference_cmp(branch, lookup) == 0);
	   cl_assert(git_path_exists(refpath.ptr));

	   git_reference_free(lookup);
	   git_reference_free(branch);
	   git_reference_free(head);
	   git_commit_free(commit);
	   git_buf_dispose(&refpath);
}