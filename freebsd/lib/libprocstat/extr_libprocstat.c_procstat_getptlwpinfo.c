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
struct ptrace_lwpinfo {int dummy; } ;
struct procstat {int type; int /*<<< orphan*/  core; } ;

/* Variables and functions */
#define  PROCSTAT_CORE 130 
#define  PROCSTAT_KVM 129 
#define  PROCSTAT_SYSCTL 128 
 struct ptrace_lwpinfo* procstat_getptlwpinfo_core (int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

struct ptrace_lwpinfo *
procstat_getptlwpinfo(struct procstat *procstat, unsigned int *cntp)
{
	switch (procstat->type) {
	case PROCSTAT_KVM:
		warnx("kvm method is not supported");
		return (NULL);
	case PROCSTAT_SYSCTL:
		warnx("sysctl method is not supported");
		return (NULL);
	case PROCSTAT_CORE:
	 	return (procstat_getptlwpinfo_core(procstat->core, cntp));
	default:
		warnx("unknown access method: %d", procstat->type);
		return (NULL);
	}
}