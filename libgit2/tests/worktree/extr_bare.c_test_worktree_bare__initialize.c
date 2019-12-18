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

/* Variables and functions */
 int /*<<< orphan*/  COMMON_REPO ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_repository_is_bare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_is_worktree (int /*<<< orphan*/ ) ; 

void test_worktree_bare__initialize(void)
{
	g_repo = cl_git_sandbox_init(COMMON_REPO);

	cl_assert_equal_i(1, git_repository_is_bare(g_repo));
	cl_assert_equal_i(0, git_repository_is_worktree(g_repo));
}