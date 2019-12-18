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
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_CLR (int,int /*<<< orphan*/ *) ; 
 int CPU_FFS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAXCPU ; 
 scalar_t__ min (int,int /*<<< orphan*/ ) ; 
 scalar_t__ mp_maxid ; 
 int mp_ncpus ; 
 int /*<<< orphan*/  platform_cpu_mask (int /*<<< orphan*/ *) ; 

void
cpu_mp_setmaxid(void)
{
	cpuset_t cpumask;
	int cpu, last;

	platform_cpu_mask(&cpumask);
	mp_ncpus = 0;
	last = 1;
	while ((cpu = CPU_FFS(&cpumask)) != 0) {
		last = cpu;
		cpu--;
		CPU_CLR(cpu, &cpumask);
		mp_ncpus++;
	}
	if (mp_ncpus <= 0)
		mp_ncpus = 1;

	mp_maxid = min(last, MAXCPU) - 1;
}