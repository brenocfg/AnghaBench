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
 int /*<<< orphan*/  GIT_EINVALIDSPEC ; 
 int /*<<< orphan*/  _walk ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revwalk_push_range (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_revwalk_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revwalk_sorting (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  revwalk_basic_setup_walk (int /*<<< orphan*/ *) ; 

void test_revwalk_basic__push_range_merge_base(void)
{
	revwalk_basic_setup_walk(NULL);

	git_revwalk_reset(_walk);
	git_revwalk_sorting(_walk, 0);
	cl_git_fail_with(GIT_EINVALIDSPEC, git_revwalk_push_range(_walk, "HEAD...HEAD~2"));
}