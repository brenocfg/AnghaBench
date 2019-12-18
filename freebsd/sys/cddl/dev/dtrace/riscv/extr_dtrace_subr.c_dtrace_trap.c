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
typedef  int u_int ;
struct trapframe {int tf_sepc; } ;
struct TYPE_2__ {int cpuc_dtrace_flags; int /*<<< orphan*/  cpuc_dtrace_illval; } ;

/* Variables and functions */
 int CPU_DTRACE_BADADDR ; 
 int CPU_DTRACE_NOFAULT ; 
#define  EXCP_FAULT_FETCH 130 
#define  EXCP_FAULT_LOAD 129 
#define  EXCP_FAULT_STORE 128 
 TYPE_1__* cpu_core ; 
 size_t curcpu ; 

int
dtrace_trap(struct trapframe *frame, u_int type)
{
	/*
	 * A trap can occur while DTrace executes a probe. Before
	 * executing the probe, DTrace blocks re-scheduling and sets
	 * a flag in its per-cpu flags to indicate that it doesn't
	 * want to fault. On returning from the probe, the no-fault
	 * flag is cleared and finally re-scheduling is enabled.
	 *
	 * Check if DTrace has enabled 'no-fault' mode:
	 *
	 */

	if ((cpu_core[curcpu].cpuc_dtrace_flags & CPU_DTRACE_NOFAULT) != 0) {
		/*
		 * There are only a couple of trap types that are expected.
		 * All the rest will be handled in the usual way.
		 */
		switch (type) {
		case EXCP_FAULT_LOAD:
		case EXCP_FAULT_STORE:
		case EXCP_FAULT_FETCH:
			/* Flag a bad address. */
			cpu_core[curcpu].cpuc_dtrace_flags |= CPU_DTRACE_BADADDR;
			cpu_core[curcpu].cpuc_dtrace_illval = 0;

			/*
			 * Offset the instruction pointer to the instruction
			 * following the one causing the fault.
			 */
			frame->tf_sepc += 4;

			return (1);
		default:
			/* Handle all other traps in the usual way. */
			break;
		}
	}

	/* Handle the trap in the usual way. */
	return (0);
}