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
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_fail (int) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int git_status_file (unsigned int*,int /*<<< orphan*/ *,char*) ; 

void test_status_worktree__single_nonexistent_file_empty_repo(void)
{
	int error;
	unsigned int status_flags;
	git_repository *repo = cl_git_sandbox_init("empty_standard_repo");

	error = git_status_file(&status_flags, repo, "nonexistent");
	cl_git_fail(error);
	cl_assert(error == GIT_ENOTFOUND);
}