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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference_iterator ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_odb ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ITEROVER ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_odb_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_new (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_reference_iterator_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_iterator_new (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_next (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_wrap_odb (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

void test_refs_iterator__empty(void)
{
	git_reference_iterator *iter;
	git_odb *odb;
	git_reference *ref;
	git_repository *empty;

	cl_git_pass(git_odb_new(&odb));
	cl_git_pass(git_repository_wrap_odb(&empty, odb));

	cl_git_pass(git_reference_iterator_new(&iter, empty));
	cl_assert_equal_i(GIT_ITEROVER, git_reference_next(&ref, iter));

	git_reference_iterator_free(iter);
	git_odb_free(odb);
	git_repository_free(empty);
}