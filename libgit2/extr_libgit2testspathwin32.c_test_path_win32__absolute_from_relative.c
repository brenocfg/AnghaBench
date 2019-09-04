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

void test_path_win32__absolute_from_relative(void)
{
#ifdef GIT_WIN32
	char cwd_backup[MAX_PATH];

	cl_must_pass(p_getcwd(cwd_backup, MAX_PATH));
	cl_must_pass(p_chdir("C:/"));

	test_utf8_to_utf16("Foo", L"\\\\?\\C:\\Foo");
	test_utf8_to_utf16("..\\..\\Foo", L"\\\\?\\C:\\Foo");
	test_utf8_to_utf16("Foo\\..", L"\\\\?\\C:\\");
	test_utf8_to_utf16("Foo\\..\\..", L"\\\\?\\C:\\");
	test_utf8_to_utf16("", L"\\\\?\\C:\\");

	cl_must_pass(p_chdir("C:/Windows"));

	test_utf8_to_utf16("Foo", L"\\\\?\\C:\\Windows\\Foo");
	test_utf8_to_utf16("Foo\\Bar", L"\\\\?\\C:\\Windows\\Foo\\Bar");
	test_utf8_to_utf16("..\\Foo", L"\\\\?\\C:\\Foo");
	test_utf8_to_utf16("Foo\\..\\Bar", L"\\\\?\\C:\\Windows\\Bar");
	test_utf8_to_utf16("", L"\\\\?\\C:\\Windows");

	cl_must_pass(p_chdir(cwd_backup));
#endif
}