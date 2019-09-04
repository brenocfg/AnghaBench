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
 int /*<<< orphan*/  GIT_UNUSED (int) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symlink (char const*,char const*) ; 

__attribute__((used)) static void do_symlink(const char *old, const char *new, int is_dir)
{
#ifndef GIT_WIN32
	GIT_UNUSED(is_dir);

	cl_must_pass(symlink(old, new));
#else
	typedef DWORD (WINAPI *create_symlink_func)(LPCTSTR, LPCTSTR, DWORD);
	HMODULE module;
	create_symlink_func pCreateSymbolicLink;

	cl_assert(module = GetModuleHandle("kernel32"));
	cl_assert(pCreateSymbolicLink = (create_symlink_func)GetProcAddress(module, "CreateSymbolicLinkA"));

	cl_win32_pass(pCreateSymbolicLink(new, old, is_dir));
#endif
}