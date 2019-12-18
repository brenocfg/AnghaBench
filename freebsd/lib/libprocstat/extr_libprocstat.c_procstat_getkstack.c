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
struct procstat {int type; } ;
struct kinfo_proc {int /*<<< orphan*/  ki_pid; } ;
struct kinfo_kstack {int dummy; } ;

/* Variables and functions */
#define  PROCSTAT_CORE 130 
#define  PROCSTAT_KVM 129 
#define  PROCSTAT_SYSCTL 128 
 struct kinfo_kstack* procstat_getkstack_sysctl (int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

struct kinfo_kstack *
procstat_getkstack(struct procstat *procstat, struct kinfo_proc *kp,
    unsigned int *cntp)
{
	switch(procstat->type) {
	case PROCSTAT_KVM:
		warnx("kvm method is not supported");
		return (NULL);
	case PROCSTAT_SYSCTL:
		return (procstat_getkstack_sysctl(kp->ki_pid, cntp));
	case PROCSTAT_CORE:
		warnx("core method is not supported");
		return (NULL);
	default:
		warnx("unknown access method: %d", procstat->type);
		return (NULL);
	}
}