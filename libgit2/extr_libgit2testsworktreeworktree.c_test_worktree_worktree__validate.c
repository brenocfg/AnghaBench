#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_worktree ;
struct TYPE_2__ {int /*<<< orphan*/  repo; } ;

/* Variables and functions */
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_1__ fixture ; 
 int /*<<< orphan*/  git_worktree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_worktree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_worktree_validate (int /*<<< orphan*/ *) ; 

void test_worktree_worktree__validate(void)
{
	git_worktree *wt;

	cl_git_pass(git_worktree_lookup(&wt, fixture.repo, "testrepo-worktree"));
	cl_git_pass(git_worktree_validate(wt));

	git_worktree_free(wt);
}