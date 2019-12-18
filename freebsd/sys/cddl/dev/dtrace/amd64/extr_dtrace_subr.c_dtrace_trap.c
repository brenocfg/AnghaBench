#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct trapframe {scalar_t__ tf_rip; int /*<<< orphan*/  tf_addr; } ;
struct TYPE_2__ {int cpuc_dtrace_flags; int /*<<< orphan*/  cpuc_dtrace_illval; } ;

/* Variables and functions */
 int CPU_DTRACE_BADADDR ; 
 int CPU_DTRACE_ILLOP ; 
 int CPU_DTRACE_NOFAULT ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PSL_I ; 
#define  T_PAGEFLT 129 
#define  T_PROTFLT 128 
 TYPE_1__* cpu_core ; 
 size_t curcpu ; 
 scalar_t__ dtrace_instr_size (int /*<<< orphan*/ *) ; 
 int read_rflags () ; 
 int /*<<< orphan*/  sched_pin () ; 
 int /*<<< orphan*/  sched_unpin () ; 

int
dtrace_trap(struct trapframe *frame, u_int type)
{
	uint16_t nofault;

	/*
	 * A trap can occur while DTrace executes a probe. Before
	 * executing the probe, DTrace blocks re-scheduling and sets
	 * a flag in its per-cpu flags to indicate that it doesn't
	 * want to fault. On returning from the probe, the no-fault
	 * flag is cleared and finally re-scheduling is enabled.
	 *
	 * Check if DTrace has enabled 'no-fault' mode:
	 */
	sched_pin();
	nofault = cpu_core[curcpu].cpuc_dtrace_flags & CPU_DTRACE_NOFAULT;
	sched_unpin();
	if (nofault) {
		KASSERT((read_rflags() & PSL_I) == 0, ("interrupts enabled"));

		/*
		 * There are only a couple of trap types that are expected.
		 * All the rest will be handled in the usual way.
		 */
		switch (type) {
		/* General protection fault. */
		case T_PROTFLT:
			/* Flag an illegal operation. */
			cpu_core[curcpu].cpuc_dtrace_flags |= CPU_DTRACE_ILLOP;

			/*
			 * Offset the instruction pointer to the instruction
			 * following the one causing the fault.
			 */
			frame->tf_rip += dtrace_instr_size((u_char *) frame->tf_rip);
			return (1);
		/* Page fault. */
		case T_PAGEFLT:
			/* Flag a bad address. */
			cpu_core[curcpu].cpuc_dtrace_flags |= CPU_DTRACE_BADADDR;
			cpu_core[curcpu].cpuc_dtrace_illval = frame->tf_addr;

			/*
			 * Offset the instruction pointer to the instruction
			 * following the one causing the fault.
			 */
			frame->tf_rip += dtrace_instr_size((u_char *) frame->tf_rip);
			return (1);
		default:
			/* Handle all other traps in the usual way. */
			break;
		}
	}

	/* Handle the trap in the usual way. */
	return (0);
}