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
 int /*<<< orphan*/  assert_l64_parses (char*,int,int /*<<< orphan*/ ) ; 

void test_core_strtol__base_autodetection(void)
{
	assert_l64_parses("0", 0, 0);
	assert_l64_parses("00", 0, 0);
	assert_l64_parses("0x", 0, 0);
	assert_l64_parses("0foobar", 0, 0);
	assert_l64_parses("07", 7, 0);
	assert_l64_parses("017", 15, 0);
	assert_l64_parses("0x8", 8, 0);
	assert_l64_parses("0x18", 24, 0);
}