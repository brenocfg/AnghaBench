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
 scalar_t__ GIT_REFERENCE_DIRECT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_set_target (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_target (int /*<<< orphan*/ *) ; 
 scalar_t__ git_reference_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ref_master_name ; 
 int /*<<< orphan*/  ref_test_name ; 

void test_refs_setter__update_direct(void)
{
	git_reference *ref, *test_ref, *new_ref;
	git_oid id;

	cl_git_pass(git_reference_lookup(&ref, g_repo, ref_master_name));
	cl_assert(git_reference_type(ref) == GIT_REFERENCE_DIRECT);
	git_oid_cpy(&id, git_reference_target(ref));
	git_reference_free(ref);

	cl_git_pass(git_reference_lookup(&test_ref, g_repo, ref_test_name));
	cl_assert(git_reference_type(test_ref) == GIT_REFERENCE_DIRECT);

	cl_git_pass(git_reference_set_target(&new_ref, test_ref, &id, NULL));

	git_reference_free(test_ref);
	git_reference_free(new_ref);

	cl_git_pass(git_reference_lookup(&test_ref, g_repo, ref_test_name));
	cl_assert(git_reference_type(test_ref) == GIT_REFERENCE_DIRECT);
	cl_assert_equal_oid(&id, git_reference_target(test_ref));
	git_reference_free(test_ref);
}