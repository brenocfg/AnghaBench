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
 int /*<<< orphan*/  FILE_BINARY_DELTA_MODIFIED ; 
 int /*<<< orphan*/  FILE_BINARY_DELTA_MODIFIED_LEN ; 
 int /*<<< orphan*/  PATCH_BINARY_NOT_REVERSIBLE ; 
 int /*<<< orphan*/  apply_patchfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 

void test_apply_fromfile__binary_change_must_be_reversible(void)
{
	cl_git_fail(apply_patchfile(
		FILE_BINARY_DELTA_MODIFIED, FILE_BINARY_DELTA_MODIFIED_LEN,
		NULL, 0,
		PATCH_BINARY_NOT_REVERSIBLE, NULL, 0));
}