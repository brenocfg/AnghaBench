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
 int /*<<< orphan*/  FILE_EMPTY_CONTEXT_MODIFIED ; 
 int /*<<< orphan*/  FILE_EMPTY_CONTEXT_ORIGINAL ; 
 int /*<<< orphan*/  PATCH_EMPTY_CONTEXT ; 
 int /*<<< orphan*/  apply_patchfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

void test_apply_fromfile__empty_context(void)
{
	cl_git_pass(apply_patchfile(
		FILE_EMPTY_CONTEXT_ORIGINAL, strlen(FILE_EMPTY_CONTEXT_ORIGINAL),
		FILE_EMPTY_CONTEXT_MODIFIED, strlen(FILE_EMPTY_CONTEXT_MODIFIED),
		PATCH_EMPTY_CONTEXT,
		"file.txt", 0100644));
}