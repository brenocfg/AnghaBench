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

/* Variables and functions */
 int /*<<< orphan*/  FILE_CHANGE_FIRSTLINE ; 
 int /*<<< orphan*/  FILE_ORIGINAL ; 
 int /*<<< orphan*/  PATCH_ORIGINAL_TO_CHANGE_FIRSTLINE ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_and_apply_patchfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 

void test_apply_fromfile__change_firstline(void)
{
	cl_git_pass(validate_and_apply_patchfile(
		FILE_ORIGINAL, strlen(FILE_ORIGINAL),
		FILE_CHANGE_FIRSTLINE, strlen(FILE_CHANGE_FIRSTLINE),
		PATCH_ORIGINAL_TO_CHANGE_FIRSTLINE, NULL,
		"file.txt", 0100644));
}