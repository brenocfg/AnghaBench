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
typedef  int /*<<< orphan*/  git_tag ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 scalar_t__ GIT_OBJECT_TAG ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_id (int /*<<< orphan*/ *) ; 
 scalar_t__ git_oid_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tag_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tag_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tag_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tag_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tag_target (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ git_tag_target_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tag1_id ; 
 int /*<<< orphan*/  tag2_id ; 
 int /*<<< orphan*/  tagged_commit ; 

void test_object_tag_read__parse(void)
{
	/* read and parse a tag from the repository */
	git_tag *tag1, *tag2;
	git_commit *commit;
	git_oid id1, id2, id_commit;

	git_oid_fromstr(&id1, tag1_id);
	git_oid_fromstr(&id2, tag2_id);
	git_oid_fromstr(&id_commit, tagged_commit);

	cl_git_pass(git_tag_lookup(&tag1, g_repo, &id1));

	cl_assert_equal_s(git_tag_name(tag1), "test");
	cl_assert(git_tag_target_type(tag1) == GIT_OBJECT_TAG);

	cl_git_pass(git_tag_target((git_object **)&tag2, tag1));
	cl_assert(tag2 != NULL);

	cl_assert(git_oid_cmp(&id2, git_tag_id(tag2)) == 0);

	cl_git_pass(git_tag_target((git_object **)&commit, tag2));
	cl_assert(commit != NULL);

	cl_assert(git_oid_cmp(&id_commit, git_commit_id(commit)) == 0);

	git_tag_free(tag1);
	git_tag_free(tag2);
	git_commit_free(commit);
}