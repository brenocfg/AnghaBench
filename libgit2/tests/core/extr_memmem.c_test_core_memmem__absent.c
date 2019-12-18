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
 int /*<<< orphan*/  assert_absent (char*,char*) ; 

void test_core_memmem__absent(void)
{
	assert_absent("a", "b");
	assert_absent("a", "aa");
	assert_absent("ba", "ab");
	assert_absent("ba", "ab");
	assert_absent("abc", "abcd");
	assert_absent("abcabcabc", "bcac");
}