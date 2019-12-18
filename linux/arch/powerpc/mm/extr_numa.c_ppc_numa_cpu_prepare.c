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
 int numa_setup_cpu (unsigned int) ; 
 int /*<<< orphan*/  verify_cpu_node_mapping (unsigned int,int) ; 

__attribute__((used)) static int ppc_numa_cpu_prepare(unsigned int cpu)
{
	int nid;

	nid = numa_setup_cpu(cpu);
	verify_cpu_node_mapping(cpu, nid);
	return 0;
}