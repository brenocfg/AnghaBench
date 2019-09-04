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
 int /*<<< orphan*/  assert_checked_out (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  cl_git_sandbox_cleanup () ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  repo ; 

void test_refs_branches_checkedout__simple_repo(void)
{
	repo = cl_git_sandbox_init("testrepo");
	assert_checked_out(repo, "refs/heads/master", 1);
	assert_checked_out(repo, "refs/heads/executable", 0);
	cl_git_sandbox_cleanup();
}