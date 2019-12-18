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
 int /*<<< orphan*/  GIT_STATUS_WT_MODIFIED ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  cl_repo_set_bool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_status_file (unsigned int*,int /*<<< orphan*/ *,char*) ; 

void test_status_worktree__line_endings_dont_count_as_changes_with_autocrlf(void)
{
	git_repository *repo = cl_git_sandbox_init("status");
	unsigned int status;

	cl_repo_set_bool(repo, "core.autocrlf", true);

	cl_git_rewritefile("status/current_file", "current_file\r\n");

	cl_git_pass(git_status_file(&status, repo, "current_file"));

	/* stat data on file should no longer match stat cache, even though
	 * file diff will be empty because of line-ending conversion - matches
	 * the Git command-line behavior here.
	 */
	cl_assert_equal_i(GIT_STATUS_WT_MODIFIED, status);
}