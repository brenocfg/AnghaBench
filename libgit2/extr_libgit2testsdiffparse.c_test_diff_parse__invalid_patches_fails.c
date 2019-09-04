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
 int /*<<< orphan*/  PATCH_CORRUPT_MISSING_HUNK_HEADER ; 
 int /*<<< orphan*/  PATCH_CORRUPT_MISSING_NEW_FILE ; 
 int /*<<< orphan*/  PATCH_CORRUPT_MISSING_OLD_FILE ; 
 int /*<<< orphan*/  PATCH_CORRUPT_NO_CHANGES ; 
 int /*<<< orphan*/  test_parse_invalid_diff (int /*<<< orphan*/ ) ; 

void test_diff_parse__invalid_patches_fails(void)
{
	test_parse_invalid_diff(PATCH_CORRUPT_MISSING_NEW_FILE);
	test_parse_invalid_diff(PATCH_CORRUPT_MISSING_OLD_FILE);
	test_parse_invalid_diff(PATCH_CORRUPT_NO_CHANGES);
	test_parse_invalid_diff(PATCH_CORRUPT_MISSING_HUNK_HEADER);
}