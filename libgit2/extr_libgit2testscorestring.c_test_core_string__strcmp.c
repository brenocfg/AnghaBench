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
 scalar_t__ git__strcmp (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

void test_core_string__strcmp(void)
{
	cl_assert(git__strcmp("", "") == 0);
	cl_assert(git__strcmp("foo", "foo") == 0);
	cl_assert(git__strcmp("Foo", "foo") < 0);
	cl_assert(git__strcmp("foo", "FOO") > 0);
	cl_assert(git__strcmp("foo", "fOO") > 0);

	cl_assert(strcmp("rt\303\202of", "rt dev\302\266h") > 0);
	cl_assert(strcmp("e\342\202\254ghi=", "et") > 0);
	cl_assert(strcmp("rt dev\302\266h", "rt\303\202of") < 0);
	cl_assert(strcmp("et", "e\342\202\254ghi=") < 0);
	cl_assert(strcmp("\303\215", "\303\255") < 0);

	cl_assert(git__strcmp("rt\303\202of", "rt dev\302\266h") > 0);
	cl_assert(git__strcmp("e\342\202\254ghi=", "et") > 0);
	cl_assert(git__strcmp("rt dev\302\266h", "rt\303\202of") < 0);
	cl_assert(git__strcmp("et", "e\342\202\254ghi=") < 0);
	cl_assert(git__strcmp("\303\215", "\303\255") < 0);
}