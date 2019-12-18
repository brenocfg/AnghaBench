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
 scalar_t__ ESRCH ; 
 int KERN_PROC ; 
 int KERN_PROC_PATHNAME ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  nitems (int*) ; 
 int sysctl (int*,int /*<<< orphan*/ ,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,int) ; 

__attribute__((used)) static int
procstat_getpathname_sysctl(pid_t pid, char *pathname, size_t maxlen)
{
	int error, name[4];
	size_t len;

	name[0] = CTL_KERN;
	name[1] = KERN_PROC;
	name[2] = KERN_PROC_PATHNAME;
	name[3] = pid;
	len = maxlen;
	error = sysctl(name, nitems(name), pathname, &len, NULL, 0);
	if (error != 0 && errno != ESRCH)
		warn("sysctl: kern.proc.pathname: %d", pid);
	if (len == 0)
		pathname[0] = '\0';
	return (error);
}