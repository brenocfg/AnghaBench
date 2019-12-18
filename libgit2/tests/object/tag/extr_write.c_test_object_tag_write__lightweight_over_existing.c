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
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_EEXISTS ; 
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_oid_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tag_create_lightweight (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tag2_id ; 
 int /*<<< orphan*/  tagged_commit ; 

void test_object_tag_write__lightweight_over_existing(void)
{
	/* Attempt to write a lightweight tag bearing the same name than an already existing tag */
	git_oid target_id, object_id, existing_object_id;
	git_object *target;

	git_oid_fromstr(&target_id, tagged_commit);
	cl_git_pass(git_object_lookup(&target, g_repo, &target_id, GIT_OBJECT_COMMIT));

	cl_assert_equal_i(GIT_EEXISTS, git_tag_create_lightweight(
                                          &object_id,
                                          g_repo,
                                          "e90810b",
                                          target,
                                          0));

	git_oid_fromstr(&existing_object_id, tag2_id);
	cl_assert(git_oid_cmp(&object_id, &existing_object_id) == 0);

	git_object_free(target);
}