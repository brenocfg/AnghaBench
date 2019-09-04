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

/* Variables and functions */
 int /*<<< orphan*/  PATCH_CORRUPT_GIT_HEADER ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_patch_from_buffer (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

void test_apply_fromfile__fail_corrupt_githeader(void)
{
	git_patch *patch;
	cl_git_fail(git_patch_from_buffer(&patch, PATCH_CORRUPT_GIT_HEADER,
		strlen(PATCH_CORRUPT_GIT_HEADER), NULL));
}