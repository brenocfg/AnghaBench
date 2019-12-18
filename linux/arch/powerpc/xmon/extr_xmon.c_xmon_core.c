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
struct pt_regs {unsigned long nip; int msr; int /*<<< orphan*/  trap; } ;
struct bpt {unsigned long address; int /*<<< orphan*/ * instr; int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 char* BP_NUM (struct bpt*) ; 
 int EOF ; 
 scalar_t__ IS_RFID (int /*<<< orphan*/ ) ; 
 int JMP_BUF_LEN ; 
 int MSR_64BIT ; 
 int MSR_DE ; 
 int MSR_IR ; 
 int MSR_PR ; 
 int TRAP (struct pt_regs*) ; 
 struct bpt* at_breakpoint (unsigned long) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  barrier () ; 
 long* bus_error_jmp ; 
 scalar_t__ catch_spr_faults ; 
 int cmds (struct pt_regs*) ; 
 int /*<<< orphan*/  cpumask_clear_cpu (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int,int /*<<< orphan*/ *) ; 
 scalar_t__ cpumask_test_cpu (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpus_in_xmon ; 
 int /*<<< orphan*/  disable_surveillance () ; 
 int emulate_step (struct pt_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  excprint (struct pt_regs*) ; 
 int /*<<< orphan*/  get_output_lock () ; 
 int /*<<< orphan*/  getvecname (int) ; 
 int /*<<< orphan*/  hard_irq_disable () ; 
 struct bpt* in_breakpoint_table (unsigned long,unsigned long*) ; 
 int in_xmon ; 
 int /*<<< orphan*/  insert_bpts () ; 
 int /*<<< orphan*/  insert_cpu_bpts () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  longjmp (long*,int) ; 
 int /*<<< orphan*/  mb () ; 
 int num_online_cpus () ; 
 int /*<<< orphan*/  ppc_inst_dump (unsigned long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  release_output_lock () ; 
 int /*<<< orphan*/  remove_bpts () ; 
 int /*<<< orphan*/  remove_cpu_bpts () ; 
 scalar_t__ setjmp (long*) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  smp_send_debugger_break () ; 
 int /*<<< orphan*/  spin_begin () ; 
 int /*<<< orphan*/  spin_cpu_relax () ; 
 int /*<<< orphan*/  spin_end () ; 
 int test_and_set_bit (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  touch_nmi_watchdog () ; 
 int /*<<< orphan*/  tracing_enabled ; 
 int /*<<< orphan*/  tracing_is_on () ; 
 int /*<<< orphan*/  tracing_off () ; 
 scalar_t__ unrecoverable_excp (struct pt_regs*) ; 
 int /*<<< orphan*/  wait_for_other_cpus (int) ; 
 int /*<<< orphan*/  wmb () ; 
 long** xmon_fault_jmp ; 
 int xmon_gate ; 
 int xmon_owner ; 
 int /*<<< orphan*/  xmon_print_symbol (unsigned long,char*,char*) ; 
 int xmon_taken ; 

__attribute__((used)) static int xmon_core(struct pt_regs *regs, int fromipi)
{
	int cmd = 0;
	struct bpt *bp;
	long recurse_jmp[JMP_BUF_LEN];
	unsigned long offset;
	unsigned long flags;
#ifdef CONFIG_SMP
	int cpu;
	int secondary;
#endif

	local_irq_save(flags);
	hard_irq_disable();

	if (!fromipi) {
		tracing_enabled = tracing_is_on();
		tracing_off();
	}

	bp = in_breakpoint_table(regs->nip, &offset);
	if (bp != NULL) {
		regs->nip = bp->address + offset;
		atomic_dec(&bp->ref_count);
	}

	remove_cpu_bpts();

#ifdef CONFIG_SMP
	cpu = smp_processor_id();
	if (cpumask_test_cpu(cpu, &cpus_in_xmon)) {
		/*
		 * We catch SPR read/write faults here because the 0x700, 0xf60
		 * etc. handlers don't call debugger_fault_handler().
		 */
		if (catch_spr_faults)
			longjmp(bus_error_jmp, 1);
		get_output_lock();
		excprint(regs);
		printf("cpu 0x%x: Exception %lx %s in xmon, "
		       "returning to main loop\n",
		       cpu, regs->trap, getvecname(TRAP(regs)));
		release_output_lock();
		longjmp(xmon_fault_jmp[cpu], 1);
	}

	if (setjmp(recurse_jmp) != 0) {
		if (!in_xmon || !xmon_gate) {
			get_output_lock();
			printf("xmon: WARNING: bad recursive fault "
			       "on cpu 0x%x\n", cpu);
			release_output_lock();
			goto waiting;
		}
		secondary = !(xmon_taken && cpu == xmon_owner);
		goto cmdloop;
	}

	xmon_fault_jmp[cpu] = recurse_jmp;

	bp = NULL;
	if ((regs->msr & (MSR_IR|MSR_PR|MSR_64BIT)) == (MSR_IR|MSR_64BIT))
		bp = at_breakpoint(regs->nip);
	if (bp || unrecoverable_excp(regs))
		fromipi = 0;

	if (!fromipi) {
		get_output_lock();
		excprint(regs);
		if (bp) {
			printf("cpu 0x%x stopped at breakpoint 0x%tx (",
			       cpu, BP_NUM(bp));
			xmon_print_symbol(regs->nip, " ", ")\n");
		}
		if (unrecoverable_excp(regs))
			printf("WARNING: exception is not recoverable, "
			       "can't continue\n");
		release_output_lock();
	}

	cpumask_set_cpu(cpu, &cpus_in_xmon);

 waiting:
	secondary = 1;
	spin_begin();
	while (secondary && !xmon_gate) {
		if (in_xmon == 0) {
			if (fromipi) {
				spin_end();
				goto leave;
			}
			secondary = test_and_set_bit(0, &in_xmon);
		}
		spin_cpu_relax();
		touch_nmi_watchdog();
	}
	spin_end();

	if (!secondary && !xmon_gate) {
		/* we are the first cpu to come in */
		/* interrupt other cpu(s) */
		int ncpus = num_online_cpus();

		xmon_owner = cpu;
		mb();
		if (ncpus > 1) {
			/*
			 * A system reset (trap == 0x100) can be triggered on
			 * all CPUs, so when we come in via 0x100 try waiting
			 * for the other CPUs to come in before we send the
			 * debugger break (IPI). This is similar to
			 * crash_kexec_secondary().
			 */
			if (TRAP(regs) != 0x100 || !wait_for_other_cpus(ncpus))
				smp_send_debugger_break();

			wait_for_other_cpus(ncpus);
		}
		remove_bpts();
		disable_surveillance();
		/* for breakpoint or single step, print the current instr. */
		if (bp || TRAP(regs) == 0xd00)
			ppc_inst_dump(regs->nip, 1, 0);
		printf("enter ? for help\n");
		mb();
		xmon_gate = 1;
		barrier();
		touch_nmi_watchdog();
	}

 cmdloop:
	while (in_xmon) {
		if (secondary) {
			spin_begin();
			if (cpu == xmon_owner) {
				if (!test_and_set_bit(0, &xmon_taken)) {
					secondary = 0;
					spin_end();
					continue;
				}
				/* missed it */
				while (cpu == xmon_owner)
					spin_cpu_relax();
			}
			spin_cpu_relax();
			touch_nmi_watchdog();
		} else {
			cmd = cmds(regs);
			if (cmd != 0) {
				/* exiting xmon */
				insert_bpts();
				xmon_gate = 0;
				wmb();
				in_xmon = 0;
				break;
			}
			/* have switched to some other cpu */
			secondary = 1;
		}
	}
 leave:
	cpumask_clear_cpu(cpu, &cpus_in_xmon);
	xmon_fault_jmp[cpu] = NULL;
#else
	/* UP is simple... */
	if (in_xmon) {
		printf("Exception %lx %s in xmon, returning to main loop\n",
		       regs->trap, getvecname(TRAP(regs)));
		longjmp(xmon_fault_jmp[0], 1);
	}
	if (setjmp(recurse_jmp) == 0) {
		xmon_fault_jmp[0] = recurse_jmp;
		in_xmon = 1;

		excprint(regs);
		bp = at_breakpoint(regs->nip);
		if (bp) {
			printf("Stopped at breakpoint %tx (", BP_NUM(bp));
			xmon_print_symbol(regs->nip, " ", ")\n");
		}
		if (unrecoverable_excp(regs))
			printf("WARNING: exception is not recoverable, "
			       "can't continue\n");
		remove_bpts();
		disable_surveillance();
		/* for breakpoint or single step, print the current instr. */
		if (bp || TRAP(regs) == 0xd00)
			ppc_inst_dump(regs->nip, 1, 0);
		printf("enter ? for help\n");
	}

	cmd = cmds(regs);

	insert_bpts();
	in_xmon = 0;
#endif

#ifdef CONFIG_BOOKE
	if (regs->msr & MSR_DE) {
		bp = at_breakpoint(regs->nip);
		if (bp != NULL) {
			regs->nip = (unsigned long) &bp->instr[0];
			atomic_inc(&bp->ref_count);
		}
	}
#else
	if ((regs->msr & (MSR_IR|MSR_PR|MSR_64BIT)) == (MSR_IR|MSR_64BIT)) {
		bp = at_breakpoint(regs->nip);
		if (bp != NULL) {
			int stepped = emulate_step(regs, bp->instr[0]);
			if (stepped == 0) {
				regs->nip = (unsigned long) &bp->instr[0];
				atomic_inc(&bp->ref_count);
			} else if (stepped < 0) {
				printf("Couldn't single-step %s instruction\n",
				    (IS_RFID(bp->instr[0])? "rfid": "mtmsrd"));
			}
		}
	}
#endif
	insert_cpu_bpts();

	touch_nmi_watchdog();
	local_irq_restore(flags);

	return cmd != 'X' && cmd != EOF;
}