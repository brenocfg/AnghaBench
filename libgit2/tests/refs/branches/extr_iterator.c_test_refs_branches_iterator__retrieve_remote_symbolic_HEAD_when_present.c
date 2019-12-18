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
typedef  int /*<<< orphan*/  git_branch_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BRANCH_REMOTE ; 
 int /*<<< orphan*/  assert_branch_has_been_found (struct expectations*,char*) ; 
 int /*<<< orphan*/  assert_retrieval (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  contains_branches (struct expectations*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fake_remote ; 
 int /*<<< orphan*/  git_branch_iterator_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_branch_iterator_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_symbolic_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  repo ; 

void test_refs_branches_iterator__retrieve_remote_symbolic_HEAD_when_present(void)
{
	git_branch_iterator *iter;
	struct expectations exp[] = {
		{ "nulltoken/HEAD", 0 },
		{ "nulltoken/master", 0 },
		{ NULL, 0 }
	};

	git_reference_free(fake_remote);
	cl_git_pass(git_reference_symbolic_create(&fake_remote, repo, "refs/remotes/nulltoken/HEAD", "refs/remotes/nulltoken/master", 0, NULL));

	assert_retrieval(GIT_BRANCH_REMOTE, 3);

	cl_git_pass(git_branch_iterator_new(&iter, repo, GIT_BRANCH_REMOTE));
	contains_branches(exp, iter);
	git_branch_iterator_free(iter);

	assert_branch_has_been_found(exp, "nulltoken/HEAD");
	assert_branch_has_been_found(exp, "nulltoken/master");
}