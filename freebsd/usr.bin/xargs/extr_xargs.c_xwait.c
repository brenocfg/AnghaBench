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
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECHILD ; 
 int /*<<< orphan*/  WNOHANG ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ pids_empty () ; 
 scalar_t__ pids_remove (int) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static pid_t
xwait(int block, int *status) {
	pid_t pid;

	if (pids_empty()) {
		errno = ECHILD;
		return (-1);
	}

	while ((pid = waitpid(-1, status, block ? 0 : WNOHANG)) > 0)
		if (pids_remove(pid))
			break;

	return (pid);
}