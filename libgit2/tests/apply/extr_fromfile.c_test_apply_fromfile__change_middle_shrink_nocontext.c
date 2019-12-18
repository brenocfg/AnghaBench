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
struct TYPE_4__ {scalar_t__ context_lines; } ;
typedef  TYPE_1__ git_diff_options ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_CHANGE_MIDDLE_SHRINK ; 
 int /*<<< orphan*/  FILE_ORIGINAL ; 
 TYPE_1__ GIT_DIFF_OPTIONS_INIT ; 
 int /*<<< orphan*/  PATCH_ORIGINAL_TO_MIDDLE_SHRINK_NOCONTEXT ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_and_apply_patchfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,char*,int) ; 

void test_apply_fromfile__change_middle_shrink_nocontext(void)
{
	git_diff_options diff_opts = GIT_DIFF_OPTIONS_INIT;
	diff_opts.context_lines = 0;

	cl_git_pass(validate_and_apply_patchfile(
		FILE_ORIGINAL, strlen(FILE_ORIGINAL),
		FILE_CHANGE_MIDDLE_SHRINK, strlen(FILE_CHANGE_MIDDLE_SHRINK),
		PATCH_ORIGINAL_TO_MIDDLE_SHRINK_NOCONTEXT, &diff_opts,
		"file.txt", 0100644));
}