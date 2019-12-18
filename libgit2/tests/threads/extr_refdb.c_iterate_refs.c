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
struct th_data {int /*<<< orphan*/  path; } ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference_iterator ;
typedef  int /*<<< orphan*/  git_reference ;

/* Variables and functions */
 int GIT_ELOCKED ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (scalar_t__,int) ; 
 int /*<<< orphan*/  cl_git_thread_pass (struct th_data*,int) ; 
 scalar_t__ g_expected ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_iterator_free (int /*<<< orphan*/ *) ; 
 int git_reference_iterator_new (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_next (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int git_repository_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *iterate_refs(void *arg)
{
	struct th_data *data = (struct th_data *) arg;
	git_reference_iterator *i;
	git_reference *ref;
	int count = 0, error;
	git_repository *repo;

	cl_git_thread_pass(data, git_repository_open(&repo, data->path));
	do {
		error = git_reference_iterator_new(&i, repo);
	} while (error == GIT_ELOCKED);
	cl_git_thread_pass(data, error);

	for (count = 0; !git_reference_next(&ref, i); ++count) {
		cl_assert(ref != NULL);
		git_reference_free(ref);
	}

	if (g_expected > 0)
		cl_assert_equal_i(g_expected, count);

	git_reference_iterator_free(i);

	git_repository_free(repo);
	git_error_clear();
	return arg;
}