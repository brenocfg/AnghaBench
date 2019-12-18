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

/* Variables and functions */
 int cpu_first_thread_sibling (int) ; 
 int /*<<< orphan*/  cpu_l1_cache_map ; 
 scalar_t__ cpu_online (int) ; 
 int /*<<< orphan*/  cpu_smallcore_mask (int) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int,int /*<<< orphan*/ ) ; 
 scalar_t__ cpumask_test_cpu (int,struct cpumask*) ; 
 int /*<<< orphan*/  has_big_cores ; 
 struct cpumask* per_cpu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_cpus_related (int,int,int /*<<< orphan*/  (*) (int)) ; 
 int threads_per_core ; 

__attribute__((used)) static inline void add_cpu_to_smallcore_masks(int cpu)
{
	struct cpumask *this_l1_cache_map = per_cpu(cpu_l1_cache_map, cpu);
	int i, first_thread = cpu_first_thread_sibling(cpu);

	if (!has_big_cores)
		return;

	cpumask_set_cpu(cpu, cpu_smallcore_mask(cpu));

	for (i = first_thread; i < first_thread + threads_per_core; i++) {
		if (cpu_online(i) && cpumask_test_cpu(i, this_l1_cache_map))
			set_cpus_related(i, cpu, cpu_smallcore_mask);
	}
}