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
struct TYPE_3__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int GIT_INDEX_CAPABILITY_IGNORE_CASE ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/  cl_set_cleanup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cleanup_myrepo ; 
 scalar_t__ git__strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 int git_index_caps (int /*<<< orphan*/ *) ; 
 scalar_t__ git_index_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* git_index_get_bypath (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_rename (char*,char*) ; 

void test_index_tests__preserves_case(void)
{
	git_repository *repo;
	git_index *index;
	const git_index_entry *entry;
	int index_caps;

	cl_set_cleanup(&cleanup_myrepo, NULL);

	cl_git_pass(git_repository_init(&repo, "./myrepo", 0));
	cl_git_pass(git_repository_index(&index, repo));

	index_caps = git_index_caps(index);

	cl_git_rewritefile("myrepo/test.txt", "hey there\n");
	cl_git_pass(git_index_add_bypath(index, "test.txt"));

	cl_git_pass(p_rename("myrepo/test.txt", "myrepo/TEST.txt"));
	cl_git_rewritefile("myrepo/TEST.txt", "hello again\n");
	cl_git_pass(git_index_add_bypath(index, "TEST.txt"));

	if (index_caps & GIT_INDEX_CAPABILITY_IGNORE_CASE)
		cl_assert_equal_i(1, (int)git_index_entrycount(index));
	else
		cl_assert_equal_i(2, (int)git_index_entrycount(index));

	/* Test access by path instead of index */
	cl_assert((entry = git_index_get_bypath(index, "test.txt", 0)) != NULL);
	/* The path should *not* have changed without an explicit remove */
	cl_assert(git__strcmp(entry->path, "test.txt") == 0);

	cl_assert((entry = git_index_get_bypath(index, "TEST.txt", 0)) != NULL);
	if (index_caps & GIT_INDEX_CAPABILITY_IGNORE_CASE)
		/* The path should *not* have changed without an explicit remove */
		cl_assert(git__strcmp(entry->path, "test.txt") == 0);
	else
		cl_assert(git__strcmp(entry->path, "TEST.txt") == 0);

	git_index_free(index);
	git_repository_free(repo);
}