#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * active_mm; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* take_timebase ) () ;int /*<<< orphan*/  (* setup_cpu ) (unsigned int) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  processorCount; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  CPUHP_AP_ONLINE_IDLE ; 
 scalar_t__ SYSTEM_RUNNING ; 
 int /*<<< orphan*/  add_cpu_to_masks (unsigned int) ; 
 int /*<<< orphan*/  boot_init_stack_canary () ; 
 int* cpu_callin_map ; 
 int /*<<< orphan*/  cpu_l2_cache_mask (unsigned int) ; 
 struct cpumask* cpu_sibling_mask (int) ; 
 struct cpumask* cpu_smallcore_mask (int) ; 
 int /*<<< orphan*/  cpu_startup_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_equal (int /*<<< orphan*/ ,struct cpumask*) ; 
 TYPE_3__* current ; 
 scalar_t__ has_big_cores ; 
 int /*<<< orphan*/  init_mm ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  local_memory_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmgrab (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notify_cpu_starting (unsigned int) ; 
 int /*<<< orphan*/ * numa_cpu_lookup_table ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  secondary_cpu_time_init () ; 
 int /*<<< orphan*/  set_cpu_online (unsigned int,int) ; 
 int /*<<< orphan*/  set_dec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_numa_mem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_numa_node (int /*<<< orphan*/ ) ; 
 int shared_caches ; 
 TYPE_2__* smp_ops ; 
 unsigned int smp_processor_id () ; 
 int /*<<< orphan*/  smp_store_cpu_info (unsigned int) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  stub1 (unsigned int) ; 
 int /*<<< orphan*/  stub2 () ; 
 scalar_t__ system_state ; 
 int /*<<< orphan*/  tb_ticks_per_jiffy ; 
 int /*<<< orphan*/  this_cpu_enable_ftrace () ; 
 TYPE_1__* vdso_data ; 
 int /*<<< orphan*/  vdso_getcpu_init () ; 

void start_secondary(void *unused)
{
	unsigned int cpu = smp_processor_id();
	struct cpumask *(*sibling_mask)(int) = cpu_sibling_mask;

	mmgrab(&init_mm);
	current->active_mm = &init_mm;

	smp_store_cpu_info(cpu);
	set_dec(tb_ticks_per_jiffy);
	preempt_disable();
	cpu_callin_map[cpu] = 1;

	if (smp_ops->setup_cpu)
		smp_ops->setup_cpu(cpu);
	if (smp_ops->take_timebase)
		smp_ops->take_timebase();

	secondary_cpu_time_init();

#ifdef CONFIG_PPC64
	if (system_state == SYSTEM_RUNNING)
		vdso_data->processorCount++;

	vdso_getcpu_init();
#endif
	/* Update topology CPU masks */
	add_cpu_to_masks(cpu);

	if (has_big_cores)
		sibling_mask = cpu_smallcore_mask;
	/*
	 * Check for any shared caches. Note that this must be done on a
	 * per-core basis because one core in the pair might be disabled.
	 */
	if (!cpumask_equal(cpu_l2_cache_mask(cpu), sibling_mask(cpu)))
		shared_caches = true;

	set_numa_node(numa_cpu_lookup_table[cpu]);
	set_numa_mem(local_memory_node(numa_cpu_lookup_table[cpu]));

	smp_wmb();
	notify_cpu_starting(cpu);
	set_cpu_online(cpu, true);

	boot_init_stack_canary();

	local_irq_enable();

	/* We can enable ftrace for secondary cpus now */
	this_cpu_enable_ftrace();

	cpu_startup_entry(CPUHP_AP_ONLINE_IDLE);

	BUG();
}