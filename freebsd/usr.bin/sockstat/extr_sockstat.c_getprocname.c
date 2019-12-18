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
struct kinfo_proc {char const* ki_comm; } ;
typedef  int /*<<< orphan*/  proc ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int CTL_KERN ; 
 scalar_t__ ESRCH ; 
 int KERN_PROC ; 
 int KERN_PROC_PID ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  nitems (int*) ; 
 int sysctl (int*,int /*<<< orphan*/ ,struct kinfo_proc*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static const char *
getprocname(pid_t pid)
{
	static struct kinfo_proc proc;
	size_t len;
	int mib[4];

	mib[0] = CTL_KERN;
	mib[1] = KERN_PROC;
	mib[2] = KERN_PROC_PID;
	mib[3] = (int)pid;
	len = sizeof(proc);
	if (sysctl(mib, nitems(mib), &proc, &len, NULL, 0) == -1) {
		/* Do not warn if the process exits before we get its name. */
		if (errno != ESRCH)
			warn("sysctl()");
		return ("??");
	}
	return (proc.ki_comm);
}