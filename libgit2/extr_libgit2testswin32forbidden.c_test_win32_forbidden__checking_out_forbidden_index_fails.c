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

/* Variables and functions */

void test_win32_forbidden__checking_out_forbidden_index_fails(void)
{
#ifdef GIT_WIN32
	git_index *index;
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;
	git_diff *diff;
	const git_diff_delta *delta;
	git_tree *tree;
	size_t num_deltas, i;

	opts.checkout_strategy = GIT_CHECKOUT_FORCE;

	cl_git_pass(git_repository_index(&index, repo));
	cl_git_fail(git_checkout_index(repo, index, &opts));

	cl_git_pass(git_repository_head_tree(&tree, repo));
	cl_git_pass(git_diff_index_to_workdir(&diff, repo, index, NULL));

	num_deltas = git_diff_num_deltas(diff);

	cl_assert(num_deltas > 0);

	for (i = 0; i < num_deltas; i++) {
		delta = git_diff_get_delta(diff, i);
		cl_assert_equal_i(GIT_DELTA_DELETED, delta->status);
	}

	git_diff_free(diff);
	git_tree_free(tree);
	git_index_free(index);
#endif
}