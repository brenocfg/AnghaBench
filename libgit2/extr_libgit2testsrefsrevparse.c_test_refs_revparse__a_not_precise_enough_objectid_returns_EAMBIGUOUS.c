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
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_EAMBIGUOUS ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_cleanup () ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 

void test_refs_revparse__a_not_precise_enough_objectid_returns_EAMBIGUOUS(void)
{
	git_repository *repo;
	git_index *index;
	git_object *obj;

	repo = cl_git_sandbox_init("testrepo");

	cl_git_mkfile("testrepo/one.txt", "aabqhq\n");
	cl_git_mkfile("testrepo/two.txt", "aaazvc\n");
	
	cl_git_pass(git_repository_index(&index, repo));
	cl_git_pass(git_index_add_bypath(index, "one.txt"));
	cl_git_pass(git_index_add_bypath(index, "two.txt"));
	
	cl_git_fail_with(git_revparse_single(&obj, repo, "dea509d0"), GIT_EAMBIGUOUS);

	cl_git_pass(git_revparse_single(&obj, repo, "dea509d09"));

	git_object_free(obj);
	git_index_free(index);
	cl_git_sandbox_cleanup();
}