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
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link (char const*,char const*) ; 

__attribute__((used)) static void do_hardlink(const char *old, const char *new)
{
#ifndef GIT_WIN32
	cl_must_pass(link(old, new));
#else
	typedef DWORD (WINAPI *create_hardlink_func)(LPCTSTR, LPCTSTR, LPSECURITY_ATTRIBUTES);
	HMODULE module;
	create_hardlink_func pCreateHardLink;

	cl_assert(module = GetModuleHandle("kernel32"));
	cl_assert(pCreateHardLink = (create_hardlink_func)GetProcAddress(module, "CreateHardLinkA"));

	cl_win32_pass(pCreateHardLink(new, old, 0));
#endif
}