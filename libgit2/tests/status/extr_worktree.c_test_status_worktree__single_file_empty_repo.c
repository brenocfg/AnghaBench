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

/* Variables and functions */
 unsigned int GIT_STATUS_WT_NEW ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_status_file (unsigned int*,int /*<<< orphan*/ *,char*) ; 

void test_status_worktree__single_file_empty_repo(void)
{
	unsigned int status_flags;
	git_repository *repo = cl_git_sandbox_init("empty_standard_repo");

	cl_git_mkfile("empty_standard_repo/new_file", "new_file\n");

	cl_git_pass(git_status_file(&status_flags, repo, "new_file"));
	cl_assert(status_flags == GIT_STATUS_WT_NEW);
}