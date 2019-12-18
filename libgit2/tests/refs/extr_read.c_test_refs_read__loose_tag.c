#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tag ;
struct TYPE_11__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ git_reference ;
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_12__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_OBJECT_ANY ; 
 scalar_t__ GIT_OBJECT_TAG ; 
 int GIT_REFERENCE_DIRECT ; 
 int /*<<< orphan*/  GIT_REFS_TAGS_DIR ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ git_object_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_reference_lookup (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_target (TYPE_1__*) ; 
 int git_reference_type (TYPE_1__*) ; 
 int /*<<< orphan*/  git_tag_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  loose_tag_ref_name ; 
 scalar_t__ reference_is_packed (TYPE_1__*) ; 

void test_refs_read__loose_tag(void)
{
	/* lookup a loose tag reference */
	git_reference *reference;
	git_object *object;
	git_buf ref_name_from_tag_name = GIT_BUF_INIT;

	cl_git_pass(git_reference_lookup(&reference, g_repo, loose_tag_ref_name));
	cl_assert(git_reference_type(reference) & GIT_REFERENCE_DIRECT);
	cl_assert(reference_is_packed(reference) == 0);
	cl_assert_equal_s(reference->name, loose_tag_ref_name);

	cl_git_pass(git_object_lookup(&object, g_repo, git_reference_target(reference), GIT_OBJECT_ANY));
	cl_assert(object != NULL);
	cl_assert(git_object_type(object) == GIT_OBJECT_TAG);

	/* Ensure the name of the tag matches the name of the reference */
	cl_git_pass(git_buf_joinpath(&ref_name_from_tag_name, GIT_REFS_TAGS_DIR, git_tag_name((git_tag *)object)));
	cl_assert_equal_s(ref_name_from_tag_name.ptr, loose_tag_ref_name);
	git_buf_dispose(&ref_name_from_tag_name);

	git_object_free(object);

	git_reference_free(reference);
}