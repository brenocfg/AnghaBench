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
 char* GIT_HEAD_FILE ; 
 int /*<<< orphan*/  branch ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_branch_is_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_symbolic_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_head (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo ; 

void test_refs_branches_ishead__only_direct_references_are_considered(void)
{
	git_reference *linked, *super, *head;

	cl_git_pass(git_reference_symbolic_create(&linked, repo, "refs/heads/linked", "refs/heads/master", 0, NULL));
	cl_git_pass(git_reference_symbolic_create(&super, repo, "refs/heads/super", "refs/heads/linked", 0, NULL));
	cl_git_pass(git_reference_symbolic_create(&head, repo, GIT_HEAD_FILE, "refs/heads/super", 1, NULL));

	cl_assert_equal_i(false, git_branch_is_head(linked));
	cl_assert_equal_i(false, git_branch_is_head(super));

	cl_git_pass(git_repository_head(&branch, repo));
	cl_assert_equal_s("refs/heads/master", git_reference_name(branch));

	git_reference_free(linked);
	git_reference_free(super);
	git_reference_free(head);
}