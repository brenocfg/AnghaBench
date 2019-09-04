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
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_EUNCOMMITTED ; 
 int /*<<< orphan*/  GIT_STATUS_CURRENT ; 
 int /*<<< orphan*/  GIT_STATUS_INDEX_MODIFIED ; 
 int /*<<< orphan*/  assert_status (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_index_has_conflicts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_stash_apply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  repo_index ; 

void test_stash_apply__fails_with_uncommitted_changes_in_index(void)
{
	cl_git_rewritefile("stash/who", "nothing\n");
	cl_git_pass(git_index_add_bypath(repo_index, "who"));
	cl_git_pass(git_index_write(repo_index));

	cl_git_fail_with(git_stash_apply(repo, 0, NULL), GIT_EUNCOMMITTED);

	cl_assert_equal_i(git_index_has_conflicts(repo_index), 0);
	assert_status(repo, "what", GIT_STATUS_CURRENT);
	assert_status(repo, "how", GIT_STATUS_CURRENT);
	assert_status(repo, "who", GIT_STATUS_INDEX_MODIFIED);
	assert_status(repo, "when", GIT_ENOTFOUND);
	assert_status(repo, "why", GIT_ENOTFOUND);
}