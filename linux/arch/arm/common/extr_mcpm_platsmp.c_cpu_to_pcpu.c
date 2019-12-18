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
 unsigned int MPIDR_AFFINITY_LEVEL (unsigned int,int) ; 
 unsigned int cpu_logical_map (unsigned int) ; 

__attribute__((used)) static void cpu_to_pcpu(unsigned int cpu,
			unsigned int *pcpu, unsigned int *pcluster)
{
	unsigned int mpidr;

	mpidr = cpu_logical_map(cpu);
	*pcpu = MPIDR_AFFINITY_LEVEL(mpidr, 0);
	*pcluster = MPIDR_AFFINITY_LEVEL(mpidr, 1);
}