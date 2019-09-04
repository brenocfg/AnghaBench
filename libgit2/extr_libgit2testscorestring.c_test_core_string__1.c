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
 int /*<<< orphan*/  cl_assert (int) ; 
 scalar_t__ git__suffixcmp (char*,char*) ; 

void test_core_string__1(void)
{
	cl_assert(git__suffixcmp("", "") == 0);
	cl_assert(git__suffixcmp("a", "") == 0);
	cl_assert(git__suffixcmp("", "a") < 0);
	cl_assert(git__suffixcmp("a", "b") < 0);
	cl_assert(git__suffixcmp("b", "a") > 0);
	cl_assert(git__suffixcmp("ba", "a") == 0);
	cl_assert(git__suffixcmp("zaa", "ac") < 0);
	cl_assert(git__suffixcmp("zaz", "ac") > 0);
}