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
 int /*<<< orphan*/  GIT_HEAD_FILE ; 
 int /*<<< orphan*/  GIT_REFERENCE_SYMBOLIC ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_branch_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_branch_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_symbolic_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_detach_head (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo ; 

void test_refs_branches_delete__can_delete_a_branch_pointed_at_by_detached_HEAD(void)
{
	git_reference *head, *branch;

	cl_git_pass(git_reference_lookup(&head, repo, GIT_HEAD_FILE));
	cl_assert_equal_i(GIT_REFERENCE_SYMBOLIC, git_reference_type(head));
	cl_assert_equal_s("refs/heads/master", git_reference_symbolic_target(head));
	git_reference_free(head);

	/* Detach HEAD and make it target the commit that "master" points to */
	git_repository_detach_head(repo);

	cl_git_pass(git_branch_lookup(&branch, repo, "master", GIT_BRANCH_LOCAL));
	cl_git_pass(git_branch_delete(branch));
	git_reference_free(branch);
}