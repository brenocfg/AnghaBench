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
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileW (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FILE_FLAG_BACKUP_SEMANTICS ; 
 int /*<<< orphan*/  FILE_NAME_NORMALIZED ; 
 int FILE_SHARE_DELETE ; 
 int FILE_SHARE_READ ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 scalar_t__ GIT_WIN_PATH_UTF16 ; 
 scalar_t__ GetFinalPathNameByHandleW (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 scalar_t__ git_win32_path_remove_namespace (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int getfinalpath_w(
	git_win32_path dest,
	const wchar_t *path)
{
	HANDLE hFile;
	DWORD dwChars;

	/* Use FILE_FLAG_BACKUP_SEMANTICS so we can open a directory. Do not
	* specify FILE_FLAG_OPEN_REPARSE_POINT; we want to open a handle to the
	* target of the link. */
	hFile = CreateFileW(path, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_DELETE,
		NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
		return -1;

	/* Call GetFinalPathNameByHandle */
	dwChars = GetFinalPathNameByHandleW(hFile, dest, GIT_WIN_PATH_UTF16, FILE_NAME_NORMALIZED);
	CloseHandle(hFile);

	if (!dwChars || dwChars >= GIT_WIN_PATH_UTF16)
		return -1;

	/* The path may be delivered to us with a namespace prefix; remove */
	return (int)git_win32_path_remove_namespace(dest, dwChars);
}