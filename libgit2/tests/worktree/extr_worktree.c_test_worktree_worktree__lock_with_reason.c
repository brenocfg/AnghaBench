#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_9__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int locked; } ;
typedef  TYPE_1__ git_worktree ;
struct TYPE_12__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;
struct TYPE_13__ {int /*<<< orphan*/  repo; } ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_9__ fixture ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int /*<<< orphan*/  git_worktree_free (TYPE_1__*) ; 
 scalar_t__ git_worktree_is_locked (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  git_worktree_lock (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  git_worktree_lookup (TYPE_1__**,int /*<<< orphan*/ ,char*) ; 

void test_worktree_worktree__lock_with_reason(void)
{
	git_worktree *wt;
	git_buf reason = GIT_BUF_INIT;

	cl_git_pass(git_worktree_lookup(&wt, fixture.repo, "testrepo-worktree"));

	cl_assert(!git_worktree_is_locked(NULL, wt));
	cl_git_pass(git_worktree_lock(wt, "because"));
	cl_assert(git_worktree_is_locked(&reason, wt) > 0);
	cl_assert_equal_s(reason.ptr, "because");
	cl_assert(wt->locked);

	git_buf_dispose(&reason);
	git_worktree_free(wt);
}