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
 int INT64_MAX ; 
 int INT64_MIN ; 
 int /*<<< orphan*/  assert_l64_fails (char*,int) ; 
 int /*<<< orphan*/  assert_l64_parses (char*,int,int) ; 

void test_core_strtol__int64(void)
{
	assert_l64_parses("123", 123, 10);
	assert_l64_parses("  +123 ", 123, 10);
	assert_l64_parses("  +2147483647 ", 2147483647, 10);
	assert_l64_parses("  -2147483648 ", -2147483648LL, 10);
	assert_l64_parses("  2147483657 ", 2147483657LL, 10);
	assert_l64_parses("  -2147483657 ", -2147483657LL, 10);
	assert_l64_parses(" 9223372036854775807  ", INT64_MAX, 10);
	assert_l64_parses("   -9223372036854775808  ", INT64_MIN, 10);
	assert_l64_parses("   0x7fffffffffffffff  ", INT64_MAX, 16);
	assert_l64_parses("   -0x8000000000000000   ", INT64_MIN, 16);
	assert_l64_parses("1a", 26, 16);
	assert_l64_parses("1A", 26, 16);

	assert_l64_fails("", 10);
	assert_l64_fails("a", 10);
	assert_l64_fails("x10x", 10);
	assert_l64_fails("0x8000000000000000", 16);
	assert_l64_fails("-0x8000000000000001", 16);
}