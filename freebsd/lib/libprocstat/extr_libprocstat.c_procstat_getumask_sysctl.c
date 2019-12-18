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
 int CTL_KERN ; 
 scalar_t__ EPERM ; 
 scalar_t__ ESRCH ; 
 int KERN_PROC ; 
 int KERN_PROC_UMASK ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  nitems (int*) ; 
 int sysctl (int*,int /*<<< orphan*/ ,unsigned short*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,int) ; 

__attribute__((used)) static int
procstat_getumask_sysctl(pid_t pid, unsigned short *maskp)
{
	int error;
	int mib[4];
	size_t len;

	mib[0] = CTL_KERN;
	mib[1] = KERN_PROC;
	mib[2] = KERN_PROC_UMASK;
	mib[3] = pid;
	len = sizeof(*maskp);
	error = sysctl(mib, nitems(mib), maskp, &len, NULL, 0);
	if (error != 0 && errno != ESRCH && errno != EPERM)
		warn("sysctl: kern.proc.umask: %d", pid);
	return (error);
}