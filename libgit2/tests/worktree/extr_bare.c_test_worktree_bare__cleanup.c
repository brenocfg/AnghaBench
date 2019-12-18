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
 int /*<<< orphan*/  WORKTREE_REPO ; 
 int /*<<< orphan*/  cl_fixture_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_cleanup () ; 

void test_worktree_bare__cleanup(void)
{
	cl_fixture_cleanup(WORKTREE_REPO);
	cl_git_sandbox_cleanup();
}