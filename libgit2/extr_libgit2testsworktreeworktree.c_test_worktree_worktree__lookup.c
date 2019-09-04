#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  commondir_path; int /*<<< orphan*/  gitlink_path; int /*<<< orphan*/  parent_path; int /*<<< orphan*/  gitdir_path; } ;
typedef  TYPE_2__ git_worktree ;
struct TYPE_13__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_3__ git_buf ;
struct TYPE_15__ {TYPE_5__* repo; TYPE_1__* worktree; } ;
struct TYPE_14__ {int /*<<< orphan*/  commondir; int /*<<< orphan*/  gitdir; int /*<<< orphan*/  workdir; } ;
struct TYPE_11__ {int /*<<< orphan*/  gitlink; } ;

/* Variables and functions */
 TYPE_3__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_9__ fixture ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_3__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_worktree_free (TYPE_2__*) ; 
 int /*<<< orphan*/  git_worktree_lookup (TYPE_2__**,TYPE_5__*,char*) ; 

void test_worktree_worktree__lookup(void)
{
	git_worktree *wt;
	git_buf gitdir_path = GIT_BUF_INIT;

	cl_git_pass(git_worktree_lookup(&wt, fixture.repo, "testrepo-worktree"));

	cl_git_pass(git_buf_joinpath(&gitdir_path, fixture.repo->commondir, "worktrees/testrepo-worktree/"));

	cl_assert_equal_s(wt->gitdir_path, gitdir_path.ptr);
	cl_assert_equal_s(wt->parent_path, fixture.repo->workdir);
	cl_assert_equal_s(wt->gitlink_path, fixture.worktree->gitlink);
	cl_assert_equal_s(wt->commondir_path, fixture.repo->gitdir);
	cl_assert_equal_s(wt->commondir_path, fixture.repo->commondir);

	git_buf_dispose(&gitdir_path);
	git_worktree_free(wt);
}