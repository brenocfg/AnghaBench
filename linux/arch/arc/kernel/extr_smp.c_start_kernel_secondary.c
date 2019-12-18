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
struct mm_struct {int dummy; } ;
struct TYPE_6__ {struct mm_struct* active_mm; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* init_per_cpu ) (unsigned int) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  (* init_per_cpu ) (unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CPUHP_AP_ONLINE_IDLE ; 
 int /*<<< orphan*/  cpu_startup_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_set_cpu (unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_3__* current ; 
 struct mm_struct init_mm ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 TYPE_2__* machine_desc ; 
 int /*<<< orphan*/  mm_cpumask (struct mm_struct*) ; 
 int /*<<< orphan*/  mmget (struct mm_struct*) ; 
 int /*<<< orphan*/  mmgrab (struct mm_struct*) ; 
 int /*<<< orphan*/  notify_cpu_starting (unsigned int) ; 
 TYPE_1__ plat_smp_ops ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  set_cpu_online (unsigned int,int) ; 
 int /*<<< orphan*/  setup_processor () ; 
 unsigned int smp_processor_id () ; 
 int /*<<< orphan*/  stub1 (unsigned int) ; 
 int /*<<< orphan*/  stub2 (unsigned int) ; 

void start_kernel_secondary(void)
{
	struct mm_struct *mm = &init_mm;
	unsigned int cpu = smp_processor_id();

	/* MMU, Caches, Vector Table, Interrupts etc */
	setup_processor();

	mmget(mm);
	mmgrab(mm);
	current->active_mm = mm;
	cpumask_set_cpu(cpu, mm_cpumask(mm));

	/* Some SMP H/w setup - for each cpu */
	if (plat_smp_ops.init_per_cpu)
		plat_smp_ops.init_per_cpu(cpu);

	if (machine_desc->init_per_cpu)
		machine_desc->init_per_cpu(cpu);

	notify_cpu_starting(cpu);
	set_cpu_online(cpu, true);

	pr_info("## CPU%u LIVE ##: Executing Code...\n", cpu);

	local_irq_enable();
	preempt_disable();
	cpu_startup_entry(CPUHP_AP_ONLINE_IDLE);
}