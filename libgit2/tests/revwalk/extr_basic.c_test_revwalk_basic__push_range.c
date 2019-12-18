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
 int /*<<< orphan*/  _walk ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  commit_sorting_segment ; 
 int /*<<< orphan*/  git_revwalk_push_range (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_revwalk_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revwalk_sorting (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  revwalk_basic_setup_walk (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_walk_only (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void test_revwalk_basic__push_range(void)
{
	revwalk_basic_setup_walk(NULL);

	git_revwalk_reset(_walk);
	git_revwalk_sorting(_walk, 0);
	cl_git_pass(git_revwalk_push_range(_walk, "9fd738e~2..9fd738e"));
	cl_git_pass(test_walk_only(_walk, commit_sorting_segment, 2));
}