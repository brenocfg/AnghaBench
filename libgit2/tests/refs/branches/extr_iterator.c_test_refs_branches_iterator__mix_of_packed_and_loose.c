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
struct expectations {char* member_0; int /*<<< orphan*/  member_1; } ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_branch_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BRANCH_ALL ; 
 int /*<<< orphan*/  assert_branch_has_been_found (struct expectations*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  contains_branches (struct expectations*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_branch_iterator_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_branch_iterator_new (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void test_refs_branches_iterator__mix_of_packed_and_loose(void)
{
	git_branch_iterator *iter;
	struct expectations exp[] = {
		{ "master", 0 },
		{ "origin/HEAD", 0 },
		{ "origin/master", 0 },
		{ "origin/packed", 0 },
		{ NULL, 0 }
	};
	git_repository *r2;

	r2 = cl_git_sandbox_init("testrepo2");

	cl_git_pass(git_branch_iterator_new(&iter, r2, GIT_BRANCH_ALL));
	contains_branches(exp, iter);

	git_branch_iterator_free(iter);

	assert_branch_has_been_found(exp, "master");
	assert_branch_has_been_found(exp, "origin/HEAD");
	assert_branch_has_been_found(exp, "origin/master");
	assert_branch_has_been_found(exp, "origin/packed");
}