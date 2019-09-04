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
typedef  int /*<<< orphan*/  git_revwalk ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int GIT_ITEROVER ; 
 int /*<<< orphan*/  GIT_SORT_TOPOLOGICAL ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  commit_head ; 
 int /*<<< orphan*/ * expected_str ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revwalk_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revwalk_new (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int git_revwalk_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revwalk_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revwalk_simplify_first_parent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revwalk_sorting (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void test_revwalk_simplify__first_parent(void)
{
	git_repository *repo;
	git_revwalk *walk;
	git_oid id, expected[4];
	int i, error;

	for (i = 0; i < 4; i++) {
		git_oid_fromstr(&expected[i], expected_str[i]);
	}

	repo = cl_git_sandbox_init("testrepo.git");
	cl_git_pass(git_revwalk_new(&walk, repo));

	git_oid_fromstr(&id, commit_head);
	cl_git_pass(git_revwalk_push(walk, &id));
	git_revwalk_sorting(walk, GIT_SORT_TOPOLOGICAL);
	git_revwalk_simplify_first_parent(walk);

	i = 0;
	while ((error = git_revwalk_next(&id, walk)) == 0) {
		cl_assert_equal_oid(&expected[i], &id);
		i++;
	}

	cl_assert_equal_i(i, 4);
	cl_assert_equal_i(error, GIT_ITEROVER);

	git_revwalk_free(walk);
}