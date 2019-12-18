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
struct kinfo_proc {int dummy; } ;
struct filestat_list {int dummy; } ;

/* Variables and functions */
#define  PROCSTAT_CORE 130 
#define  PROCSTAT_KVM 129 
#define  PROCSTAT_SYSCTL 128 
 struct filestat_list* procstat_getfiles_kvm (struct procstat*,struct kinfo_proc*,int) ; 
 struct filestat_list* procstat_getfiles_sysctl (struct procstat*,struct kinfo_proc*,int) ; 
 int /*<<< orphan*/  warnx (char*,int) ; 

struct filestat_list *
procstat_getfiles(struct procstat *procstat, struct kinfo_proc *kp, int mmapped)
{

	switch(procstat->type) {
	case PROCSTAT_KVM:
		return (procstat_getfiles_kvm(procstat, kp, mmapped));
	case PROCSTAT_SYSCTL:
	case PROCSTAT_CORE:
		return (procstat_getfiles_sysctl(procstat, kp, mmapped));
	default:
		warnx("unknown access method: %d", procstat->type);
		return (NULL);
	}
}