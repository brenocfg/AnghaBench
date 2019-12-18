#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_12__ {int flags; } ;
typedef  TYPE_1__ const git_patch ;
struct TYPE_13__ {int context_lines; int interhunk_lines; int flags; int max_size; } ;
typedef  TYPE_2__ git_diff_options ;
typedef  TYPE_1__ git_diff_delta ;
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 int GIT_DIFF_FLAG_BINARY ; 
 int GIT_DIFF_FLAG_NOT_BINARY ; 
 int GIT_DIFF_INCLUDE_IGNORED ; 
 int GIT_DIFF_INCLUDE_UNTRACKED ; 
 TYPE_2__ GIT_DIFF_OPTIONS_INIT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cl_assert (TYPE_1__ const*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_index_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 size_t git_diff_num_deltas (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_free (TYPE_1__ const*) ; 
 int /*<<< orphan*/  git_patch_from_diff (TYPE_1__ const**,int /*<<< orphan*/ *,size_t) ; 
 TYPE_1__* git_patch_get_delta (TYPE_1__ const*) ; 
 scalar_t__ git_patch_num_hunks (TYPE_1__ const*) ; 

void test_diff_diffiter__max_size_threshold(void)
{
	git_repository *repo = cl_git_sandbox_init("status");
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	git_diff *diff = NULL;
	int file_count = 0, binary_count = 0, hunk_count = 0;
	size_t d, num_d;

	opts.context_lines = 3;
	opts.interhunk_lines = 1;
	opts.flags |= GIT_DIFF_INCLUDE_IGNORED | GIT_DIFF_INCLUDE_UNTRACKED;

	cl_git_pass(git_diff_index_to_workdir(&diff, repo, NULL, &opts));
	num_d = git_diff_num_deltas(diff);

	for (d = 0; d < num_d; ++d) {
		git_patch *patch;
		const git_diff_delta *delta;

		cl_git_pass(git_patch_from_diff(&patch, diff, d));
		cl_assert(patch);
		delta = git_patch_get_delta(patch);
		cl_assert(delta);

		file_count++;
		hunk_count += (int)git_patch_num_hunks(patch);

		assert((delta->flags & (GIT_DIFF_FLAG_BINARY|GIT_DIFF_FLAG_NOT_BINARY)) != 0);
		binary_count += ((delta->flags & GIT_DIFF_FLAG_BINARY) != 0);

		git_patch_free(patch);
	}

	cl_assert_equal_i(13, file_count);
	cl_assert_equal_i(0, binary_count);
	cl_assert_equal_i(8, hunk_count);

	git_diff_free(diff);

	/* try again with low file size threshold */

	file_count = binary_count = hunk_count = 0;

	opts.context_lines = 3;
	opts.interhunk_lines = 1;
	opts.flags |= GIT_DIFF_INCLUDE_IGNORED | GIT_DIFF_INCLUDE_UNTRACKED;
	opts.max_size = 50; /* treat anything over 50 bytes as binary! */

	cl_git_pass(git_diff_index_to_workdir(&diff, repo, NULL, &opts));
	num_d = git_diff_num_deltas(diff);

	for (d = 0; d < num_d; ++d) {
		git_patch *patch;
		const git_diff_delta *delta;

		cl_git_pass(git_patch_from_diff(&patch, diff, d));
		delta = git_patch_get_delta(patch);

		file_count++;
		hunk_count += (int)git_patch_num_hunks(patch);

		assert((delta->flags & (GIT_DIFF_FLAG_BINARY|GIT_DIFF_FLAG_NOT_BINARY)) != 0);
		binary_count += ((delta->flags & GIT_DIFF_FLAG_BINARY) != 0);

		git_patch_free(patch);
	}

	cl_assert_equal_i(13, file_count);
	/* Three files are over the 50 byte threshold:
	 * - staged_changes_file_deleted
	 * - staged_changes_modified_file
	 * - staged_new_file_modified_file
	 */
	cl_assert_equal_i(3, binary_count);
	cl_assert_equal_i(5, hunk_count);

	git_diff_free(diff);
}