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
 int /*<<< orphan*/  FILE_CHANGE_MIDDLE ; 
 int /*<<< orphan*/  FILE_ORIGINAL ; 
 int /*<<< orphan*/  PATCH_RENAME_SIMILAR_QUOTEDNAME ; 
 int /*<<< orphan*/  apply_patchfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

void test_apply_fromfile__rename_similar_quotedname(void)
{
	cl_git_pass(apply_patchfile(
		FILE_ORIGINAL, strlen(FILE_ORIGINAL),
		FILE_CHANGE_MIDDLE, strlen(FILE_CHANGE_MIDDLE),
		PATCH_RENAME_SIMILAR_QUOTEDNAME, "foo\"bar.txt", 0100644));
}