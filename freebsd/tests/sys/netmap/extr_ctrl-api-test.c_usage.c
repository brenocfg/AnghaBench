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
 int /*<<< orphan*/  printf (char*,char const*) ; 

__attribute__((used)) static void
usage(const char *prog)
{
	printf("%s -i IFNAME\n"
	       "[-j TEST_NUM1[-[TEST_NUM2]] | -[TEST_NUM_2]]\n"
	       "[-l (list test cases)]\n",
	       prog);
}