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
 scalar_t__ GIT_REFERENCE_SYMBOLIC ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_reference_symbolic_set_target (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_symbolic_target (int /*<<< orphan*/ *) ; 
 scalar_t__ git_reference_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ref_master_name ; 
 int /*<<< orphan*/  ref_test_name ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void test_refs_setter__update_symbolic(void)
{
	git_reference *head, *new_head;

	cl_git_pass(git_reference_lookup(&head, g_repo, "HEAD"));
	cl_assert(git_reference_type(head) == GIT_REFERENCE_SYMBOLIC);
	cl_assert(strcmp(git_reference_symbolic_target(head), ref_master_name) == 0);

	cl_git_pass(git_reference_symbolic_set_target(&new_head, head, ref_test_name, NULL));
	git_reference_free(new_head);
	git_reference_free(head);

	cl_git_pass(git_reference_lookup(&head, g_repo, "HEAD"));
	cl_assert(git_reference_type(head) == GIT_REFERENCE_SYMBOLIC);
	cl_assert(strcmp(git_reference_symbolic_target(head), ref_test_name) == 0);
	git_reference_free(head);
}