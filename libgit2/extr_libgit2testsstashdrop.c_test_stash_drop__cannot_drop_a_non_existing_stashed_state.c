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
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_stash_drop (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  push_three_states () ; 
 int /*<<< orphan*/  repo ; 

void test_stash_drop__cannot_drop_a_non_existing_stashed_state(void)
{
	push_three_states();

	cl_git_fail_with(git_stash_drop(repo, 666), GIT_ENOTFOUND);
	cl_git_fail_with(git_stash_drop(repo, 42), GIT_ENOTFOUND);
	cl_git_fail_with(git_stash_drop(repo, 3), GIT_ENOTFOUND);
}