#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_patch ;
struct TYPE_7__ {int context_lines; int interhunk_lines; int flags; } ;
typedef  TYPE_1__ git_diff_options ;
struct TYPE_8__ {scalar_t__ content; } ;
typedef  TYPE_2__ git_diff_line ;
typedef  int /*<<< orphan*/  git_diff_hunk ;
typedef  int /*<<< orphan*/  git_diff ;
struct TYPE_9__ {int /*<<< orphan*/  lines; int /*<<< orphan*/  hunks; int /*<<< orphan*/  files; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ diff_expects ;

/* Variables and functions */
 int GIT_DIFF_INCLUDE_IGNORED ; 
 int GIT_DIFF_INCLUDE_UNTRACKED ; 
 TYPE_1__ GIT_DIFF_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_index_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 size_t git_diff_num_deltas (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_from_diff (int /*<<< orphan*/ **,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  git_patch_get_hunk (int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  git_patch_get_line_in_hunk (TYPE_2__ const**,int /*<<< orphan*/ *,size_t,size_t) ; 
 size_t git_patch_num_hunks (int /*<<< orphan*/ *) ; 

void test_diff_diffiter__iterate_all(void)
{
	git_repository *repo = cl_git_sandbox_init("status");
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	git_diff *diff = NULL;
	diff_expects exp = {0};
	size_t d, num_d;

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
		exp.files++;

		num_h = git_patch_num_hunks(patch);
		for (h = 0; h < num_h; h++) {
			const git_diff_hunk *range;
			size_t l, num_l;

			cl_git_pass(git_patch_get_hunk(&range, &num_l, patch, h));
			cl_assert(range);
			exp.hunks++;

			for (l = 0; l < num_l; ++l) {
				const git_diff_line *line;

				cl_git_pass(git_patch_get_line_in_hunk(&line, patch, h, l));
				cl_assert(line && line->content);
				exp.lines++;
			}
		}

		git_patch_free(patch);
	}

	cl_assert_equal_i(13, exp.files);
	cl_assert_equal_i(8, exp.hunks);
	cl_assert_equal_i(14, exp.lines);

	git_diff_free(diff);
}