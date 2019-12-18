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
 int /*<<< orphan*/  assert_found (char*,char*,int) ; 

void test_core_memmem__found(void)
{
	assert_found("a", "a", 0);
	assert_found("ab", "a", 0);
	assert_found("ba", "a", 1);
	assert_found("aa", "a", 0);
	assert_found("aab", "aa", 0);
	assert_found("baa", "aa", 1);
	assert_found("dabc", "abc", 1);
	assert_found("abababc", "abc", 4);
}