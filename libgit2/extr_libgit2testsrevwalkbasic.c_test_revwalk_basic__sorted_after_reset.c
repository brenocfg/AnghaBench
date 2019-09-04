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
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_SORT_TIME ; 
 int /*<<< orphan*/  _walk ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  commit_count ; 
 int /*<<< orphan*/  commit_head ; 
 int /*<<< orphan*/  commit_sorting_time ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_revwalk_next (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revwalk_push (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revwalk_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revwalk_sorting (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  revwalk_basic_setup_walk (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_walk_only (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void test_revwalk_basic__sorted_after_reset(void)
{
	int i = 0;
	git_oid oid;

	revwalk_basic_setup_walk(NULL);

	git_oid_fromstr(&oid, commit_head);

	/* push, sort, and test the walk */
	cl_git_pass(git_revwalk_push(_walk, &oid));
	git_revwalk_sorting(_walk, GIT_SORT_TIME);

	cl_git_pass(test_walk_only(_walk, commit_sorting_time, 2));

	/* reset, push, and test again - we should see all entries */
	git_revwalk_reset(_walk);
	cl_git_pass(git_revwalk_push(_walk, &oid));

	while (git_revwalk_next(&oid, _walk) == 0)
		i++;

	cl_assert_equal_i(i, commit_count);
}