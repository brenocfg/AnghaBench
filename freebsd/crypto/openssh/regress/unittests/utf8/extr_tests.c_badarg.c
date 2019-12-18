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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_INT_EQ (int,int) ; 
 int /*<<< orphan*/  ASSERT_STRING_EQ (char*,char*) ; 
 int /*<<< orphan*/  TEST_DONE () ; 
 int /*<<< orphan*/  TEST_START (char*) ; 
 int snmprintf (char*,int,int*,char*) ; 

__attribute__((used)) static void
badarg(void)
{
	char	 buf[16];
	int	 len, width;

	width = 1;
	TEST_START("utf8_badarg");
	len = snmprintf(buf, sizeof(buf), &width, "\377");
	ASSERT_INT_EQ(len, -1);
	ASSERT_STRING_EQ(buf, "");
	ASSERT_INT_EQ(width, 0);
	TEST_DONE();
}