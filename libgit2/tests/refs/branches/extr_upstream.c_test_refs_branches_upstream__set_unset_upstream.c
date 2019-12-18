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
typedef  int /*<<< orphan*/  git_reference ;

/* Variables and functions */
 int /*<<< orphan*/  assert_config_entry_existence (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  assert_config_entry_value (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_cleanup () ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_branch_set_upstream (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 

void test_refs_branches_upstream__set_unset_upstream(void)
{
	git_reference *branch;
	git_repository *repository;

	repository = cl_git_sandbox_init("testrepo.git");

	/* remote */
	cl_git_pass(git_reference_lookup(&branch, repository, "refs/heads/test"));
	cl_git_pass(git_branch_set_upstream(branch, "test/master"));

	assert_config_entry_value(repository, "branch.test.remote", "test");
	assert_config_entry_value(repository, "branch.test.merge", "refs/heads/master");

	git_reference_free(branch);

	/* local */
	cl_git_pass(git_reference_lookup(&branch, repository, "refs/heads/test"));
	cl_git_pass(git_branch_set_upstream(branch, "master"));

	assert_config_entry_value(repository, "branch.test.remote", ".");
	assert_config_entry_value(repository, "branch.test.merge", "refs/heads/master");

	/* unset */
	cl_git_pass(git_branch_set_upstream(branch, NULL));
	assert_config_entry_existence(repository, "branch.test.remote", false);
	assert_config_entry_existence(repository, "branch.test.merge", false);

	git_reference_free(branch);

	cl_git_pass(git_reference_lookup(&branch, repository, "refs/heads/master"));
	cl_git_pass(git_branch_set_upstream(branch, NULL));
	assert_config_entry_existence(repository, "branch.test.remote", false);
	assert_config_entry_existence(repository, "branch.test.merge", false);

	git_reference_free(branch);

	cl_git_sandbox_cleanup();
}