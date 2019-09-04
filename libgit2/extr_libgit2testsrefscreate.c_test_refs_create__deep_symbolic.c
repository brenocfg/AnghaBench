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
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_head_target ; 
 int /*<<< orphan*/  current_master_tip ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_reference_resolve (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_symbolic_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_target (int /*<<< orphan*/ *) ; 

void test_refs_create__deep_symbolic(void)
{
	/* create a deep symbolic reference */
	git_reference *new_reference, *looked_up_ref, *resolved_ref;
	git_oid id;

	const char *new_head_tracker = "deep/rooted/tracker";

	git_oid_fromstr(&id, current_master_tip);

	cl_git_pass(git_reference_symbolic_create(&new_reference, g_repo, new_head_tracker, current_head_target, 0, NULL));
	cl_git_pass(git_reference_lookup(&looked_up_ref, g_repo, new_head_tracker));
	cl_git_pass(git_reference_resolve(&resolved_ref, looked_up_ref));
	cl_assert_equal_oid(&id, git_reference_target(resolved_ref));

	git_reference_free(new_reference);
	git_reference_free(looked_up_ref);
	git_reference_free(resolved_ref);
}