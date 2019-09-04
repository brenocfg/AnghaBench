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
 int /*<<< orphan*/  PATCH_APPEND_NO_NL ; 
 int /*<<< orphan*/  verify_patch_id (int /*<<< orphan*/ ,char*) ; 

void test_diff_patchid__filename_with_spaces(void)
{
	verify_patch_id(PATCH_APPEND_NO_NL, "f0ba05413beaef743b630e796153839462ee477a");
}