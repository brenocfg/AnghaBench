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
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  _repo ; 
 int ahead ; 
 int behind ; 
 int /*<<< orphan*/  cl_assert_equal_sz (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * commit ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_commit_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_nth_gen_ancestor (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_graph_ahead_behind (int*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 

void test_graph_ahead_behind__returns_correct_result(void)
{	
	git_oid oid;
	git_oid oid2;
	git_commit *other;

	cl_git_pass(git_oid_fromstr(&oid, "e90810b8df3e80c413d903f631643c716887138d"));
	cl_git_pass(git_oid_fromstr(&oid2, "be3563ae3f795b2b4353bcce3a527ad0a4f7f644"));
	
	cl_git_pass(git_graph_ahead_behind(&ahead, &behind, _repo, &oid, &oid2));
	cl_assert_equal_sz(2, ahead);
	cl_assert_equal_sz(6, behind);

	cl_git_pass(git_graph_ahead_behind(&ahead, &behind, _repo, git_commit_id(commit), git_commit_id(commit)));
	cl_assert_equal_sz(ahead, behind);
	cl_git_pass(git_commit_nth_gen_ancestor(&other, commit, 1));

	cl_git_pass(git_graph_ahead_behind(&ahead, &behind, _repo, git_commit_id(commit), git_commit_id(other)));
	cl_assert_equal_sz(ahead, behind + 2);
	cl_git_pass(git_graph_ahead_behind(&ahead, &behind, _repo, git_commit_id(other), git_commit_id(commit)));
	cl_assert_equal_sz(ahead + 2, behind);

	git_commit_free(other);

	cl_git_pass(git_commit_nth_gen_ancestor(&other, commit, 3));

	cl_git_pass(git_graph_ahead_behind(&ahead, &behind, _repo, git_commit_id(commit), git_commit_id(other)));
	cl_assert_equal_sz(ahead, behind + 4);
	cl_git_pass(git_graph_ahead_behind(&ahead, &behind, _repo, git_commit_id(other), git_commit_id(commit)));
	cl_assert_equal_sz(ahead + 4, behind);

	git_commit_free(other);
}