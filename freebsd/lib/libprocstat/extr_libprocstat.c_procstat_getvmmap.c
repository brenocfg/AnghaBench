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
struct procstat {int type; int /*<<< orphan*/  core; } ;
struct kinfo_vmentry {int dummy; } ;
struct kinfo_proc {int /*<<< orphan*/  ki_pid; } ;

/* Variables and functions */
#define  PROCSTAT_CORE 130 
#define  PROCSTAT_KVM 129 
#define  PROCSTAT_SYSCTL 128 
 struct kinfo_vmentry* kinfo_getvmmap (int /*<<< orphan*/ ,unsigned int*) ; 
 struct kinfo_vmentry* kinfo_getvmmap_core (int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

struct kinfo_vmentry *
procstat_getvmmap(struct procstat *procstat, struct kinfo_proc *kp,
    unsigned int *cntp)
{

	switch(procstat->type) {
	case PROCSTAT_KVM:
		warnx("kvm method is not supported");
		return (NULL);
	case PROCSTAT_SYSCTL:
		return (kinfo_getvmmap(kp->ki_pid, cntp));
	case PROCSTAT_CORE:
		return (kinfo_getvmmap_core(procstat->core, cntp));
	default:
		warnx("unknown access method: %d", procstat->type);
		return (NULL);
	}
}