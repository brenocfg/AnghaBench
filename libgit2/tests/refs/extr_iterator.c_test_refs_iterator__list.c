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
typedef  int /*<<< orphan*/  git_vector ;
typedef  int /*<<< orphan*/  git_reference_iterator ;
typedef  int /*<<< orphan*/  git_reference ;

/* Variables and functions */
 int GIT_ITEROVER ; 
 int /*<<< orphan*/  assert_all_refnames_match (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_pass (int) ; 
 int /*<<< orphan*/  git_reference_iterator_free (int /*<<< orphan*/ *) ; 
 int git_reference_iterator_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int git_reference_next (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int git_vector_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int git_vector_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcmp_cb ; 
 int /*<<< orphan*/  refnames ; 
 int /*<<< orphan*/  repo ; 

void test_refs_iterator__list(void)
{
	git_reference_iterator *iter;
	git_vector output;
	git_reference *ref;

	cl_git_pass(git_vector_init(&output, 33, &refcmp_cb));
	cl_git_pass(git_reference_iterator_new(&iter, repo));

	while (1) {
		int error = git_reference_next(&ref, iter);
		if (error == GIT_ITEROVER)
			break;
		cl_git_pass(error);
		cl_git_pass(git_vector_insert(&output, ref));
	}

	git_reference_iterator_free(iter);

	assert_all_refnames_match(refnames, &output);
}