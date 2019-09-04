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
 int /*<<< orphan*/  assert_l32_fails (char*,int) ; 
 int /*<<< orphan*/  assert_l32_parses (char*,int,int) ; 

void test_core_strtol__int32(void)
{
	assert_l32_parses("123", 123, 10);
	assert_l32_parses("  +123 ", 123, 10);
	assert_l32_parses("  +2147483647 ", 2147483647, 10);
	assert_l32_parses("  -2147483648 ", -2147483648LL, 10);
	assert_l32_parses("A", 10, 16);
	assert_l32_parses("1x1", 1, 10);

	assert_l32_fails("", 10);
	assert_l32_fails("a", 10);
	assert_l32_fails("x10x", 10);
	assert_l32_fails("  2147483657 ", 10);
	assert_l32_fails("  -2147483657 ", 10);
}