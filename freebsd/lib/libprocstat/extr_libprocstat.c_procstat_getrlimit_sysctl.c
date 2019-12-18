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
struct rlimit {int dummy; } ;
typedef  int pid_t ;

/* Variables and functions */
 int CTL_KERN ; 
 scalar_t__ ESRCH ; 
 int KERN_PROC ; 
 int KERN_PROC_RLIMIT ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  nitems (int*) ; 
 int sysctl (int*,int /*<<< orphan*/ ,struct rlimit*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,int) ; 

__attribute__((used)) static int
procstat_getrlimit_sysctl(pid_t pid, int which, struct rlimit* rlimit)
{
	int error, name[5];
	size_t len;

	name[0] = CTL_KERN;
	name[1] = KERN_PROC;
	name[2] = KERN_PROC_RLIMIT;
	name[3] = pid;
	name[4] = which;
	len = sizeof(struct rlimit);
	error = sysctl(name, nitems(name), rlimit, &len, NULL, 0);
	if (error < 0 && errno != ESRCH) {
		warn("sysctl: kern.proc.rlimit: %d", pid);
		return (-1);
	}
	if (error < 0 || len != sizeof(struct rlimit))
		return (-1);
	return (0);
}