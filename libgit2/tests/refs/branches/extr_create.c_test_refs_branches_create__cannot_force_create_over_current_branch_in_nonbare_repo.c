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
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BRANCH_LOCAL ; 
 int /*<<< orphan*/ * branch ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail_with (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_cleanup () ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_branch_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_branch_is_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_branch_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_reference_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  retrieve_known_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target ; 

void test_refs_branches_create__cannot_force_create_over_current_branch_in_nonbare_repo(void)
{
	const git_oid *oid;
	git_reference *branch2;

	/* Default repo for these tests is a bare repo, but this test requires a non-bare one */
	cl_git_sandbox_cleanup();
	repo = cl_git_sandbox_init("testrepo");
	retrieve_known_commit(&target, repo);

	cl_git_pass(git_branch_lookup(&branch2, repo, "master", GIT_BRANCH_LOCAL));
	cl_assert_equal_s("refs/heads/master", git_reference_name(branch2));
	cl_assert_equal_i(true, git_branch_is_head(branch2));
	oid = git_reference_target(branch2);

	cl_git_fail_with(-1, git_branch_create(&branch, repo, "master", target, 1));
	branch = NULL;
	cl_git_pass(git_branch_lookup(&branch, repo, "master", GIT_BRANCH_LOCAL));
	cl_assert_equal_s("refs/heads/master", git_reference_name(branch));
	cl_git_pass(git_oid_cmp(git_reference_target(branch), oid));
	git_reference_free(branch2);
}