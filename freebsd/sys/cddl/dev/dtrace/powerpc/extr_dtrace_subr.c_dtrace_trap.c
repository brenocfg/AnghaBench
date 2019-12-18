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
struct trapframe {int srr1; int dar; int srr0; } ;
struct TYPE_2__ {int cpuc_dtrace_flags; int cpuc_dtrace_illval; } ;

/* Variables and functions */
 int CPU_DTRACE_BADADDR ; 
 int CPU_DTRACE_NOFAULT ; 
#define  EXC_DSE 131 
#define  EXC_DSI 130 
#define  EXC_ISE 129 
#define  EXC_ISI 128 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PSL_EE ; 
 TYPE_1__* cpu_core ; 
 size_t curcpu ; 
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
		KASSERT((frame->srr1 & PSL_EE) == 0, ("interrupts enabled"));
		/*
		 * There are only a couple of trap types that are expected.
		 * All the rest will be handled in the usual way.
		 */
		switch (type) {
		/* Page fault. */
		case EXC_DSI:
		case EXC_DSE:
			/* Flag a bad address. */
			cpu_core[curcpu].cpuc_dtrace_flags |= CPU_DTRACE_BADADDR;
			cpu_core[curcpu].cpuc_dtrace_illval = frame->dar;

			/*
			 * Offset the instruction pointer to the instruction
			 * following the one causing the fault.
			 */
			frame->srr0 += sizeof(int);
			return (1);
		case EXC_ISI:
		case EXC_ISE:
			/* Flag a bad address. */
			cpu_core[curcpu].cpuc_dtrace_flags |= CPU_DTRACE_BADADDR;
			cpu_core[curcpu].cpuc_dtrace_illval = frame->srr0;

			/*
			 * Offset the instruction pointer to the instruction
			 * following the one causing the fault.
			 */
			frame->srr0 += sizeof(int);
			return (1);
		default:
			/* Handle all other traps in the usual way. */
			break;
		}
	}

	/* Handle the trap in the usual way. */
	return (0);
}