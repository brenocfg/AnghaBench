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
struct TYPE_6__ {int /*<<< orphan*/ * tagger; int /*<<< orphan*/ * message; } ;
typedef  TYPE_1__ git_tag ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 scalar_t__ GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tag_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_tag_lookup (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tag_name (TYPE_1__*) ; 
 scalar_t__ git_tag_target_type (TYPE_1__*) ; 
 int /*<<< orphan*/  taggerless ; 

void test_object_tag_read__without_tagger_nor_message(void)
{
	git_tag *tag;
	git_oid id;
	git_repository *repo;

	cl_git_pass(git_repository_open(&repo, cl_fixture("testrepo.git")));

	cl_git_pass(git_oid_fromstr(&id, taggerless));

	cl_git_pass(git_tag_lookup(&tag, repo, &id));

	cl_assert_equal_s(git_tag_name(tag), "taggerless");
	cl_assert(git_tag_target_type(tag) == GIT_OBJECT_COMMIT);

	cl_assert(tag->message == NULL);
	cl_assert(tag->tagger == NULL);

	git_tag_free(tag);
	git_repository_free(repo);
}