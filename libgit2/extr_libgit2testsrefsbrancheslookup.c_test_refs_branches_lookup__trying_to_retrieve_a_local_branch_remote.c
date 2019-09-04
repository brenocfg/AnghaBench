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
 int /*<<< orphan*/  GIT_BRANCH_REMOTE ; 
 int /*<<< orphan*/  branch ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_branch_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo ; 

void test_refs_branches_lookup__trying_to_retrieve_a_local_branch_remote(void)
{
	cl_git_fail(git_branch_lookup(&branch, repo, "br2", GIT_BRANCH_REMOTE));
}