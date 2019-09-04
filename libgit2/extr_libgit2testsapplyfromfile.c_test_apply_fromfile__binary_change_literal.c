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
 int /*<<< orphan*/  FILE_BINARY_LITERAL_MODIFIED ; 
 int /*<<< orphan*/  FILE_BINARY_LITERAL_MODIFIED_LEN ; 
 int /*<<< orphan*/  FILE_BINARY_LITERAL_ORIGINAL ; 
 int /*<<< orphan*/  FILE_BINARY_LITERAL_ORIGINAL_LEN ; 
 int /*<<< orphan*/  PATCH_BINARY_LITERAL ; 
 int /*<<< orphan*/  apply_patchfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 

void test_apply_fromfile__binary_change_literal(void)
{
	cl_git_pass(apply_patchfile(
		FILE_BINARY_LITERAL_ORIGINAL, FILE_BINARY_LITERAL_ORIGINAL_LEN,
		FILE_BINARY_LITERAL_MODIFIED, FILE_BINARY_LITERAL_MODIFIED_LEN,
		PATCH_BINARY_LITERAL, "binary.bin", 0100644));
}