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

/* Variables and functions */
 int /*<<< orphan*/  CPU_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlt_cpus_mask ; 
 scalar_t__ pmc_cpu_is_present (int) ; 

int
pmc_cpu_is_active(int cpu)
{
#ifdef	SMP
	return (pmc_cpu_is_present(cpu) &&
	    !CPU_ISSET(cpu, &hlt_cpus_mask));
#else
	return (1);
#endif
}