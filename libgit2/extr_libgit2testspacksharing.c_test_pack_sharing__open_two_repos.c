#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  val; } ;
struct git_pack_file {TYPE_1__ refcount; } ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_ANY ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git__pack_cache ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int git_strmap_iterate (void**,int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_strmap_size (int /*<<< orphan*/ ) ; 

void test_pack_sharing__open_two_repos(void)
{
	git_repository *repo1, *repo2;
	git_object *obj1, *obj2;
	git_oid id;
	size_t pos;
	void *data;
	int error;

	cl_git_pass(git_repository_open(&repo1, cl_fixture("testrepo.git")));
	cl_git_pass(git_repository_open(&repo2, cl_fixture("testrepo.git")));

	git_oid_fromstr(&id, "a65fedf39aefe402d3bb6e24df4d4f5fe4547750");

	cl_git_pass(git_object_lookup(&obj1, repo1, &id, GIT_OBJECT_ANY));
	cl_git_pass(git_object_lookup(&obj2, repo2, &id, GIT_OBJECT_ANY));

	pos = 0;
	while ((error = git_strmap_iterate(&data, git__pack_cache, &pos, NULL)) == 0) {
		struct git_pack_file *pack = (struct git_pack_file *) data;

		cl_assert_equal_i(2, pack->refcount.val);
	}

	cl_assert_equal_i(3, git_strmap_size(git__pack_cache));

	git_object_free(obj1);
	git_object_free(obj2);
	git_repository_free(repo1);
	git_repository_free(repo2);

	/* we don't want to keep the packs open after the repos go away */
	cl_assert_equal_i(0, git_strmap_size(git__pack_cache));
}