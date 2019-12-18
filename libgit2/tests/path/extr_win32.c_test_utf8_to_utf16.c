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
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  git_win32_path ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (char const*) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_assert_equal_wcs (char const*,int /*<<< orphan*/ ) ; 
 int git_win32_path_from_utf8 (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  wcslen (char const*) ; 

void test_utf8_to_utf16(const char *utf8_in, const wchar_t *utf16_expected)
{
#ifdef GIT_WIN32
	git_win32_path path_utf16;
	int path_utf16len;

	cl_assert((path_utf16len = git_win32_path_from_utf8(path_utf16, utf8_in)) >= 0);
	cl_assert_equal_wcs(utf16_expected, path_utf16);
	cl_assert_equal_i(wcslen(utf16_expected), path_utf16len);
#else
	GIT_UNUSED(utf8_in);
	GIT_UNUSED(utf16_expected);
#endif
}