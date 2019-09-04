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
 int /*<<< orphan*/  PATCH_SIMPLE_COMMIT ; 
 int /*<<< orphan*/  verify_patch_id (int /*<<< orphan*/ ,char*) ; 

void test_diff_patchid__simple_commit(void)
{
	verify_patch_id(PATCH_SIMPLE_COMMIT, "06094b1948b878b7d9ff7560b4eae672a014b0ec");
}