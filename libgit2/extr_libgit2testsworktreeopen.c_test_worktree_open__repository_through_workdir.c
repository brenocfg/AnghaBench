#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 int /*<<< orphan*/  COMMON_REPO ; 
 int /*<<< orphan*/  WORKTREE_REPO ; 
 int /*<<< orphan*/  assert_worktree_valid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void test_worktree_open__repository_through_workdir(void)
{
	git_repository *wt;

	cl_git_pass(git_repository_open(&wt, WORKTREE_REPO));
	assert_worktree_valid(wt, COMMON_REPO, WORKTREE_REPO);

	git_repository_free(wt);
}