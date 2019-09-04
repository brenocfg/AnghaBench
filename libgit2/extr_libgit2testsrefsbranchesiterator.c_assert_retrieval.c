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
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_branch_t ;
typedef  int /*<<< orphan*/  git_branch_iterator ;

/* Variables and functions */
 int GIT_ITEROVER ; 
 int /*<<< orphan*/  cl_assert_equal_i (unsigned int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_branch_iterator_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_branch_iterator_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ,unsigned int) ; 
 int git_branch_next (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  repo ; 

__attribute__((used)) static void assert_retrieval(unsigned int flags, unsigned int expected_count)
{
	git_branch_iterator *iter;
	git_reference *ref;
	int count = 0, error;
	git_branch_t type;

	cl_git_pass(git_branch_iterator_new(&iter, repo, flags));
	while ((error = git_branch_next(&ref, &type, iter)) == 0) {
		count++;
		git_reference_free(ref);
	}

	git_branch_iterator_free(iter);
	cl_assert_equal_i(error, GIT_ITEROVER);
	cl_assert_equal_i(expected_count, count);
}