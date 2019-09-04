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
 int /*<<< orphan*/  GIT_EINVALIDSPEC ; 
 int /*<<< orphan*/  GIT_HEAD_FILE ; 
 int /*<<< orphan*/  GIT_REFERENCE_SYMBOLIC ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_symbolic_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_type (int /*<<< orphan*/ *) ; 

void test_refs_update__updating_the_target_of_a_symref_with_an_invalid_name_returns_EINVALIDSPEC(void)
{
	git_reference *head;

	cl_git_pass(git_reference_lookup(&head, g_repo, GIT_HEAD_FILE));
	cl_assert_equal_i(GIT_REFERENCE_SYMBOLIC, git_reference_type(head));
	git_reference_free(head);

	cl_assert_equal_i(GIT_EINVALIDSPEC, git_reference_symbolic_create(&head, g_repo, GIT_HEAD_FILE, "refs/heads/inv@{id", 1, NULL));
}