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

/* Variables and functions */
 int GIT_REFERENCE_DIRECT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_create (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_reference_lookup (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_rename (TYPE_1__**,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_target (TYPE_1__*) ; 
 int git_reference_type (TYPE_1__*) ; 
 int /*<<< orphan*/  ref_master_name ; 
 int /*<<< orphan*/  ref_two_name ; 
 int /*<<< orphan*/  ref_two_name_new ; 

void test_refs_rename__move_up(void)
{
	/* can move a reference to a upper reference hierarchy */
	git_reference *ref, *ref_two, *looked_up_ref, *renamed_ref;
	git_oid id;

	cl_git_pass(git_reference_lookup(&ref, g_repo, ref_master_name));
	cl_assert(git_reference_type(ref) & GIT_REFERENCE_DIRECT);

	git_oid_cpy(&id, git_reference_target(ref));

	/* Create loose references */
	cl_git_pass(git_reference_create(&ref_two, g_repo, ref_two_name_new, &id, 0, NULL));
	git_reference_free(ref_two);

	/* An existing reference... */
	cl_git_pass(git_reference_lookup(&looked_up_ref, g_repo, ref_two_name_new));

	/* Can be renamed upward the reference tree. */
	cl_git_pass(git_reference_rename(&renamed_ref, looked_up_ref, ref_two_name, 0, NULL));
	git_reference_free(looked_up_ref);
	git_reference_free(renamed_ref);

	/* Check we actually renamed it */
	cl_git_pass(git_reference_lookup(&looked_up_ref, g_repo, ref_two_name));
	cl_assert_equal_s(looked_up_ref->name, ref_two_name);
	git_reference_free(looked_up_ref);

	cl_git_fail(git_reference_lookup(&looked_up_ref, g_repo, ref_two_name_new));
	git_reference_free(ref);
	git_reference_free(looked_up_ref);
}