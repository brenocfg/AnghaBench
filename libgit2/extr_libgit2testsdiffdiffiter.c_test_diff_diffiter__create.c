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
typedef  int /*<<< orphan*/  git_diff_delta ;
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_diff_get_delta (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  git_diff_index_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t git_diff_num_deltas (int /*<<< orphan*/ *) ; 

void test_diff_diffiter__create(void)
{
	git_repository *repo = cl_git_sandbox_init("attr");
	git_diff *diff;
	size_t d, num_d;

	cl_git_pass(git_diff_index_to_workdir(&diff, repo, NULL, NULL));

	num_d = git_diff_num_deltas(diff);
	for (d = 0; d < num_d; ++d) {
		const git_diff_delta *delta = git_diff_get_delta(diff, d);
		cl_assert(delta != NULL);
	}

	cl_assert(!git_diff_get_delta(diff, num_d));

	git_diff_free(diff);
}