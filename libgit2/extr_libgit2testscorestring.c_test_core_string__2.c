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
 scalar_t__ git__strcasesort_cmp (char*,char*) ; 

void test_core_string__2(void)
{
	cl_assert(git__strcasesort_cmp("", "") == 0);
	cl_assert(git__strcasesort_cmp("foo", "foo") == 0);
	cl_assert(git__strcasesort_cmp("foo", "bar") > 0);
	cl_assert(git__strcasesort_cmp("bar", "foo") < 0);
	cl_assert(git__strcasesort_cmp("foo", "FOO") > 0);
	cl_assert(git__strcasesort_cmp("FOO", "foo") < 0);
	cl_assert(git__strcasesort_cmp("foo", "BAR") > 0);
	cl_assert(git__strcasesort_cmp("BAR", "foo") < 0);
	cl_assert(git__strcasesort_cmp("fooBar", "foobar") < 0);
}