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
 int /*<<< orphan*/  ASSERT_LONG_EQ (int /*<<< orphan*/ ,int) ; 
 scalar_t__ LONG_MAX ; 
 int /*<<< orphan*/  TEST_DONE () ; 
 int /*<<< orphan*/  TEST_START (char*) ; 
 int /*<<< orphan*/  convtime (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned long long) ; 

void
tests(void)
{
	char buf[1024];

	TEST_START("conversion_convtime");
	ASSERT_LONG_EQ(convtime("0"), 0);
	ASSERT_LONG_EQ(convtime("1"), 1);
	ASSERT_LONG_EQ(convtime("1S"), 1);
	/* from the examples in the comment above the function */
	ASSERT_LONG_EQ(convtime("90m"), 5400);
	ASSERT_LONG_EQ(convtime("1h30m"), 5400);
	ASSERT_LONG_EQ(convtime("2d"), 172800);
	ASSERT_LONG_EQ(convtime("1w"), 604800);

	/* negative time is not allowed */
	ASSERT_LONG_EQ(convtime("-7"), -1);
	ASSERT_LONG_EQ(convtime("-9d"), -1);
	
	/* overflow */
	snprintf(buf, sizeof buf, "%llu", (unsigned long long)LONG_MAX + 1);
	ASSERT_LONG_EQ(convtime(buf), -1);

	/* overflow with multiplier */
	snprintf(buf, sizeof buf, "%lluM", (unsigned long long)LONG_MAX/60 + 1);
	ASSERT_LONG_EQ(convtime(buf), -1);
	ASSERT_LONG_EQ(convtime("1000000000000000000000w"), -1);
	TEST_DONE();
}