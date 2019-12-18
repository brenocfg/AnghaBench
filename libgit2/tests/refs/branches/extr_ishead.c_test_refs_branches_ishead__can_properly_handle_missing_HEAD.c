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
 int /*<<< orphan*/  branch ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_head (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_branch_is_head (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  repo ; 

void test_refs_branches_ishead__can_properly_handle_missing_HEAD(void)
{
	delete_head(repo);

	cl_git_pass(git_reference_lookup(&branch, repo, "refs/heads/master"));

	cl_assert_equal_i(false, git_branch_is_head(branch));
}