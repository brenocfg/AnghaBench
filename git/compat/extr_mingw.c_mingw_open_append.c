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
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileW (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ENOSYS ; 
 int /*<<< orphan*/  FILE_APPEND_DATA ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  OPEN_ALWAYS ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int O_APPEND ; 
 int /*<<< orphan*/  O_BINARY ; 
 int O_CREAT ; 
 int O_WRONLY ; 
 int _open_osfhandle (intptr_t,int /*<<< orphan*/ ) ; 
 int err_win_to_posix (int /*<<< orphan*/ ) ; 
 int errno ; 

__attribute__((used)) static int mingw_open_append(wchar_t const *wfilename, int oflags, ...)
{
	HANDLE handle;
	int fd;
	DWORD create = (oflags & O_CREAT) ? OPEN_ALWAYS : OPEN_EXISTING;

	/* only these flags are supported */
	if ((oflags & ~O_CREAT) != (O_WRONLY | O_APPEND))
		return errno = ENOSYS, -1;

	/*
	 * FILE_SHARE_WRITE is required to permit child processes
	 * to append to the file.
	 */
	handle = CreateFileW(wfilename, FILE_APPEND_DATA,
			FILE_SHARE_WRITE | FILE_SHARE_READ,
			NULL, create, FILE_ATTRIBUTE_NORMAL, NULL);
	if (handle == INVALID_HANDLE_VALUE)
		return errno = err_win_to_posix(GetLastError()), -1;

	/*
	 * No O_APPEND here, because the CRT uses it only to reset the
	 * file pointer to EOF before each write(); but that is not
	 * necessary (and may lead to races) for a file created with
	 * FILE_APPEND_DATA.
	 */
	fd = _open_osfhandle((intptr_t)handle, O_BINARY);
	if (fd < 0)
		CloseHandle(handle);
	return fd;
}