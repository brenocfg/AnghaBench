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
 int /*<<< orphan*/  PATCH_MULTIPLE_HUNKS ; 
 int /*<<< orphan*/  verify_patch_id (int /*<<< orphan*/ ,char*) ; 

void test_diff_patchid__multiple_hunks(void)
{
	verify_patch_id(PATCH_MULTIPLE_HUNKS, "81e26c34643d17f521e57c483a6a637e18ba1f57");
}