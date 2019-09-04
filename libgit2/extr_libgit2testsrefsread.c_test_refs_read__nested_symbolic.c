#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ git_reference ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_ANY ; 
 scalar_t__ GIT_OBJECT_COMMIT ; 
 int GIT_REFERENCE_DIRECT ; 
 int GIT_REFERENCE_SYMBOLIC ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_master_tip ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ git_object_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_reference_lookup (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_resolve (TYPE_1__**,TYPE_1__*) ; 
 int /*<<< orphan*/  git_reference_target (TYPE_1__*) ; 
 int git_reference_type (TYPE_1__*) ; 
 int /*<<< orphan*/  head_tracker_sym_ref_name ; 
 scalar_t__ reference_is_packed (TYPE_1__*) ; 

void test_refs_read__nested_symbolic(void)
{
	/* lookup a nested symbolic reference */
	git_reference *reference, *resolved_ref;
	git_object *object;
	git_oid id;

	cl_git_pass(git_reference_lookup(&reference, g_repo, head_tracker_sym_ref_name));
	cl_assert(git_reference_type(reference) & GIT_REFERENCE_SYMBOLIC);
	cl_assert(reference_is_packed(reference) == 0);
	cl_assert_equal_s(reference->name, head_tracker_sym_ref_name);

	cl_git_pass(git_reference_resolve(&resolved_ref, reference));
	cl_assert(git_reference_type(resolved_ref) == GIT_REFERENCE_DIRECT);

	cl_git_pass(git_object_lookup(&object, g_repo, git_reference_target(resolved_ref), GIT_OBJECT_ANY));
	cl_assert(object != NULL);
	cl_assert(git_object_type(object) == GIT_OBJECT_COMMIT);

	git_oid_fromstr(&id, current_master_tip);
	cl_assert_equal_oid(&id, git_object_id(object));

	git_object_free(object);

	git_reference_free(reference);
	git_reference_free(resolved_ref);
}