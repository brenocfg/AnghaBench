#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_7__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  locked; } ;
typedef  TYPE_1__ git_worktree ;
struct TYPE_9__ {int /*<<< orphan*/  repo; } ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_7__ fixture ; 
 int /*<<< orphan*/  git_worktree_free (TYPE_1__*) ; 
 int git_worktree_is_locked (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_worktree_lock (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_worktree_lookup (TYPE_1__**,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_worktree_unlock (TYPE_1__*) ; 

void test_worktree_worktree__unlock_locked_worktree(void)
{
	git_worktree *wt;

	cl_git_pass(git_worktree_lookup(&wt, fixture.repo, "testrepo-worktree"));
	cl_git_pass(git_worktree_lock(wt, NULL));
	cl_assert(git_worktree_is_locked(NULL, wt));
	cl_assert_equal_i(0, git_worktree_unlock(wt));
	cl_assert(!wt->locked);

	git_worktree_free(wt);
}