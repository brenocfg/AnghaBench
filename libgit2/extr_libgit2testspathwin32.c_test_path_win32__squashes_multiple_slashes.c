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

void test_path_win32__squashes_multiple_slashes(void)
{
#ifdef GIT_WIN32
	test_utf8_to_utf16("C:\\\\Foo\\Bar\\\\Foobar", L"\\\\?\\C:\\Foo\\Bar\\Foobar");
	test_utf8_to_utf16("C://Foo/Bar///Foobar", L"\\\\?\\C:\\Foo\\Bar\\Foobar");
#endif
}