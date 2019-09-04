#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ git_reference ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_EINVALIDSPEC ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_reference_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_reference_lookup (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_rename (TYPE_1__**,TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  packed_test_head_name ; 

void test_refs_rename__invalid_name(void)
{
	/* can not rename a reference with an invalid name */
	git_reference *looked_up_ref, *renamed_ref;

	/* An existing oid reference... */
	cl_git_pass(git_reference_lookup(&looked_up_ref, g_repo, packed_test_head_name));

	/* Can not be renamed with an invalid name. */
	cl_assert_equal_i(
		GIT_EINVALIDSPEC,
		git_reference_rename(&renamed_ref, looked_up_ref, "Hello! I'm a very invalid name.", 0, NULL));

	/* Can not be renamed outside of the refs hierarchy
	 * unless it's ALL_CAPS_AND_UNDERSCORES.
	 */
	cl_assert_equal_i(GIT_EINVALIDSPEC, git_reference_rename(&renamed_ref, looked_up_ref, "i-will-sudo-you", 0, NULL));

	/* Failure to rename it hasn't corrupted its state */
	git_reference_free(looked_up_ref);
	cl_git_pass(git_reference_lookup(&looked_up_ref, g_repo, packed_test_head_name));
	cl_assert_equal_s(looked_up_ref->name, packed_test_head_name);

	git_reference_free(looked_up_ref);
}