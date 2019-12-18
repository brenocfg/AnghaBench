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

/* Variables and functions */
 int /*<<< orphan*/  GIT_RESET_MIXED ; 
 unsigned int GIT_STATUS_CURRENT ; 
 unsigned int GIT_STATUS_WT_NEW ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_status_file (unsigned int*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  target ; 

void test_reset_mixed__resetting_refreshes_the_index_to_the_commit_tree(void)
{
	unsigned int status;

	cl_git_pass(git_status_file(&status, repo, "macro_bad"));
	cl_assert(status == GIT_STATUS_CURRENT);
	cl_git_pass(git_revparse_single(&target, repo, "605812a"));

	cl_git_pass(git_reset(repo, target, GIT_RESET_MIXED, NULL));

	cl_git_pass(git_status_file(&status, repo, "macro_bad"));
	cl_assert(status == GIT_STATUS_WT_NEW);
}