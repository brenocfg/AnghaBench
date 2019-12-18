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
typedef  int /*<<< orphan*/  git_reference_iterator ;

/* Variables and functions */
 size_t GIT_ITEROVER ; 
 int /*<<< orphan*/  cl_assert_equal_i (size_t,size_t) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_cleanup () ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_reference_iterator_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_iterator_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int git_reference_next_name (char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_remove (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  repo ; 

void test_refs_iterator__concurrent_delete(void)
{
	git_reference_iterator *iter;
	size_t full_count = 0, concurrent_count = 0;
	const char *name;
	int error;

	cl_git_sandbox_cleanup();
	repo = cl_git_sandbox_init("testrepo");

	cl_git_pass(git_reference_iterator_new(&iter, repo));
	while ((error = git_reference_next_name(&name, iter)) == 0) {
		full_count++;
	}

	git_reference_iterator_free(iter);
	cl_assert_equal_i(GIT_ITEROVER, error);

	cl_git_pass(git_reference_iterator_new(&iter, repo));
	while ((error = git_reference_next_name(&name, iter)) == 0) {
		cl_git_pass(git_reference_remove(repo, name));
		concurrent_count++;
	}

	git_reference_iterator_free(iter);
	cl_assert_equal_i(GIT_ITEROVER, error);

	cl_assert_equal_i(full_count, concurrent_count);
}