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
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_ANY ; 
 scalar_t__ GIT_OBJECT_COMMIT ; 
 int GIT_REFERENCE_DIRECT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ git_object_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_reference_lookup (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_target (TYPE_1__*) ; 
 int git_reference_type (TYPE_1__*) ; 
 int /*<<< orphan*/  packed_head_name ; 
 int reference_is_packed (TYPE_1__*) ; 

void test_refs_read__packed(void)
{
	/* lookup a packed reference */
	git_reference *reference;
	git_object *object;

	cl_git_pass(git_reference_lookup(&reference, g_repo, packed_head_name));
	cl_assert(git_reference_type(reference) & GIT_REFERENCE_DIRECT);
	cl_assert(reference_is_packed(reference));
	cl_assert_equal_s(reference->name, packed_head_name);

	cl_git_pass(git_object_lookup(&object, g_repo, git_reference_target(reference), GIT_OBJECT_ANY));
	cl_assert(object != NULL);
	cl_assert(git_object_type(object) == GIT_OBJECT_COMMIT);

	git_object_free(object);

	git_reference_free(reference);
}