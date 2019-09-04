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
struct TYPE_7__ {int /*<<< orphan*/ * message; } ;
typedef  TYPE_1__ git_tag ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
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
 int /*<<< orphan*/  short_tag_id ; 
 int /*<<< orphan*/  short_tagged_commit ; 

void test_object_tag_read__parse_without_message(void)
{
	/* read and parse a tag without a message field */
	git_repository *short_tag_repo;
	git_tag *short_tag;
	git_commit *commit;
	git_oid id, id_commit;

	/* TODO: This is a little messy */
	cl_git_pass(git_repository_open(&short_tag_repo, cl_fixture("short_tag.git")));

	git_oid_fromstr(&id, short_tag_id);
	git_oid_fromstr(&id_commit, short_tagged_commit);

	cl_git_pass(git_tag_lookup(&short_tag, short_tag_repo, &id));
	cl_assert(short_tag != NULL);

	cl_assert_equal_s(git_tag_name(short_tag), "no_description");
	cl_assert(git_oid_cmp(&id, git_tag_id(short_tag)) == 0);
	cl_assert(short_tag->message == NULL);

	cl_git_pass(git_tag_target((git_object **)&commit, short_tag));
	cl_assert(commit != NULL);

	cl_assert(git_oid_cmp(&id_commit, git_commit_id(commit)) == 0);

	git_tag_free(short_tag);
	git_commit_free(commit);
	git_repository_free(short_tag_repo);
}