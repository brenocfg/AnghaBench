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

void test_trace_windows_stacktrace__leaks(void)
{
#if defined(GIT_MSVC_CRTDBG)
	void * p1;
	void * p2;
	void * p3;
	void * p4;
	int before, after;
	int leaks;
	int error;

	/* remember outstanding leaks due to set setup
	 * and set mark/checkpoint.
	 */
	before = git_win32__crtdbg_stacktrace__dump(
		GIT_WIN32__CRTDBG_STACKTRACE__QUIET |
		GIT_WIN32__CRTDBG_STACKTRACE__LEAKS_TOTAL |
		GIT_WIN32__CRTDBG_STACKTRACE__SET_MARK,
		NULL);

	p1 = git__malloc(5);
	leaks = git_win32__crtdbg_stacktrace__dump(
		GIT_WIN32__CRTDBG_STACKTRACE__QUIET |
		GIT_WIN32__CRTDBG_STACKTRACE__LEAKS_SINCE_MARK,
		"p1");
	cl_assert((leaks == 1));

	p2 = git__malloc(5);
	leaks = git_win32__crtdbg_stacktrace__dump(
		GIT_WIN32__CRTDBG_STACKTRACE__QUIET |
		GIT_WIN32__CRTDBG_STACKTRACE__LEAKS_SINCE_MARK,
		"p1,p2");
	cl_assert((leaks == 2));

	p3 = git__malloc(5);
	leaks = git_win32__crtdbg_stacktrace__dump(
		GIT_WIN32__CRTDBG_STACKTRACE__QUIET |
		GIT_WIN32__CRTDBG_STACKTRACE__LEAKS_SINCE_MARK,
		"p1,p2,p3");
	cl_assert((leaks == 3));

	git__free(p2);
	leaks = git_win32__crtdbg_stacktrace__dump(
		GIT_WIN32__CRTDBG_STACKTRACE__QUIET |
		GIT_WIN32__CRTDBG_STACKTRACE__LEAKS_SINCE_MARK,
		"p1,p3");
	cl_assert((leaks == 2));

	/* move the mark. only new leaks should appear afterwards */
	error = git_win32__crtdbg_stacktrace__dump(
		GIT_WIN32__CRTDBG_STACKTRACE__SET_MARK,
		NULL);
	cl_assert((error == 0));

	leaks = git_win32__crtdbg_stacktrace__dump(
		GIT_WIN32__CRTDBG_STACKTRACE__QUIET |
		GIT_WIN32__CRTDBG_STACKTRACE__LEAKS_SINCE_MARK,
		"not_p1,not_p3");
	cl_assert((leaks == 0));

	p4 = git__malloc(5);
	leaks = git_win32__crtdbg_stacktrace__dump(
		GIT_WIN32__CRTDBG_STACKTRACE__QUIET |
		GIT_WIN32__CRTDBG_STACKTRACE__LEAKS_SINCE_MARK,
		"p4,not_p1,not_p3");
	cl_assert((leaks == 1));

	git__free(p1);
	git__free(p3);
	leaks = git_win32__crtdbg_stacktrace__dump(
		GIT_WIN32__CRTDBG_STACKTRACE__QUIET |
		GIT_WIN32__CRTDBG_STACKTRACE__LEAKS_SINCE_MARK,
		"p4");
	cl_assert((leaks == 1));

	git__free(p4);
	leaks = git_win32__crtdbg_stacktrace__dump(
		GIT_WIN32__CRTDBG_STACKTRACE__QUIET |
		GIT_WIN32__CRTDBG_STACKTRACE__LEAKS_SINCE_MARK,
		"end");
	cl_assert((leaks == 0));

	/* confirm current absolute leaks count matches beginning value. */
	after = git_win32__crtdbg_stacktrace__dump(
		GIT_WIN32__CRTDBG_STACKTRACE__QUIET |
		GIT_WIN32__CRTDBG_STACKTRACE__LEAKS_TOTAL,
		"total");
	cl_assert((before == after));
#endif
}