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
 int /*<<< orphan*/  test_copy_note (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void test_rebase_merge__copy_notes_off_by_default(void)
{
	test_copy_note(NULL, 0);
}