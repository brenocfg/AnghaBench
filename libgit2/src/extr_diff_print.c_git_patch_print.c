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
typedef  scalar_t__ git_diff_line_cb ;
typedef  int /*<<< orphan*/  git_buf ;
typedef  int /*<<< orphan*/  diff_print_info ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_DIFF_FORMAT_PATCH ; 
 int /*<<< orphan*/  assert (int) ; 
 int diff_print_info_init_frompatch (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,void*) ; 
 int /*<<< orphan*/  diff_print_patch_binary ; 
 int /*<<< orphan*/  diff_print_patch_file ; 
 int /*<<< orphan*/  diff_print_patch_hunk ; 
 int /*<<< orphan*/  diff_print_patch_line ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set_after_callback_function (int,char*) ; 
 int git_patch__invoke_callbacks (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int git_patch_print(
	git_patch *patch,
	git_diff_line_cb print_cb,
	void *payload)
{
	int error;
	git_buf temp = GIT_BUF_INIT;
	diff_print_info pi;

	assert(patch && print_cb);

	if (!(error = diff_print_info_init_frompatch(
		&pi, &temp, patch,
		GIT_DIFF_FORMAT_PATCH, print_cb, payload)))
	{
		error = git_patch__invoke_callbacks(
			patch,
			diff_print_patch_file, diff_print_patch_binary,
			diff_print_patch_hunk, diff_print_patch_line,
			&pi);

		if (error) /* make sure error message is set */
			git_error_set_after_callback_function(error, "git_patch_print");
	}

	git_buf_dispose(&temp);

	return error;
}