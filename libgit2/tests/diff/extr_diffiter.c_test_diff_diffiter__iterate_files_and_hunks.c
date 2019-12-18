#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  const git_patch ;
struct TYPE_4__ {int context_lines; int interhunk_lines; int flags; } ;
typedef  TYPE_1__ git_diff_options ;
typedef  int /*<<< orphan*/  git_diff_hunk ;
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 int GIT_DIFF_INCLUDE_IGNORED ; 
 int GIT_DIFF_INCLUDE_UNTRACKED ; 
 TYPE_1__ GIT_DIFF_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_index_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 size_t git_diff_num_deltas (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_patch_from_diff (int /*<<< orphan*/  const**,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  git_patch_get_hunk (int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 size_t git_patch_num_hunks (int /*<<< orphan*/  const*) ; 

void test_diff_diffiter__iterate_files_and_hunks(void)
{
	git_repository *repo = cl_git_sandbox_init("status");
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	git_diff *diff = NULL;
	size_t d, num_d;
	int file_count = 0, hunk_count = 0;

	opts.context_lines = 3;
	opts.interhunk_lines = 1;
	opts.flags |= GIT_DIFF_INCLUDE_IGNORED | GIT_DIFF_INCLUDE_UNTRACKED;

	cl_git_pass(git_diff_index_to_workdir(&diff, repo, NULL, &opts));

	num_d = git_diff_num_deltas(diff);

	for (d = 0; d < num_d; ++d) {
		git_patch *patch;
		size_t h, num_h;

		cl_git_pass(git_patch_from_diff(&patch, diff, d));
		cl_assert(patch);

		file_count++;

		num_h = git_patch_num_hunks(patch);

		for (h = 0; h < num_h; h++) {
			const git_diff_hunk *hunk;

			cl_git_pass(git_patch_get_hunk(&hunk, NULL, patch, h));
			cl_assert(hunk);

			hunk_count++;
		}

		git_patch_free(patch);
	}

	cl_assert_equal_i(13, file_count);
	cl_assert_equal_i(8, hunk_count);

	git_diff_free(diff);
}