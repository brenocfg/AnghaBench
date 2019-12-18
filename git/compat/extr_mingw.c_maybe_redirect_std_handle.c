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
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileW (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ GetEnvironmentVariableW (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ GetStdHandle (scalar_t__) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 scalar_t__ OPEN_ALWAYS ; 
 scalar_t__ OPEN_EXISTING ; 
 int /*<<< orphan*/  O_BINARY ; 
 scalar_t__ STD_ERROR_HANDLE ; 
 scalar_t__ STD_OUTPUT_HANDLE ; 
 int /*<<< orphan*/  SetEnvironmentVariableW (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetStdHandle (scalar_t__,scalar_t__) ; 
 int _open_osfhandle (intptr_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int /*<<< orphan*/  wcscmp (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void maybe_redirect_std_handle(const wchar_t *key, DWORD std_id, int fd,
				      DWORD desired_access, DWORD flags)
{
	DWORD create_flag = fd ? OPEN_ALWAYS : OPEN_EXISTING;
	wchar_t buf[MAX_PATH];
	DWORD max = ARRAY_SIZE(buf);
	HANDLE handle;
	DWORD ret = GetEnvironmentVariableW(key, buf, max);

	if (!ret || ret >= max)
		return;

	/* make sure this does not leak into child processes */
	SetEnvironmentVariableW(key, NULL);
	if (!wcscmp(buf, L"off")) {
		close(fd);
		handle = GetStdHandle(std_id);
		if (handle != INVALID_HANDLE_VALUE)
			CloseHandle(handle);
		return;
	}
	if (std_id == STD_ERROR_HANDLE && !wcscmp(buf, L"2>&1")) {
		handle = GetStdHandle(STD_OUTPUT_HANDLE);
		if (handle == INVALID_HANDLE_VALUE) {
			close(fd);
			handle = GetStdHandle(std_id);
			if (handle != INVALID_HANDLE_VALUE)
				CloseHandle(handle);
		} else {
			int new_fd = _open_osfhandle((intptr_t)handle, O_BINARY);
			SetStdHandle(std_id, handle);
			dup2(new_fd, fd);
			/* do *not* close the new_fd: that would close stdout */
		}
		return;
	}
	handle = CreateFileW(buf, desired_access, 0, NULL, create_flag,
			     flags, NULL);
	if (handle != INVALID_HANDLE_VALUE) {
		int new_fd = _open_osfhandle((intptr_t)handle, O_BINARY);
		SetStdHandle(std_id, handle);
		dup2(new_fd, fd);
		close(new_fd);
	}
}