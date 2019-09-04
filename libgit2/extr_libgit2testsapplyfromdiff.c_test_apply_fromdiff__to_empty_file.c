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
 int /*<<< orphan*/  PATCH_ORIGINAL_TO_EMPTY_FILE ; 
 int /*<<< orphan*/  apply_buf (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 

void test_apply_fromdiff__to_empty_file(void)
{
	cl_git_pass(apply_buf(
		FILE_ORIGINAL, "file.txt",
		"", NULL,
		PATCH_ORIGINAL_TO_EMPTY_FILE, NULL));
}