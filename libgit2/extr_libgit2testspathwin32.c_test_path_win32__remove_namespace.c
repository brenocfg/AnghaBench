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
 int /*<<< orphan*/  test_remove_namespace (char*,char*) ; 

void test_path_win32__remove_namespace(void)
{
	test_remove_namespace(L"\\\\?\\C:\\Temp\\Foo", L"C:\\Temp\\Foo");
	test_remove_namespace(L"\\\\?\\C:\\", L"C:\\");
	test_remove_namespace(L"\\\\?\\", L"");

	test_remove_namespace(L"\\??\\C:\\Temp\\Foo", L"C:\\Temp\\Foo");
	test_remove_namespace(L"\\??\\C:\\", L"C:\\");
	test_remove_namespace(L"\\??\\", L"");

	test_remove_namespace(L"\\\\?\\UNC\\server\\C$\\folder", L"\\\\server\\C$\\folder");
	test_remove_namespace(L"\\\\?\\UNC\\server\\C$\\folder", L"\\\\server\\C$\\folder");
	test_remove_namespace(L"\\\\?\\UNC\\server\\C$", L"\\\\server\\C$");
	test_remove_namespace(L"\\\\?\\UNC\\server\\", L"\\\\server");
	test_remove_namespace(L"\\\\?\\UNC\\server", L"\\\\server");

	test_remove_namespace(L"\\??\\UNC\\server\\C$\\folder", L"\\\\server\\C$\\folder");
	test_remove_namespace(L"\\??\\UNC\\server\\C$\\folder", L"\\\\server\\C$\\folder");
	test_remove_namespace(L"\\??\\UNC\\server\\C$", L"\\\\server\\C$");
	test_remove_namespace(L"\\??\\UNC\\server\\", L"\\\\server");
	test_remove_namespace(L"\\??\\UNC\\server", L"\\\\server");

	test_remove_namespace(L"\\\\server\\C$\\folder", L"\\\\server\\C$\\folder");
	test_remove_namespace(L"\\\\server\\C$", L"\\\\server\\C$");
	test_remove_namespace(L"\\\\server\\", L"\\\\server");
	test_remove_namespace(L"\\\\server", L"\\\\server");

	test_remove_namespace(L"C:\\Foo\\Bar", L"C:\\Foo\\Bar");
	test_remove_namespace(L"C:\\", L"C:\\");
	test_remove_namespace(L"", L"");

}