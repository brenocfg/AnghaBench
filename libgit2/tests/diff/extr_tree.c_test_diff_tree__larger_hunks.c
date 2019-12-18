#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const git_patch ;
typedef  int /*<<< orphan*/  git_diff_line ;
typedef  int /*<<< orphan*/  git_diff_hunk ;
struct TYPE_3__ {int context_lines; scalar_t__ interhunk_lines; } ;

/* Variables and functions */
 int /*<<< orphan*/ * a ; 
 int /*<<< orphan*/ * b ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  diff ; 
 int /*<<< orphan*/  g_repo ; 
 size_t git_diff_num_deltas (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_diff_tree_to_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_patch_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_patch_from_diff (int /*<<< orphan*/  const**,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  git_patch_get_hunk (int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  git_patch_get_line_in_hunk (int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,size_t,size_t) ; 
 size_t git_patch_num_hunks (int /*<<< orphan*/  const*) ; 
 TYPE_1__ opts ; 
 void* resolve_commit_oid_to_tree (int /*<<< orphan*/ ,char const*) ; 

void test_diff_tree__larger_hunks(void)
{
	const char *a_commit = "d70d245ed97ed2aa596dd1af6536e4bfdb047b69";
	const char *b_commit = "7a9e0b02e63179929fed24f0a3e0f19168114d10";
	size_t d, num_d, h, num_h, l, num_l;
	git_patch *patch;
	const git_diff_hunk *hunk;
	const git_diff_line *line;

	g_repo = cl_git_sandbox_init("diff");

	cl_assert((a = resolve_commit_oid_to_tree(g_repo, a_commit)) != NULL);
	cl_assert((b = resolve_commit_oid_to_tree(g_repo, b_commit)) != NULL);

	opts.context_lines = 1;
	opts.interhunk_lines = 0;

	cl_git_pass(git_diff_tree_to_tree(&diff, g_repo, a, b, &opts));

	num_d = git_diff_num_deltas(diff);
	for (d = 0; d < num_d; ++d) {
		cl_git_pass(git_patch_from_diff(&patch, diff, d));
		cl_assert(patch);

		num_h = git_patch_num_hunks(patch);
		for (h = 0; h < num_h; h++) {
			cl_git_pass(git_patch_get_hunk(&hunk, &num_l, patch, h));

			for (l = 0; l < num_l; ++l) {
				cl_git_pass(git_patch_get_line_in_hunk(&line, patch, h, l));
				cl_assert(line);
			}

			cl_git_fail(git_patch_get_line_in_hunk(&line, patch, h, num_l));
		}

		cl_git_fail(git_patch_get_hunk(&hunk, &num_l, patch, num_h));

		git_patch_free(patch);
	}

	cl_git_fail(git_patch_from_diff(&patch, diff, num_d));

	cl_assert_equal_i(2, (int)num_d);
}