#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct p_timeval {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  SYSTEMTIME ;
typedef  scalar_t__ HANDLE ;
typedef  TYPE_1__ FILETIME ;

/* Variables and functions */
 int /*<<< orphan*/  GetSystemTime (int /*<<< orphan*/ *) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ SetFileTime (scalar_t__,int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  SystemTimeToFileTime (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ _get_osfhandle (int) ; 
 int /*<<< orphan*/  git_win32__timeval_to_filetime (TYPE_1__*,struct p_timeval const) ; 

int p_futimes(int fd, const struct p_timeval times[2])
{
	HANDLE handle;
	FILETIME atime = { 0 }, mtime = { 0 };

	if (times == NULL) {
		SYSTEMTIME st;

		GetSystemTime(&st);
		SystemTimeToFileTime(&st, &atime);
		SystemTimeToFileTime(&st, &mtime);
	}
	else {
		git_win32__timeval_to_filetime(&atime, times[0]);
		git_win32__timeval_to_filetime(&mtime, times[1]);
	}

	if ((handle = (HANDLE)_get_osfhandle(fd)) == INVALID_HANDLE_VALUE)
		return -1;

	if (SetFileTime(handle, NULL, &atime, &mtime) == 0)
		return -1;

	return 0;
}