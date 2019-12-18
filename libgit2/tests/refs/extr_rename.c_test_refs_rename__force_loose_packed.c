#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ git_reference ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_reference_lookup (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_rename (TYPE_1__**,TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_target (TYPE_1__*) ; 
 int /*<<< orphan*/  packed_head_name ; 
 int /*<<< orphan*/  packed_test_head_name ; 

void test_refs_rename__force_loose_packed(void)
{
	/* can force-rename a packed reference with the name of an existing loose and packed reference */
	git_reference *looked_up_ref, *renamed_ref;
	git_oid oid;

	/* An existing reference... */
	cl_git_pass(git_reference_lookup(&looked_up_ref, g_repo, packed_head_name));
	git_oid_cpy(&oid, git_reference_target(looked_up_ref));

	/* Can be force-renamed to the name of another existing reference. */
	cl_git_pass(git_reference_rename(&renamed_ref, looked_up_ref, packed_test_head_name, 1, NULL));
	git_reference_free(looked_up_ref);
	git_reference_free(renamed_ref);

	/* Check we actually renamed it */
	cl_git_pass(git_reference_lookup(&looked_up_ref, g_repo, packed_test_head_name));
	cl_assert_equal_s(looked_up_ref->name, packed_test_head_name);
	cl_assert_equal_oid(&oid, git_reference_target(looked_up_ref));
	git_reference_free(looked_up_ref);

	/* And that the previous one doesn't exist any longer */
	cl_git_fail(git_reference_lookup(&looked_up_ref, g_repo, packed_head_name));
}