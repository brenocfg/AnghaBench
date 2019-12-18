#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;
struct TYPE_2__ {int status; } ;

/* Variables and functions */
#define  GIT_DELTA_ADDED 130 
#define  GIT_DELTA_DELETED 129 
#define  GIT_DELTA_MODIFIED 128 
 int /*<<< orphan*/  GIT_DIFF_OPTIONS_INIT ; 
 int /*<<< orphan*/  _a ; 
 int /*<<< orphan*/  _b ; 
 int /*<<< orphan*/ * _counts ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_atomic_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* git_diff_get_delta (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  git_diff_index_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t git_diff_num_deltas (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_tree_to_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *run_index_diffs(void *arg)
{
	int thread = *(int *)arg;
	git_repository *repo;
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	git_diff *diff = NULL;
	size_t i;
	int exp[4] = { 0, 0, 0, 0 };

	cl_git_pass(git_repository_open(&repo, git_repository_path(_repo)));

	switch (thread & 0x03) {
	case 0: /* diff index to workdir */;
		cl_git_pass(git_diff_index_to_workdir(&diff, repo, NULL, &opts));
		break;
	case 1: /* diff tree 'a' to index */;
		cl_git_pass(git_diff_tree_to_index(&diff, repo, _a, NULL, &opts));
		break;
	case 2: /* diff tree 'b' to index */;
		cl_git_pass(git_diff_tree_to_index(&diff, repo, _b, NULL, &opts));
		break;
	case 3: /* diff index to workdir (explicit index) */;
		{
			git_index *idx;
			cl_git_pass(git_repository_index(&idx, repo));
			cl_git_pass(git_diff_index_to_workdir(&diff, repo, idx, &opts));
			git_index_free(idx);
			break;
		}
	}

	/* keep some diff stats to make sure results are as expected */

	i = git_diff_num_deltas(diff);
	git_atomic_add(&_counts[0], (int32_t)i);
	exp[0] = (int)i;

	while (i > 0) {
		switch (git_diff_get_delta(diff, --i)->status) {
		case GIT_DELTA_MODIFIED: exp[1]++; git_atomic_inc(&_counts[1]); break;
		case GIT_DELTA_ADDED:    exp[2]++; git_atomic_inc(&_counts[2]); break;
		case GIT_DELTA_DELETED:  exp[3]++; git_atomic_inc(&_counts[3]); break;
		default: break;
		}
	}

	switch (thread & 0x03) {
	case 0: case 3:
		cl_assert_equal_i(8, exp[0]); cl_assert_equal_i(4, exp[1]);
		cl_assert_equal_i(0, exp[2]); cl_assert_equal_i(4, exp[3]);
		break;
	case 1:
		cl_assert_equal_i(12, exp[0]); cl_assert_equal_i(3, exp[1]);
		cl_assert_equal_i(7, exp[2]); cl_assert_equal_i(2, exp[3]);
		break;
	case 2:
		cl_assert_equal_i(8, exp[0]); cl_assert_equal_i(3, exp[1]);
		cl_assert_equal_i(3, exp[2]); cl_assert_equal_i(2, exp[3]);
		break;
	}

	git_diff_free(diff);
	git_repository_free(repo);
	git_error_clear();

	return arg;
}