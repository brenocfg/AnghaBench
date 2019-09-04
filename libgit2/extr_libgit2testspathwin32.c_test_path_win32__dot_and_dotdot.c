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

void test_path_win32__dot_and_dotdot(void)
{
#ifdef GIT_WIN32
	test_utf8_to_utf16("C:\\Foo\\..\\Foobar", L"\\\\?\\C:\\Foobar");
	test_utf8_to_utf16("C:\\Foo\\Bar\\..\\Foobar", L"\\\\?\\C:\\Foo\\Foobar");
	test_utf8_to_utf16("C:\\Foo\\Bar\\..\\Foobar\\..", L"\\\\?\\C:\\Foo");
	test_utf8_to_utf16("C:\\Foobar\\..", L"\\\\?\\C:\\");
	test_utf8_to_utf16("C:/Foo/Bar/../Foobar", L"\\\\?\\C:\\Foo\\Foobar");
	test_utf8_to_utf16("C:/Foo/Bar/../Foobar/../Asdf/", L"\\\\?\\C:\\Foo\\Asdf");
	test_utf8_to_utf16("C:/Foo/Bar/../Foobar/..", L"\\\\?\\C:\\Foo");
	test_utf8_to_utf16("C:/Foo/..", L"\\\\?\\C:\\");

	test_utf8_to_utf16("C:\\Foo\\Bar\\.\\Foobar", L"\\\\?\\C:\\Foo\\Bar\\Foobar");
	test_utf8_to_utf16("C:\\.\\Foo\\.\\Bar\\.\\Foobar\\.\\", L"\\\\?\\C:\\Foo\\Bar\\Foobar");
	test_utf8_to_utf16("C:/Foo/Bar/./Foobar", L"\\\\?\\C:\\Foo\\Bar\\Foobar");
	test_utf8_to_utf16("C:/Foo/../Bar/./Foobar/../", L"\\\\?\\C:\\Bar");

	test_utf8_to_utf16("C:\\Foo\\..\\..\\Bar", L"\\\\?\\C:\\Bar");
#endif
}