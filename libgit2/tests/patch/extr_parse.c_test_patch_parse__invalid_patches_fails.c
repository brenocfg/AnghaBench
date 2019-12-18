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
 int /*<<< orphan*/  GIT_ERROR ; 
 int /*<<< orphan*/  PATCH_CORRUPT_GIT_HEADER ; 
 int /*<<< orphan*/  PATCH_CORRUPT_MISSING_HUNK_HEADER ; 
 int /*<<< orphan*/  PATCH_CORRUPT_MISSING_NEW_FILE ; 
 int /*<<< orphan*/  PATCH_CORRUPT_MISSING_OLD_FILE ; 
 int /*<<< orphan*/  PATCH_CORRUPT_NO_CHANGES ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_patch_from_buffer (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

void test_patch_parse__invalid_patches_fails(void)
{
	git_patch *patch;

	cl_git_fail_with(GIT_ERROR,
		git_patch_from_buffer(&patch, PATCH_CORRUPT_GIT_HEADER,
		strlen(PATCH_CORRUPT_GIT_HEADER), NULL));
	cl_git_fail_with(GIT_ERROR,
		git_patch_from_buffer(&patch,
		PATCH_CORRUPT_MISSING_NEW_FILE,
		strlen(PATCH_CORRUPT_MISSING_NEW_FILE), NULL));
	cl_git_fail_with(GIT_ERROR,
		git_patch_from_buffer(&patch,
		PATCH_CORRUPT_MISSING_OLD_FILE,
		strlen(PATCH_CORRUPT_MISSING_OLD_FILE), NULL));
	cl_git_fail_with(GIT_ERROR,
		git_patch_from_buffer(&patch, PATCH_CORRUPT_NO_CHANGES,
		strlen(PATCH_CORRUPT_NO_CHANGES), NULL));
	cl_git_fail_with(GIT_ERROR,
		git_patch_from_buffer(&patch,
		PATCH_CORRUPT_MISSING_HUNK_HEADER,
		strlen(PATCH_CORRUPT_MISSING_HUNK_HEADER), NULL));
}