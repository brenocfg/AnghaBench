#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_4__ {int /*<<< orphan*/  cFileName; } ;
typedef  TYPE_1__ WIN32_FIND_DATAW ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_NO_MORE_FILES ; 
 int /*<<< orphan*/  FindClose (scalar_t__) ; 
 scalar_t__ FindFirstFileW (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  FindNextFileW (scalar_t__,TYPE_1__*) ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  wcscat (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  wcscmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int is_dir_empty(const wchar_t *wpath)
{
	WIN32_FIND_DATAW findbuf;
	HANDLE handle;
	wchar_t wbuf[MAX_PATH + 2];
	wcscpy(wbuf, wpath);
	wcscat(wbuf, L"\\*");
	handle = FindFirstFileW(wbuf, &findbuf);
	if (handle == INVALID_HANDLE_VALUE)
		return GetLastError() == ERROR_NO_MORE_FILES;

	while (!wcscmp(findbuf.cFileName, L".") ||
			!wcscmp(findbuf.cFileName, L".."))
		if (!FindNextFileW(handle, &findbuf)) {
			DWORD err = GetLastError();
			FindClose(handle);
			return err == ERROR_NO_MORE_FILES;
		}
	FindClose(handle);
	return 0;
}