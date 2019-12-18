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

void test_checkout_tree__checking_out_a_conflicting_type_change_returns_ECONFLICT(void)
{
	/*
	 * 099faba adds a symlink named 'link_to_new.txt'
	 * a65fedf is the parent of 099faba
	 */

	assert_conflict("link_to_new.txt", "old.txt", "a65fedf", "099faba");
}