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
struct ctl_cpu_stats {long user; long nice; long system; long intr; long idle; } ;
typedef  int /*<<< orphan*/  cp_time ;

/* Variables and functions */
 int CPUSTATES ; 
 size_t CP_IDLE ; 
 size_t CP_INTR ; 
 size_t CP_NICE ; 
 size_t CP_SYS ; 
 size_t CP_USER ; 
 int sysctlbyname (char*,long**,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int
getcpu(struct ctl_cpu_stats *cpu_stats)
{
	long cp_time[CPUSTATES];
	size_t cplen;

	cplen = sizeof(cp_time);

	if (sysctlbyname("kern.cp_time", &cp_time, &cplen, NULL, 0) == -1) {
		warn("sysctlbyname(kern.cp_time...) failed");
		return (1);
	}

	cpu_stats->user = cp_time[CP_USER];
	cpu_stats->nice = cp_time[CP_NICE];
	cpu_stats->system = cp_time[CP_SYS];
	cpu_stats->intr = cp_time[CP_INTR];
	cpu_stats->idle = cp_time[CP_IDLE];

	return (0);
}