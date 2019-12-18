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
 int /*<<< orphan*/  GIT_BRANCH_ALL ; 
 int /*<<< orphan*/  GIT_BRANCH_LOCAL ; 
 int /*<<< orphan*/  GIT_BRANCH_REMOTE ; 
 int /*<<< orphan*/  GIT_EINVALIDSPEC ; 
 int /*<<< orphan*/  branch ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_branch_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo ; 

void test_refs_branches_lookup__trying_to_retrieve_a_branch_with_an_invalid_name_returns_EINVALIDSPEC(void)
{
	cl_assert_equal_i(GIT_EINVALIDSPEC,
		git_branch_lookup(&branch, repo, "are/you/inv@{id", GIT_BRANCH_LOCAL));
	cl_assert_equal_i(GIT_EINVALIDSPEC,
		git_branch_lookup(&branch, repo, "yes/i am", GIT_BRANCH_REMOTE));
	cl_assert_equal_i(GIT_EINVALIDSPEC,
		git_branch_lookup(&branch, repo, "inv al/id", GIT_BRANCH_ALL));
}