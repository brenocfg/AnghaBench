#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct mm_struct {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* cpu_postboot ) () ;} ;
struct TYPE_4__ {struct mm_struct* active_mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUHP_AP_ONLINE_IDLE ; 
 int /*<<< orphan*/  CPU_BOOT_SUCCESS ; 
 int /*<<< orphan*/  DAIF_PROCCTX ; 
 int MPIDR_HWID_BITMASK ; 
 int /*<<< orphan*/  check_local_cpu_capabilities () ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 TYPE_3__** cpu_ops ; 
 int /*<<< orphan*/  cpu_running ; 
 int /*<<< orphan*/  cpu_startup_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_uninstall_idmap () ; 
 int /*<<< orphan*/  cpuinfo_store_cpu () ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  init_gic_priority_masking () ; 
 struct mm_struct init_mm ; 
 int /*<<< orphan*/  local_daif_restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmgrab (struct mm_struct*) ; 
 int /*<<< orphan*/  notify_cpu_starting (unsigned int) ; 
 int /*<<< orphan*/  numa_add_cpu (unsigned int) ; 
 int /*<<< orphan*/  per_cpu_offset (unsigned int) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  read_cpuid_id () ; 
 int read_cpuid_mpidr () ; 
 int /*<<< orphan*/  set_cpu_online (unsigned int,int) ; 
 int /*<<< orphan*/  set_my_cpu_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store_cpu_topology (unsigned int) ; 
 int /*<<< orphan*/  stub1 () ; 
 scalar_t__ system_uses_irq_prio_masking () ; 
 unsigned int task_cpu (TYPE_1__*) ; 
 int /*<<< orphan*/  trace_hardirqs_off () ; 
 int /*<<< orphan*/  update_cpu_boot_status (int /*<<< orphan*/ ) ; 

void secondary_start_kernel(void)
{
	u64 mpidr = read_cpuid_mpidr() & MPIDR_HWID_BITMASK;
	struct mm_struct *mm = &init_mm;
	unsigned int cpu;

	cpu = task_cpu(current);
	set_my_cpu_offset(per_cpu_offset(cpu));

	/*
	 * All kernel threads share the same mm context; grab a
	 * reference and switch to it.
	 */
	mmgrab(mm);
	current->active_mm = mm;

	/*
	 * TTBR0 is only used for the identity mapping at this stage. Make it
	 * point to zero page to avoid speculatively fetching new entries.
	 */
	cpu_uninstall_idmap();

	if (system_uses_irq_prio_masking())
		init_gic_priority_masking();

	preempt_disable();
	trace_hardirqs_off();

	/*
	 * If the system has established the capabilities, make sure
	 * this CPU ticks all of those. If it doesn't, the CPU will
	 * fail to come online.
	 */
	check_local_cpu_capabilities();

	if (cpu_ops[cpu]->cpu_postboot)
		cpu_ops[cpu]->cpu_postboot();

	/*
	 * Log the CPU info before it is marked online and might get read.
	 */
	cpuinfo_store_cpu();

	/*
	 * Enable GIC and timers.
	 */
	notify_cpu_starting(cpu);

	store_cpu_topology(cpu);
	numa_add_cpu(cpu);

	/*
	 * OK, now it's safe to let the boot CPU continue.  Wait for
	 * the CPU migration code to notice that the CPU is online
	 * before we continue.
	 */
	pr_info("CPU%u: Booted secondary processor 0x%010lx [0x%08x]\n",
					 cpu, (unsigned long)mpidr,
					 read_cpuid_id());
	update_cpu_boot_status(CPU_BOOT_SUCCESS);
	set_cpu_online(cpu, true);
	complete(&cpu_running);

	local_daif_restore(DAIF_PROCCTX);

	/*
	 * OK, it's off to the idle thread for us
	 */
	cpu_startup_entry(CPUHP_AP_ONLINE_IDLE);
}