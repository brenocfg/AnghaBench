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
struct kinfo_proc {char* ki_comm; } ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  newkp ;

/* Variables and functions */
 int CTL_KERN ; 
 int KERN_PROC ; 
 int KERN_PROC_PID ; 
 char* strdup (char*) ; 
 int sysctl (int*,int,struct kinfo_proc*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_warn (char*) ; 

__attribute__((used)) static char *
bpf_pidname(pid_t pid)
{
	struct kinfo_proc newkp;
	int error, mib[4];
	size_t size;

	mib[0] = CTL_KERN;
	mib[1] = KERN_PROC;
	mib[2] = KERN_PROC_PID;
	mib[3] = pid;
	size = sizeof(newkp);
	error = sysctl(mib, 4, &newkp, &size, NULL, 0);
	if (error < 0) {
		xo_warn("kern.proc.pid failed");
		return (strdup("??????"));
	}
	return (strdup(newkp.ki_comm));
}