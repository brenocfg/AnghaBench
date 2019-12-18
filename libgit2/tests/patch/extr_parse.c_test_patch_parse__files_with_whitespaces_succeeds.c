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
 int /*<<< orphan*/  PATCH_NAME_WHITESPACE ; 
 int /*<<< orphan*/  ensure_identical_patch_inout (int /*<<< orphan*/ ) ; 

void test_patch_parse__files_with_whitespaces_succeeds(void)
{
	ensure_identical_patch_inout(PATCH_NAME_WHITESPACE);
}