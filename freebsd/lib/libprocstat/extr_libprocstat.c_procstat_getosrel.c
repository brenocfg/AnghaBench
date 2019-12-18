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
struct procstat {int type; int /*<<< orphan*/  core; int /*<<< orphan*/  kd; } ;
struct kinfo_proc {int /*<<< orphan*/  ki_pid; } ;

/* Variables and functions */
#define  PROCSTAT_CORE 130 
#define  PROCSTAT_KVM 129 
#define  PROCSTAT_SYSCTL 128 
 int procstat_getosrel_core (int /*<<< orphan*/ ,int*) ; 
 int procstat_getosrel_kvm (int /*<<< orphan*/ ,struct kinfo_proc*,int*) ; 
 int procstat_getosrel_sysctl (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  warnx (char*,int) ; 

int
procstat_getosrel(struct procstat *procstat, struct kinfo_proc *kp, int *osrelp)
{
	switch(procstat->type) {
	case PROCSTAT_KVM:
		return (procstat_getosrel_kvm(procstat->kd, kp, osrelp));
	case PROCSTAT_SYSCTL:
		return (procstat_getosrel_sysctl(kp->ki_pid, osrelp));
	case PROCSTAT_CORE:
		return (procstat_getosrel_core(procstat->core, osrelp));
	default:
		warnx("unknown access method: %d", procstat->type);
		return (-1);
	}
}