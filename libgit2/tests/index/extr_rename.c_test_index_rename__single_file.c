#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_fixture_cleanup (char*) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 int git_index_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_find (size_t*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* git_index_get_byindex (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  git_index_remove (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 
 int /*<<< orphan*/  p_rename (char*,char*) ; 

void test_index_rename__single_file(void)
{
	git_repository *repo;
	git_index *index;
	size_t position;
	git_oid expected;
	const git_index_entry *entry;

	p_mkdir("rename", 0700);

	cl_git_pass(git_repository_init(&repo, "./rename", 0));
	cl_git_pass(git_repository_index(&index, repo));

	cl_assert(git_index_entrycount(index) == 0);

	cl_git_mkfile("./rename/lame.name.txt", "new_file\n");

	/* This should add a new blob to the object database in 'd4/fa8600b4f37d7516bef4816ae2c64dbf029e3a' */
	cl_git_pass(git_index_add_bypath(index, "lame.name.txt"));
	cl_assert(git_index_entrycount(index) == 1);

	cl_git_pass(git_oid_fromstr(&expected, "d4fa8600b4f37d7516bef4816ae2c64dbf029e3a"));

	cl_assert(!git_index_find(&position, index, "lame.name.txt"));

	entry = git_index_get_byindex(index, position);
	cl_assert_equal_oid(&expected, &entry->id);

	/* This removes the entry from the index, but not from the object database */
	cl_git_pass(git_index_remove(index, "lame.name.txt", 0));
	cl_assert(git_index_entrycount(index) == 0);

	p_rename("./rename/lame.name.txt", "./rename/fancy.name.txt");

	cl_git_pass(git_index_add_bypath(index, "fancy.name.txt"));
	cl_assert(git_index_entrycount(index) == 1);

	cl_assert(!git_index_find(&position, index, "fancy.name.txt"));

	entry = git_index_get_byindex(index, position);
	cl_assert_equal_oid(&expected, &entry->id);

	git_index_free(index);
	git_repository_free(repo);

	cl_fixture_cleanup("rename");
}