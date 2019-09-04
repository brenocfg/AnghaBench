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

void test_path_win32__canonicalize(void)
{
#ifdef GIT_WIN32
	test_canonicalize(L"C:\\Foo\\Bar", L"C:\\Foo\\Bar");
	test_canonicalize(L"C:\\Foo\\", L"C:\\Foo");
	test_canonicalize(L"C:\\Foo\\\\", L"C:\\Foo");
	test_canonicalize(L"C:\\Foo\\..\\Bar", L"C:\\Bar");
	test_canonicalize(L"C:\\Foo\\..\\..\\Bar", L"C:\\Bar");
	test_canonicalize(L"C:\\Foo\\..\\..\\..\\..\\", L"C:\\");
	test_canonicalize(L"C:/Foo/Bar", L"C:\\Foo\\Bar");
	test_canonicalize(L"C:/", L"C:\\");

	test_canonicalize(L"Foo\\\\Bar\\\\Asdf\\\\", L"Foo\\Bar\\Asdf");
	test_canonicalize(L"Foo\\\\Bar\\\\..\\\\Asdf\\", L"Foo\\Asdf");
	test_canonicalize(L"Foo\\\\Bar\\\\.\\\\Asdf\\", L"Foo\\Bar\\Asdf");
	test_canonicalize(L"Foo\\\\..\\Bar\\\\.\\\\Asdf\\", L"Bar\\Asdf");
	test_canonicalize(L"\\", L"");
	test_canonicalize(L"", L"");
	test_canonicalize(L"Foo\\..\\..\\..\\..", L"");
	test_canonicalize(L"..\\..\\..\\..", L"");
	test_canonicalize(L"\\..\\..\\..\\..", L"");

	test_canonicalize(L"\\\\?\\C:\\Foo\\Bar", L"\\\\?\\C:\\Foo\\Bar");
	test_canonicalize(L"\\\\?\\C:\\Foo\\Bar\\", L"\\\\?\\C:\\Foo\\Bar");
	test_canonicalize(L"\\\\?\\C:\\\\Foo\\.\\Bar\\\\..\\", L"\\\\?\\C:\\Foo");
	test_canonicalize(L"\\\\?\\C:\\\\", L"\\\\?\\C:\\");
	test_canonicalize(L"//?/C:/", L"\\\\?\\C:\\");
	test_canonicalize(L"//?/C:/../../Foo/", L"\\\\?\\C:\\Foo");
	test_canonicalize(L"//?/C:/Foo/../../", L"\\\\?\\C:\\");

	test_canonicalize(L"\\\\?\\UNC\\server\\C$\\folder", L"\\\\?\\UNC\\server\\C$\\folder");
	test_canonicalize(L"\\\\?\\UNC\\server\\C$\\folder\\", L"\\\\?\\UNC\\server\\C$\\folder");
	test_canonicalize(L"\\\\?\\UNC\\server\\C$\\folder\\", L"\\\\?\\UNC\\server\\C$\\folder");
	test_canonicalize(L"\\\\?\\UNC\\server\\C$\\folder\\..\\..\\..\\..\\share\\", L"\\\\?\\UNC\\server\\share");

	test_canonicalize(L"\\\\server\\share", L"\\\\server\\share");
	test_canonicalize(L"\\\\server\\share\\", L"\\\\server\\share");
	test_canonicalize(L"\\\\server\\share\\\\foo\\\\bar", L"\\\\server\\share\\foo\\bar");
	test_canonicalize(L"\\\\server\\\\share\\\\foo\\\\bar", L"\\\\server\\share\\foo\\bar");
	test_canonicalize(L"\\\\server\\share\\..\\foo", L"\\\\server\\foo");
	test_canonicalize(L"\\\\server\\..\\..\\share\\.\\foo", L"\\\\server\\share\\foo");
#endif
}