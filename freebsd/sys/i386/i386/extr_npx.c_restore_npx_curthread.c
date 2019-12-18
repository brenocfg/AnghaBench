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
struct thread {int dummy; } ;
struct pcb {int pcb_flags; scalar_t__ pcb_initial_npxcw; int /*<<< orphan*/  pcb_save; } ;

/* Variables and functions */
 int PCB_NPXINITDONE ; 
 int PCB_NPXUSERINITDONE ; 
 scalar_t__ PCB_USER_FPU (struct pcb*) ; 
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,struct thread*) ; 
 scalar_t__ __INITIAL_NPXCW__ ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_fxsr ; 
 int /*<<< orphan*/  cpu_max_ext_state_size ; 
 int /*<<< orphan*/  fldcw (scalar_t__) ; 
 int /*<<< orphan*/  fpcurthread ; 
 int /*<<< orphan*/  fpu_clean_state () ; 
 int /*<<< orphan*/  fpurstor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  npx_initialstate ; 
 int /*<<< orphan*/  stop_emulating () ; 

__attribute__((used)) static void
restore_npx_curthread(struct thread *td, struct pcb *pcb)
{

	/*
	 * Record new context early in case frstor causes a trap.
	 */
	PCPU_SET(fpcurthread, td);

	stop_emulating();
	if (cpu_fxsr)
		fpu_clean_state();

	if ((pcb->pcb_flags & PCB_NPXINITDONE) == 0) {
		/*
		 * This is the first time this thread has used the FPU or
		 * the PCB doesn't contain a clean FPU state.  Explicitly
		 * load an initial state.
		 *
		 * We prefer to restore the state from the actual save
		 * area in PCB instead of directly loading from
		 * npx_initialstate, to ignite the XSAVEOPT
		 * tracking engine.
		 */
		bcopy(npx_initialstate, pcb->pcb_save, cpu_max_ext_state_size);
		fpurstor(pcb->pcb_save);
		if (pcb->pcb_initial_npxcw != __INITIAL_NPXCW__)
			fldcw(pcb->pcb_initial_npxcw);
		pcb->pcb_flags |= PCB_NPXINITDONE;
		if (PCB_USER_FPU(pcb))
			pcb->pcb_flags |= PCB_NPXUSERINITDONE;
	} else {
		fpurstor(pcb->pcb_save);
	}
}