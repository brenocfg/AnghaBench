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
 int /*<<< orphan*/  FILE_ORIGINAL ; 
 int /*<<< orphan*/  PATCH_MODECHANGE_UNCHANGED ; 
 int /*<<< orphan*/  apply_patchfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

void test_apply_fromfile__modechange(void)
{
	cl_git_pass(apply_patchfile(
		FILE_ORIGINAL, strlen(FILE_ORIGINAL),
		FILE_ORIGINAL, strlen(FILE_ORIGINAL),
		PATCH_MODECHANGE_UNCHANGED, "file.txt", 0100755));
}