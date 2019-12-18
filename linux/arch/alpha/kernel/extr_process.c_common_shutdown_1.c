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
struct percpu_struct {unsigned long flags; } ;
struct halt_info {scalar_t__ mode; int /*<<< orphan*/  restart_cmd; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* kill_arch ) (scalar_t__) ;} ;
struct TYPE_3__ {int processor_size; scalar_t__ processor_offset; } ;

/* Variables and functions */
 scalar_t__ LINUX_REBOOT_CMD_RESTART ; 
 scalar_t__ MAX_NR_CONSOLES ; 
 TYPE_2__ alpha_mv ; 
 scalar_t__ alpha_using_srm ; 
 int /*<<< orphan*/  barrier () ; 
 int boot_cpuid ; 
 int /*<<< orphan*/  console_lock () ; 
 int /*<<< orphan*/  console_unlock () ; 
 int /*<<< orphan*/  cpu_present_mask ; 
 scalar_t__ cpumask_weight (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_take_over_console (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  dummy_con ; 
 int /*<<< orphan*/  halt () ; 
 TYPE_1__* hwrpb ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  irq_exit () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  pci_restore_srm_config () ; 
 int /*<<< orphan*/  set_cpu_possible (int,int) ; 
 int /*<<< orphan*/  set_cpu_present (int,int) ; 
 int /*<<< orphan*/  set_hae (int /*<<< orphan*/ ) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  srm_hae ; 
 int /*<<< orphan*/  srm_paging_stop () ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

__attribute__((used)) static void
common_shutdown_1(void *generic_ptr)
{
	struct halt_info *how = (struct halt_info *)generic_ptr;
	struct percpu_struct *cpup;
	unsigned long *pflags, flags;
	int cpuid = smp_processor_id();

	/* No point in taking interrupts anymore. */
	local_irq_disable();

	cpup = (struct percpu_struct *)
			((unsigned long)hwrpb + hwrpb->processor_offset
			 + hwrpb->processor_size * cpuid);
	pflags = &cpup->flags;
	flags = *pflags;

	/* Clear reason to "default"; clear "bootstrap in progress". */
	flags &= ~0x00ff0001UL;

#ifdef CONFIG_SMP
	/* Secondaries halt here. */
	if (cpuid != boot_cpuid) {
		flags |= 0x00040000UL; /* "remain halted" */
		*pflags = flags;
		set_cpu_present(cpuid, false);
		set_cpu_possible(cpuid, false);
		halt();
	}
#endif

	if (how->mode == LINUX_REBOOT_CMD_RESTART) {
		if (!how->restart_cmd) {
			flags |= 0x00020000UL; /* "cold bootstrap" */
		} else {
			/* For SRM, we could probably set environment
			   variables to get this to work.  We'd have to
			   delay this until after srm_paging_stop unless
			   we ever got srm_fixup working.

			   At the moment, SRM will use the last boot device,
			   but the file and flags will be the defaults, when
			   doing a "warm" bootstrap.  */
			flags |= 0x00030000UL; /* "warm bootstrap" */
		}
	} else {
		flags |= 0x00040000UL; /* "remain halted" */
	}
	*pflags = flags;

#ifdef CONFIG_SMP
	/* Wait for the secondaries to halt. */
	set_cpu_present(boot_cpuid, false);
	set_cpu_possible(boot_cpuid, false);
	while (cpumask_weight(cpu_present_mask))
		barrier();
#endif

	/* If booted from SRM, reset some of the original environment. */
	if (alpha_using_srm) {
#ifdef CONFIG_DUMMY_CONSOLE
		/* If we've gotten here after SysRq-b, leave interrupt
		   context before taking over the console. */
		if (in_interrupt())
			irq_exit();
		/* This has the effect of resetting the VGA video origin.  */
		console_lock();
		do_take_over_console(&dummy_con, 0, MAX_NR_CONSOLES-1, 1);
		console_unlock();
#endif
		pci_restore_srm_config();
		set_hae(srm_hae);
	}

	if (alpha_mv.kill_arch)
		alpha_mv.kill_arch(how->mode);

	if (! alpha_using_srm && how->mode != LINUX_REBOOT_CMD_RESTART) {
		/* Unfortunately, since MILO doesn't currently understand
		   the hwrpb bits above, we can't reliably halt the 
		   processor and keep it halted.  So just loop.  */
		return;
	}

	if (alpha_using_srm)
		srm_paging_stop();

	halt();
}