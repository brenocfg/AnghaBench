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
struct TYPE_7__ {int /*<<< orphan*/ * tagger; } ;
typedef  TYPE_1__ git_tag ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  bad_tag_id ; 
 int /*<<< orphan*/  badly_tagged_commit ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_id (int /*<<< orphan*/ *) ; 
 scalar_t__ git_oid_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tag_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_tag_id (TYPE_1__*) ; 
 int /*<<< orphan*/  git_tag_lookup (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tag_name (TYPE_1__*) ; 
 int /*<<< orphan*/  git_tag_target (int /*<<< orphan*/ **,TYPE_1__*) ; 

void test_object_tag_read__parse_without_tagger(void)
{
	/* read and parse a tag without a tagger field */
	git_repository *bad_tag_repo;
	git_tag *bad_tag;
	git_commit *commit;
	git_oid id, id_commit;

	/* TODO: This is a little messy */
	cl_git_pass(git_repository_open(&bad_tag_repo, cl_fixture("bad_tag.git")));

	git_oid_fromstr(&id, bad_tag_id);
	git_oid_fromstr(&id_commit, badly_tagged_commit);

	cl_git_pass(git_tag_lookup(&bad_tag, bad_tag_repo, &id));
	cl_assert(bad_tag != NULL);

	cl_assert_equal_s(git_tag_name(bad_tag), "e90810b");
	cl_assert(git_oid_cmp(&id, git_tag_id(bad_tag)) == 0);
	cl_assert(bad_tag->tagger == NULL);

	cl_git_pass(git_tag_target((git_object **)&commit, bad_tag));
	cl_assert(commit != NULL);

	cl_assert(git_oid_cmp(&id_commit, git_commit_id(commit)) == 0);


	git_tag_free(bad_tag);
	git_commit_free(commit);
	git_repository_free(bad_tag_repo);
}