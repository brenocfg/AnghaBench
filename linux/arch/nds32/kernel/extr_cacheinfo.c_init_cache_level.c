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
struct cpu_cacheinfo {int num_levels; int num_leaves; } ;

/* Variables and functions */
 struct cpu_cacheinfo* get_cpu_cacheinfo (unsigned int) ; 

int init_cache_level(unsigned int cpu)
{
	struct cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);

	/* Only 1 level and I/D cache seperate. */
	this_cpu_ci->num_levels = 1;
	this_cpu_ci->num_leaves = 2;
	return 0;
}