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
 int /*<<< orphan*/  GIT_STATUS_INDEX_NEW ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_repo_set_bool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  cl_set_cleanup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cleanup_new_repo ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_status_file (unsigned int*,int /*<<< orphan*/ *,char*) ; 

void test_status_worktree_init__new_staged_file_must_handle_crlf(void)
{
	git_repository *repo;
	git_index *index;
	unsigned int status;

	cl_set_cleanup(&cleanup_new_repo, "getting_started");
	cl_git_pass(git_repository_init(&repo, "getting_started", 0));

	/* Ensure that repo has core.autocrlf=true */
	cl_repo_set_bool(repo, "core.autocrlf", true);

	cl_git_mkfile("getting_started/testfile.txt", "content\r\n");	/* Content with CRLF */

	cl_git_pass(git_repository_index(&index, repo));
	cl_git_pass(git_index_add_bypath(index, "testfile.txt"));
	cl_git_pass(git_index_write(index));

	cl_git_pass(git_status_file(&status, repo, "testfile.txt"));
	cl_assert_equal_i(GIT_STATUS_INDEX_NEW, status);

	git_index_free(index);
	git_repository_free(repo);
}