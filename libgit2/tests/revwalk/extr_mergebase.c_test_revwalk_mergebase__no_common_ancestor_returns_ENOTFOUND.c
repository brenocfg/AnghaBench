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
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_assert_equal_sz (int,size_t) ; 
 int /*<<< orphan*/  cl_git_fail (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_graph_ahead_behind (size_t*,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_merge_base (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 

void test_revwalk_mergebase__no_common_ancestor_returns_ENOTFOUND(void)
{
	git_oid result, one, two;
	size_t ahead, behind;
	int error;

	cl_git_pass(git_oid_fromstr(&one, "763d71aadf09a7951596c9746c024e7eece7c7af"));
	cl_git_pass(git_oid_fromstr(&two, "e90810b8df3e80c413d903f631643c716887138d"));

	error = git_merge_base(&result, _repo, &one, &two);
	cl_git_fail(error);

	cl_assert_equal_i(GIT_ENOTFOUND, error);

	cl_git_pass(git_graph_ahead_behind(&ahead, &behind, _repo, &one, &two));
	cl_assert_equal_sz(4, ahead);
	cl_assert_equal_sz(2, behind);
}