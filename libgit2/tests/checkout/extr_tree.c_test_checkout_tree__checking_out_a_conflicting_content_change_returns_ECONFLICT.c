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
 int /*<<< orphan*/  assert_conflict (char*,char*,char*,char*) ; 

void test_checkout_tree__checking_out_a_conflicting_content_change_returns_ECONFLICT(void)
{
	/*
	 * c47800c adds a symlink named 'branch_file.txt'
	 * 5b5b025 is the parent of 763d71a
	 */

	assert_conflict("branch_file.txt", "hello\n", "5b5b025", "c47800c");
}