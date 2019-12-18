#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  gitlink_path; } ;
typedef  TYPE_2__ git_worktree ;
struct TYPE_16__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_3__ git_buf ;
struct TYPE_17__ {int /*<<< orphan*/  workdir; } ;
struct TYPE_14__ {int /*<<< orphan*/  gitlink; } ;
struct TYPE_13__ {TYPE_1__* worktree; TYPE_5__* repo; } ;

/* Variables and functions */
 TYPE_3__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_11__ fixture ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_3__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_worktree_add (TYPE_2__**,TYPE_5__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_worktree_free (TYPE_2__*) ; 
 int /*<<< orphan*/  git_worktree_lookup (TYPE_2__**,TYPE_5__*,char*) ; 

void test_worktree_worktree__init_existing_worktree(void)
{
	git_worktree *wt;
	git_buf path = GIT_BUF_INIT;

	cl_git_pass(git_buf_joinpath(&path, fixture.repo->workdir, "../worktree-new"));
	cl_git_fail(git_worktree_add(&wt, fixture.repo, "testrepo-worktree", path.ptr, NULL));

	cl_git_pass(git_worktree_lookup(&wt, fixture.repo, "testrepo-worktree"));
	cl_assert_equal_s(wt->gitlink_path, fixture.worktree->gitlink);

	git_buf_dispose(&path);
	git_worktree_free(wt);
}