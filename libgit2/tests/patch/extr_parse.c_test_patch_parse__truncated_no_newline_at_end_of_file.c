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
struct TYPE_3__ {int /*<<< orphan*/  content; } ;
typedef  TYPE_1__ git_diff_line ;

/* Variables and functions */
 char* PATCH_APPEND_NO_NL ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_patch_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_from_buffer (int /*<<< orphan*/ **,char*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_get_line_in_hunk (TYPE_1__ const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 size_t strlen (char*) ; 

void test_patch_parse__truncated_no_newline_at_end_of_file(void)
{
	size_t len = strlen(PATCH_APPEND_NO_NL) - strlen("at end of file\n");
	const git_diff_line *line;
	git_patch *patch;

	cl_git_pass(git_patch_from_buffer(&patch, PATCH_APPEND_NO_NL, len, NULL));
	cl_git_pass(git_patch_get_line_in_hunk(&line, patch, 0, 4));
	cl_assert_equal_s(line->content, "\\ No newline ");

	git_patch_free(patch);
}