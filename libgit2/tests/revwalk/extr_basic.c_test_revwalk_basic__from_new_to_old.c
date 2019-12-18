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
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_revwalk_hide (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ git_revwalk_next (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revwalk_push (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revwalk_sorting (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  revwalk_basic_setup_walk (int /*<<< orphan*/ *) ; 

void test_revwalk_basic__from_new_to_old(void)
{
	git_oid from_oid, to_oid, oid;
	int i = 0;

	revwalk_basic_setup_walk(NULL);
	git_revwalk_sorting(_walk, GIT_SORT_TIME);

	cl_git_pass(git_oid_fromstr(&to_oid, "5b5b025afb0b4c913b4c338a42934a3863bf3644"));
	cl_git_pass(git_oid_fromstr(&from_oid, "a4a7dce85cf63874e984719f4fdd239f5145052f"));

	cl_git_pass(git_revwalk_push(_walk, &to_oid));
	cl_git_pass(git_revwalk_hide(_walk, &from_oid));

	while (git_revwalk_next(&oid, _walk) == 0)
		i++;

	cl_assert_equal_i(i, 0);
}