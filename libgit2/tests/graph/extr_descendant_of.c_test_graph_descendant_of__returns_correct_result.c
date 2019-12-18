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
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * commit ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_nth_gen_ancestor (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_graph_descendant_of (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void test_graph_descendant_of__returns_correct_result(void)
{
	git_commit *other;

	cl_assert_equal_i(0, git_graph_descendant_of(_repo, git_commit_id(commit), git_commit_id(commit)));


	cl_git_pass(git_commit_nth_gen_ancestor(&other, commit, 1));

	cl_assert_equal_i(1, git_graph_descendant_of(_repo, git_commit_id(commit), git_commit_id(other)));
	cl_assert_equal_i(0, git_graph_descendant_of(_repo, git_commit_id(other), git_commit_id(commit)));

	git_commit_free(other);


	cl_git_pass(git_commit_nth_gen_ancestor(&other, commit, 3));

	cl_assert_equal_i(1, git_graph_descendant_of(_repo, git_commit_id(commit), git_commit_id(other)));
	cl_assert_equal_i(0, git_graph_descendant_of(_repo, git_commit_id(other), git_commit_id(commit)));

	git_commit_free(other);

}