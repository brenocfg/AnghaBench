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
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/ * cl_git_sandbox_reopen () ; 
 int /*<<< orphan*/  cl_repo_set_bool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_status_file (unsigned int*,int /*<<< orphan*/ *,char*) ; 

void test_status_worktree__file_status_honors_case_ignorecase_regarding_untracked_files(void)
{
    git_repository *repo = cl_git_sandbox_init("status");
    unsigned int status;
    git_index *index;

    cl_repo_set_bool(repo, "core.ignorecase", false);

	repo = cl_git_sandbox_reopen();

    /* Actually returns GIT_STATUS_IGNORED on Windows */
    cl_git_fail_with(git_status_file(&status, repo, "NEW_FILE"), GIT_ENOTFOUND);

    cl_git_pass(git_repository_index(&index, repo));

    cl_git_pass(git_index_add_bypath(index, "new_file"));
    cl_git_pass(git_index_write(index));
    git_index_free(index);

    /* Actually returns GIT_STATUS_IGNORED on Windows */
    cl_git_fail_with(git_status_file(&status, repo, "NEW_FILE"), GIT_ENOTFOUND);
}