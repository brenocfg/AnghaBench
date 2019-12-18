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
typedef  scalar_t__ processorid_t ;
typedef  int /*<<< orphan*/  dtrace_xcall_t ;
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SETOF (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ DTRACE_CPUALL ; 
 int /*<<< orphan*/  all_cpus ; 
 int /*<<< orphan*/  smp_no_rendezvous_barrier ; 
 int /*<<< orphan*/  smp_rendezvous_cpus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

void
dtrace_xcall(processorid_t cpu, dtrace_xcall_t func, void *arg)
{
	cpuset_t cpus;

	if (cpu == DTRACE_CPUALL)
		cpus = all_cpus;
	else
		CPU_SETOF(cpu, &cpus);

	smp_rendezvous_cpus(cpus, smp_no_rendezvous_barrier, func,
	    smp_no_rendezvous_barrier, arg);
}