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
typedef  int /*<<< orphan*/  git_reference ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BRANCH_LOCAL ; 
 int /*<<< orphan*/  assert_config_entry_existence (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_branch_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_branch_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  repo ; 

void test_refs_branches_delete__deleting_a_branch_removes_related_configuration_data(void)
{
	git_reference *branch;

	assert_config_entry_existence(repo, "branch.track-local.remote", true);
	assert_config_entry_existence(repo, "branch.track-local.merge", true);

	cl_git_pass(git_branch_lookup(&branch, repo, "track-local", GIT_BRANCH_LOCAL));
	cl_git_pass(git_branch_delete(branch));
	git_reference_free(branch);

	assert_config_entry_existence(repo, "branch.track-local.remote", false);
	assert_config_entry_existence(repo, "branch.track-local.merge", false);
}