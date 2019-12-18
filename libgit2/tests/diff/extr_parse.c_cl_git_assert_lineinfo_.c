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
struct TYPE_3__ {int /*<<< orphan*/  num_lines; int /*<<< orphan*/  new_lineno; int /*<<< orphan*/  old_lineno; } ;
typedef  TYPE_1__ git_diff_line ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_i_src (int,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  cl_git_expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  git_patch_get_line_in_hunk (TYPE_1__ const**,int /*<<< orphan*/ *,size_t,size_t) ; 

__attribute__((used)) static void cl_git_assert_lineinfo_(int old_lineno, int new_lineno, int num_lines, git_patch *patch, size_t hunk_idx, size_t line_idx, const char *file, int lineno)
{
	const git_diff_line *line;

	cl_git_expect(git_patch_get_line_in_hunk(&line, patch, hunk_idx, line_idx), 0, file, lineno);
	cl_assert_equal_i_src(old_lineno, line->old_lineno, file, lineno);
	cl_assert_equal_i_src(new_lineno, line->new_lineno, file, lineno);
	cl_assert_equal_i_src(num_lines, line->num_lines, file, lineno);
}