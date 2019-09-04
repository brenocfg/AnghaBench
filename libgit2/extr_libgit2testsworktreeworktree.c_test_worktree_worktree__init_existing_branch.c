#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_worktree ;
struct TYPE_16__ {int /*<<< orphan*/  oid; } ;
struct TYPE_17__ {TYPE_1__ target; } ;
typedef  TYPE_2__ git_reference ;
typedef  int /*<<< orphan*/  git_commit ;
struct TYPE_18__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_3__ git_buf ;
struct TYPE_19__ {int /*<<< orphan*/  workdir; } ;
struct TYPE_15__ {TYPE_4__* repo; } ;

/* Variables and functions */
 TYPE_3__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_13__ fixture ; 
 int /*<<< orphan*/  git_branch_create (TYPE_2__**,TYPE_4__*,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_3__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ **,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (TYPE_2__*) ; 
 int /*<<< orphan*/  git_repository_head (TYPE_2__**,TYPE_4__*) ; 
 int /*<<< orphan*/  git_worktree_add (int /*<<< orphan*/ **,TYPE_4__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void test_worktree_worktree__init_existing_branch(void)
{
	git_reference *head, *branch;
	git_commit *commit;
	git_worktree *wt;
	git_buf path = GIT_BUF_INIT;

	cl_git_pass(git_repository_head(&head, fixture.repo));
	cl_git_pass(git_commit_lookup(&commit, fixture.repo, &head->target.oid));
	cl_git_pass(git_branch_create(&branch, fixture.repo, "worktree-new", commit, false));

	cl_git_pass(git_buf_joinpath(&path, fixture.repo->workdir, "../worktree-new"));
	cl_git_fail(git_worktree_add(&wt, fixture.repo, "worktree-new", path.ptr, NULL));

	git_buf_dispose(&path);
	git_commit_free(commit);
	git_reference_free(head);
	git_reference_free(branch);
}