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
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_oid_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * git_reference_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tag_create_lightweight (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tag_delete (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tagged_commit ; 

void test_object_tag_write__lightweight(void)
{
	/* write a lightweight tag to the repository and read it again */
	git_oid target_id, object_id;
	git_reference *ref_tag;
	git_object *target;

	git_oid_fromstr(&target_id, tagged_commit);
	cl_git_pass(git_object_lookup(&target, g_repo, &target_id, GIT_OBJECT_COMMIT));

	cl_git_pass(git_tag_create_lightweight(
                                          &object_id,
                                          g_repo,
                                          "light-tag",
                                          target,
                                          0));

	git_object_free(target);

	cl_assert(git_oid_cmp(&object_id, &target_id) == 0);

	cl_git_pass(git_reference_lookup(&ref_tag, g_repo, "refs/tags/light-tag"));
	cl_assert(git_oid_cmp(git_reference_target(ref_tag), &target_id) == 0);

	cl_git_pass(git_tag_delete(g_repo, "light-tag"));

	git_reference_free(ref_tag);
}