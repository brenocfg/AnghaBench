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
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_index_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_num_deltas (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_race () ; 

void test_index_racy__detects_diff_of_change_in_identical_timestamp(void)
{
	git_index *index;
	git_diff *diff;

	cl_git_pass(git_repository_index__weakptr(&index, g_repo));

	setup_race();

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, index, NULL));
	cl_assert_equal_i(1, git_diff_num_deltas(diff));

	git_diff_free(diff);
}