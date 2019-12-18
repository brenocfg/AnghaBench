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
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_assert_equal_sz (size_t,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_graph_ahead_behind (size_t*,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_merge_base (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 

void test_revwalk_mergebase__merged_branch(void)
{
	git_oid result, one, two, expected;
	size_t ahead, behind;

	cl_git_pass(git_oid_fromstr(&one, "a65fedf39aefe402d3bb6e24df4d4f5fe4547750"));
	cl_git_pass(git_oid_fromstr(&two, "9fd738e8f7967c078dceed8190330fc8648ee56a"));
	cl_git_pass(git_oid_fromstr(&expected, "9fd738e8f7967c078dceed8190330fc8648ee56a"));

	cl_git_pass(git_merge_base(&result, _repo, &one, &two));
	cl_assert_equal_oid(&expected, &result);

	cl_git_pass(git_merge_base(&result, _repo, &two, &one));
	cl_assert_equal_oid(&expected, &result);

	cl_git_pass(git_graph_ahead_behind(&ahead, &behind, _repo, &one, &two));
	cl_assert_equal_sz(ahead,  3);
	cl_assert_equal_sz(behind,  0);

	cl_git_pass(git_graph_ahead_behind(&ahead, &behind, _repo, &two, &one));
	cl_assert_equal_sz(ahead,  0);
	cl_assert_equal_sz(behind,  3);
}