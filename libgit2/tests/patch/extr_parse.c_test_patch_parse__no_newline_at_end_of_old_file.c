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
 int /*<<< orphan*/  PATCH_APPEND_NO_NL_IN_OLD_FILE ; 
 int /*<<< orphan*/  ensure_identical_patch_inout (int /*<<< orphan*/ ) ; 

void test_patch_parse__no_newline_at_end_of_old_file(void)
{
	ensure_identical_patch_inout(PATCH_APPEND_NO_NL_IN_OLD_FILE);
}