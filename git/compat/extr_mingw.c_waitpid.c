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
struct pinfo_t {int pid; struct pinfo_t* next; int /*<<< orphan*/  proc; } ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  LPDWORD ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECHILD ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetExitCodeProcess (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OpenProcess (int,int /*<<< orphan*/ ,int) ; 
 int PROCESS_QUERY_INFORMATION ; 
 int SYNCHRONIZE ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 int WNOHANG ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct pinfo_t*) ; 
 struct pinfo_t* pinfo ; 
 int /*<<< orphan*/  pinfo_cs ; 

pid_t waitpid(pid_t pid, int *status, int options)
{
	HANDLE h = OpenProcess(SYNCHRONIZE | PROCESS_QUERY_INFORMATION,
	    FALSE, pid);
	if (!h) {
		errno = ECHILD;
		return -1;
	}

	if (pid > 0 && options & WNOHANG) {
		if (WAIT_OBJECT_0 != WaitForSingleObject(h, 0)) {
			CloseHandle(h);
			return 0;
		}
		options &= ~WNOHANG;
	}

	if (options == 0) {
		struct pinfo_t **ppinfo;
		if (WaitForSingleObject(h, INFINITE) != WAIT_OBJECT_0) {
			CloseHandle(h);
			return 0;
		}

		if (status)
			GetExitCodeProcess(h, (LPDWORD)status);

		EnterCriticalSection(&pinfo_cs);

		ppinfo = &pinfo;
		while (*ppinfo) {
			struct pinfo_t *info = *ppinfo;
			if (info->pid == pid) {
				CloseHandle(info->proc);
				*ppinfo = info->next;
				free(info);
				break;
			}
			ppinfo = &info->next;
		}

		LeaveCriticalSection(&pinfo_cs);

		CloseHandle(h);
		return pid;
	}
	CloseHandle(h);

	errno = EINVAL;
	return -1;
}