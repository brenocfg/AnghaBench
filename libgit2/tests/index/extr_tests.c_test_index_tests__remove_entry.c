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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_fixture_cleanup (char*) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 int git_index_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_index_get_bypath (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_index_remove (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 

void test_index_tests__remove_entry(void)
{
	git_repository *repo;
	git_index *index;

	p_mkdir("index_test", 0770);

	cl_git_pass(git_repository_init(&repo, "index_test", 0));
	cl_git_pass(git_repository_index(&index, repo));
	cl_assert(git_index_entrycount(index) == 0);

	cl_git_mkfile("index_test/hello", NULL);
	cl_git_pass(git_index_add_bypath(index, "hello"));
	cl_git_pass(git_index_write(index));

	cl_git_pass(git_index_read(index, true)); /* reload */
	cl_assert(git_index_entrycount(index) == 1);
	cl_assert(git_index_get_bypath(index, "hello", 0) != NULL);

	cl_git_pass(git_index_remove(index, "hello", 0));
	cl_git_pass(git_index_write(index));

	cl_git_pass(git_index_read(index, true)); /* reload */
	cl_assert(git_index_entrycount(index) == 0);
	cl_assert(git_index_get_bypath(index, "hello", 0) == NULL);

	git_index_free(index);
	git_repository_free(repo);
	cl_fixture_cleanup("index_test");
}