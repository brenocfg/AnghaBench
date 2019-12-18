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
 int /*<<< orphan*/  GIT_STATUS_INDEX_DELETED ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 scalar_t__ git_index_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_open (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_set_index (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_set_workdir (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_status_file (unsigned int*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 
 int /*<<< orphan*/  p_rmdir (char*) ; 

void test_status_worktree_init__status_file_without_index_or_workdir(void)
{
	git_repository *repo;
	unsigned int status = 0;
	git_index *index;

	cl_git_pass(p_mkdir("wd", 0777));

	cl_git_pass(git_repository_open(&repo, cl_fixture("testrepo.git")));
	cl_git_pass(git_repository_set_workdir(repo, "wd", false));

	cl_git_pass(git_index_open(&index, "empty-index"));
	cl_assert_equal_i(0, (int)git_index_entrycount(index));
	git_repository_set_index(repo, index);

	cl_git_pass(git_status_file(&status, repo, "branch_file.txt"));

	cl_assert_equal_i(GIT_STATUS_INDEX_DELETED, status);

	git_repository_free(repo);
	git_index_free(index);
	cl_git_pass(p_rmdir("wd"));
}