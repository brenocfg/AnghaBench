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
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  PATCH_NOT_A_PATCH ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_patch_from_buffer (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

void test_patch_parse__nonpatches_fail_with_notfound(void)
{
	git_patch *patch;

	cl_git_fail_with(GIT_ENOTFOUND,
		git_patch_from_buffer(&patch, PATCH_NOT_A_PATCH,
		strlen(PATCH_NOT_A_PATCH), NULL));
}