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
struct thread {struct pcb* td_pcb; } ;
struct pcb {int pcb_flags; scalar_t__ pcb_initial_fpucw; int /*<<< orphan*/  pcb_save; } ;

/* Variables and functions */
 int PCB_FPUINITDONE ; 
 int PCB_USERFPUINITDONE ; 
 scalar_t__ PCB_USER_FPU (struct pcb*) ; 
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,struct thread*) ; 
 scalar_t__ __INITIAL_FPUCW__ ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_max_ext_state_size ; 
 int /*<<< orphan*/  fldcw (scalar_t__) ; 
 int /*<<< orphan*/  fpcurthread ; 
 int /*<<< orphan*/  fpu_clean_state () ; 
 int /*<<< orphan*/  fpu_initialstate ; 
 int /*<<< orphan*/  fpurestore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pcb_flags (struct pcb*,int) ; 
 int /*<<< orphan*/  stop_emulating () ; 

__attribute__((used)) static void
restore_fpu_curthread(struct thread *td)
{
	struct pcb *pcb;

	/*
	 * Record new context early in case frstor causes a trap.
	 */
	PCPU_SET(fpcurthread, td);

	stop_emulating();
	fpu_clean_state();
	pcb = td->td_pcb;

	if ((pcb->pcb_flags & PCB_FPUINITDONE) == 0) {
		/*
		 * This is the first time this thread has used the FPU or
		 * the PCB doesn't contain a clean FPU state.  Explicitly
		 * load an initial state.
		 *
		 * We prefer to restore the state from the actual save
		 * area in PCB instead of directly loading from
		 * fpu_initialstate, to ignite the XSAVEOPT
		 * tracking engine.
		 */
		bcopy(fpu_initialstate, pcb->pcb_save,
		    cpu_max_ext_state_size);
		fpurestore(pcb->pcb_save);
		if (pcb->pcb_initial_fpucw != __INITIAL_FPUCW__)
			fldcw(pcb->pcb_initial_fpucw);
		if (PCB_USER_FPU(pcb))
			set_pcb_flags(pcb, PCB_FPUINITDONE |
			    PCB_USERFPUINITDONE);
		else
			set_pcb_flags(pcb, PCB_FPUINITDONE);
	} else
		fpurestore(pcb->pcb_save);
}