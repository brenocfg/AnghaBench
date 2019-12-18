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
typedef  int /*<<< orphan*/  git_patch ;
typedef  int /*<<< orphan*/  git_diff_hunk ;
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 char* PATCH_ORIGINAL_TO_CHANGE_MIDDLE ; 
 int /*<<< orphan*/  cl_assert_equal_i (size_t,size_t) ; 
 int /*<<< orphan*/  cl_git_assert_lineinfo (int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_from_buffer (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_patch_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_from_diff (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_patch_get_hunk (int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void test_diff_parse__lineinfo(void)
{
	const char *text = PATCH_ORIGINAL_TO_CHANGE_MIDDLE;
	git_diff *diff;
	git_patch *patch;
	const git_diff_hunk *hunk;
	size_t n, l = 0;

	cl_git_pass(git_diff_from_buffer(&diff, text, strlen(text)));
	cl_git_pass(git_patch_from_diff(&patch, diff, 0));
	cl_git_pass(git_patch_get_hunk(&hunk, &n, patch, 0));

	cl_git_assert_lineinfo(3, 3, 1, patch, 0, l++);
	cl_git_assert_lineinfo(4, 4, 1, patch, 0, l++);
	cl_git_assert_lineinfo(5, 5, 1, patch, 0, l++);
	cl_git_assert_lineinfo(6, -1, 1, patch, 0, l++);
	cl_git_assert_lineinfo(-1, 6, 1, patch, 0, l++);
	cl_git_assert_lineinfo(7, 7, 1, patch, 0, l++);
	cl_git_assert_lineinfo(8, 8, 1, patch, 0, l++);
	cl_git_assert_lineinfo(9, 9, 1, patch, 0, l++);

	cl_assert_equal_i(n, l);

	git_patch_free(patch);
	git_diff_free(diff);
}