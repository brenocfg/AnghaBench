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
struct cpumask {int dummy; } ;
struct cache {int level; struct cpumask const shared_cpu_map; } ;

/* Variables and functions */
 struct cpumask const* cpu_smallcore_mask (int) ; 

__attribute__((used)) static const struct cpumask *get_big_core_shared_cpu_map(int cpu, struct cache *cache)
{
	if (cache->level == 1)
		return cpu_smallcore_mask(cpu);

	return &cache->shared_cpu_map;
}