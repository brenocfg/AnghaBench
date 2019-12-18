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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  git_win32_path ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (int /*<<< orphan*/  const*) ; 
 scalar_t__ MAX_PATH ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_wcs (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_win32_path_remove_namespace (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 scalar_t__ wcslen (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void test_remove_namespace(const wchar_t *in, const wchar_t *expected)
{
#ifdef GIT_WIN32
	git_win32_path canonical;

	cl_assert(wcslen(in) < MAX_PATH);
	wcscpy(canonical, in);

	git_win32_path_remove_namespace(canonical, wcslen(in));
	cl_assert_equal_wcs(expected, canonical);
#else
	GIT_UNUSED(in);
	GIT_UNUSED(expected);
#endif
}