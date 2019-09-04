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
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_branch_remote_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/ * git_error_last () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void test_refs_branches_remote__no_matching_remote_returns_error(void)
{
	const char *unknown = "refs/remotes/nonexistent/master";
	git_buf buf;

	git_error_clear();
	memset(&buf, 0, sizeof(git_buf));
	cl_git_fail_with(git_branch_remote_name(&buf, g_repo, unknown), GIT_ENOTFOUND);
	cl_assert(git_error_last() != NULL);
}