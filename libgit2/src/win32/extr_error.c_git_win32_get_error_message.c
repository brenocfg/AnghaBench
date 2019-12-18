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
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/ * HMODULE ;
typedef  int DWORD ;

/* Variables and functions */
 int FORMAT_MESSAGE_ALLOCATE_BUFFER ; 
 int FORMAT_MESSAGE_FROM_HMODULE ; 
 int FORMAT_MESSAGE_FROM_SYSTEM ; 
 int FORMAT_MESSAGE_IGNORE_INSERTS ; 
 scalar_t__ FormatMessageW (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GIT_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetModuleHandleW (char*) ; 
 int /*<<< orphan*/  LANG_NEUTRAL ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUBLANG_DEFAULT ; 
 int WINHTTP_ERROR_BASE ; 
 int WINHTTP_ERROR_LAST ; 
 scalar_t__ git__utf16_to_8_alloc (char**,int /*<<< orphan*/ *) ; 

char *git_win32_get_error_message(DWORD error_code)
{
	LPWSTR lpMsgBuf = NULL;
	HMODULE hModule = NULL;
	char *utf8_msg = NULL;
	DWORD dwFlags =
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS;

	if (!error_code)
		return NULL;

#ifdef GIT_WINHTTP
	/* Errors raised by WinHTTP are not in the system resource table */
	if (error_code >= WINHTTP_ERROR_BASE &&
		error_code <= WINHTTP_ERROR_LAST)
		hModule = GetModuleHandleW(L"winhttp");
#endif

	GIT_UNUSED(hModule);

	if (hModule)
		dwFlags |= FORMAT_MESSAGE_FROM_HMODULE;
	else
		dwFlags |= FORMAT_MESSAGE_FROM_SYSTEM;

	if (FormatMessageW(dwFlags, hModule, error_code,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPWSTR)&lpMsgBuf, 0, NULL)) {
		/* Convert the message to UTF-8. If this fails, we will
		 * return NULL, which is a condition expected by the caller */
		if (git__utf16_to_8_alloc(&utf8_msg, lpMsgBuf) < 0)
			utf8_msg = NULL;

		LocalFree(lpMsgBuf);
	}

	return utf8_msg;
}