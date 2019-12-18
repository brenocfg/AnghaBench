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
typedef  int /*<<< orphan*/  git_reference ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_REFS_STASH_FILE ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_stash_drop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_three_states () ; 
 int /*<<< orphan*/  repo ; 

void test_stash_drop__dropping_the_last_entry_removes_the_stash(void)
{
	git_reference *stash;

	push_three_states();

	cl_git_pass(git_reference_lookup(&stash, repo, GIT_REFS_STASH_FILE));
	git_reference_free(stash);

	cl_git_pass(git_stash_drop(repo, 0));
	cl_git_pass(git_stash_drop(repo, 0));
	cl_git_pass(git_stash_drop(repo, 0));

	cl_git_fail_with(
		git_reference_lookup(&stash, repo, GIT_REFS_STASH_FILE), GIT_ENOTFOUND);
}