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
typedef  scalar_t__ pid_t ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ OpenProcess (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  PROCESS_QUERY_INFORMATION ; 
 int /*<<< orphan*/  PROCESS_TERMINATE ; 
 int SIGTERM ; 
 scalar_t__ TerminateProcess (scalar_t__,int) ; 
 int /*<<< orphan*/  err_win_to_posix (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 

int mingw_kill(pid_t pid, int sig)
{
	if (pid > 0 && sig == SIGTERM) {
		HANDLE h = OpenProcess(PROCESS_TERMINATE, FALSE, pid);

		if (TerminateProcess(h, -1)) {
			CloseHandle(h);
			return 0;
		}

		errno = err_win_to_posix(GetLastError());
		CloseHandle(h);
		return -1;
	} else if (pid > 0 && sig == 0) {
		HANDLE h = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
		if (h) {
			CloseHandle(h);
			return 0;
		}
	}

	errno = EINVAL;
	return -1;
}