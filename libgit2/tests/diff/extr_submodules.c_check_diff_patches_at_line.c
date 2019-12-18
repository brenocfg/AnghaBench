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
typedef  int /*<<< orphan*/  git_patch ;
struct TYPE_3__ {scalar_t__ status; } ;
typedef  TYPE_1__ git_diff_delta ;
typedef  int /*<<< orphan*/  git_diff ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 scalar_t__ GIT_DELTA_UNMODIFIED ; 
 scalar_t__ GIT_DELTA_UNTRACKED ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_at_line (int,char const*,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clar__assert_equal (char const*,int,char*,int,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_buf_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 size_t git_diff_num_deltas (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_from_diff (int /*<<< orphan*/ **,int /*<<< orphan*/ *,size_t) ; 
 TYPE_1__* git_patch_get_delta (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_to_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static void check_diff_patches_at_line(
	git_diff *diff, const char **expected, const char *file, int line)
{
	const git_diff_delta *delta;
	git_patch *patch = NULL;
	size_t d, num_d = git_diff_num_deltas(diff);
	git_buf buf = GIT_BUF_INIT;

	for (d = 0; d < num_d; ++d, git_patch_free(patch)) {
		cl_git_pass(git_patch_from_diff(&patch, diff, d));
		cl_assert((delta = git_patch_get_delta(patch)) != NULL);

		if (delta->status == GIT_DELTA_UNMODIFIED) {
			cl_assert_at_line(expected[d] == NULL, file, line);
			continue;
		}

		if (expected[d] && !strcmp(expected[d], "<SKIP>"))
			continue;
		if (expected[d] && !strcmp(expected[d], "<UNTRACKED>")) {
			cl_assert_at_line(delta->status == GIT_DELTA_UNTRACKED, file, line);
			continue;
		}
		if (expected[d] && !strcmp(expected[d], "<END>")) {
			cl_git_pass(git_patch_to_buf(&buf, patch));
			cl_assert_at_line(!strcmp(expected[d], "<END>"), file, line);
		}

		cl_git_pass(git_patch_to_buf(&buf, patch));

		clar__assert_equal(
			file, line, "expected diff did not match actual diff", 1,
			"%s", expected[d], get_buf_ptr(&buf));
		git_buf_dispose(&buf);
	}

	cl_assert_at_line(expected[d] && !strcmp(expected[d], "<END>"), file, line);
}