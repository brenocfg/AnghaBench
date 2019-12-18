#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * active_mm; } ;
struct TYPE_3__ {scalar_t__ new_child; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUHP_AP_ONLINE_IDLE ; 
 int /*<<< orphan*/  __flush_tlb_all () ; 
 int /*<<< orphan*/  __local_per_cpu_offset ; 
 int /*<<< orphan*/  __per_cpu_offset (int) ; 
 int callin_flag ; 
 int /*<<< orphan*/  cheetah_enable_pcache () ; 
 scalar_t__ cheetah_pcache_forced_on ; 
 int /*<<< orphan*/  cpu_startup_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_test_cpu (int,int /*<<< orphan*/ *) ; 
 TYPE_2__* current ; 
 TYPE_1__* current_thread_info () ; 
 int hard_smp_processor_id () ; 
 scalar_t__ hypervisor ; 
 int /*<<< orphan*/  init_mm ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  mmgrab (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notify_cpu_starting (int) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  set_cpu_online (int,int) ; 
 int /*<<< orphan*/  setup_sparc64_timer () ; 
 int /*<<< orphan*/  smp_commenced_mask ; 
 int /*<<< orphan*/  sun4v_ktsb_register () ; 
 scalar_t__ tlb_type ; 

void smp_callin(void)
{
	int cpuid = hard_smp_processor_id();

	__local_per_cpu_offset = __per_cpu_offset(cpuid);

	if (tlb_type == hypervisor)
		sun4v_ktsb_register();

	__flush_tlb_all();

	setup_sparc64_timer();

	if (cheetah_pcache_forced_on)
		cheetah_enable_pcache();

	callin_flag = 1;
	__asm__ __volatile__("membar #Sync\n\t"
			     "flush  %%g6" : : : "memory");

	/* Clear this or we will die instantly when we
	 * schedule back to this idler...
	 */
	current_thread_info()->new_child = 0;

	/* Attach to the address space of init_task. */
	mmgrab(&init_mm);
	current->active_mm = &init_mm;

	/* inform the notifiers about the new cpu */
	notify_cpu_starting(cpuid);

	while (!cpumask_test_cpu(cpuid, &smp_commenced_mask))
		rmb();

	set_cpu_online(cpuid, true);

	/* idle thread is expected to have preempt disabled */
	preempt_disable();

	local_irq_enable();

	cpu_startup_entry(CPUHP_AP_ONLINE_IDLE);
}