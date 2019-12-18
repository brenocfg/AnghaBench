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
typedef  int u_long ;
struct trapframe {int tf_rflags; int tf_rsp; int tf_rdi; int /*<<< orphan*/  tf_flags; int /*<<< orphan*/  tf_gs; int /*<<< orphan*/  tf_fs; void* tf_es; void* tf_ds; int /*<<< orphan*/  tf_cs; void* tf_ss; int /*<<< orphan*/  tf_rip; } ;
struct thread {TYPE_2__* td_proc; struct pcb* td_pcb; struct trapframe* td_frame; } ;
struct pcb {int pcb_flags; scalar_t__ pcb_dr7; scalar_t__ pcb_dr6; scalar_t__ pcb_dr3; scalar_t__ pcb_dr2; scalar_t__ pcb_dr1; scalar_t__ pcb_dr0; int /*<<< orphan*/  pcb_initial_fpucw; scalar_t__ pcb_gsbase; scalar_t__ pcb_fsbase; } ;
struct image_params {int /*<<< orphan*/  entry_addr; } ;
typedef  int register_t ;
struct TYPE_3__ {int /*<<< orphan*/ * md_ldt; } ;
struct TYPE_4__ {TYPE_1__ p_md; } ;

/* Variables and functions */
 int PCB_32BIT ; 
 int PCB_DBREGS ; 
 int PSL_T ; 
 int PSL_USER ; 
 int /*<<< orphan*/  TF_HASSEGS ; 
 int /*<<< orphan*/  __INITIAL_FPUCW__ ; 
 int /*<<< orphan*/  _ucodesel ; 
 void* _udatasel ; 
 int /*<<< orphan*/  _ufssel ; 
 int /*<<< orphan*/  _ugssel ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  clear_pcb_flags (struct pcb*,int) ; 
 struct pcb* curpcb ; 
 int /*<<< orphan*/  fpstate_drop (struct thread*) ; 
 int /*<<< orphan*/  reset_dbregs () ; 
 int /*<<< orphan*/  update_pcb_bases (struct pcb*) ; 
 int /*<<< orphan*/  user_ldt_free (struct thread*) ; 

void
exec_setregs(struct thread *td, struct image_params *imgp, u_long stack)
{
	struct trapframe *regs;
	struct pcb *pcb;
	register_t saved_rflags;

	regs = td->td_frame;
	pcb = td->td_pcb;

	if (td->td_proc->p_md.md_ldt != NULL)
		user_ldt_free(td);

	update_pcb_bases(pcb);
	pcb->pcb_fsbase = 0;
	pcb->pcb_gsbase = 0;
	clear_pcb_flags(pcb, PCB_32BIT);
	pcb->pcb_initial_fpucw = __INITIAL_FPUCW__;

	saved_rflags = regs->tf_rflags & PSL_T;
	bzero((char *)regs, sizeof(struct trapframe));
	regs->tf_rip = imgp->entry_addr;
	regs->tf_rsp = ((stack - 8) & ~0xFul) + 8;
	regs->tf_rdi = stack;		/* argv */
	regs->tf_rflags = PSL_USER | saved_rflags;
	regs->tf_ss = _udatasel;
	regs->tf_cs = _ucodesel;
	regs->tf_ds = _udatasel;
	regs->tf_es = _udatasel;
	regs->tf_fs = _ufssel;
	regs->tf_gs = _ugssel;
	regs->tf_flags = TF_HASSEGS;

	/*
	 * Reset the hardware debug registers if they were in use.
	 * They won't have any meaning for the newly exec'd process.
	 */
	if (pcb->pcb_flags & PCB_DBREGS) {
		pcb->pcb_dr0 = 0;
		pcb->pcb_dr1 = 0;
		pcb->pcb_dr2 = 0;
		pcb->pcb_dr3 = 0;
		pcb->pcb_dr6 = 0;
		pcb->pcb_dr7 = 0;
		if (pcb == curpcb) {
			/*
			 * Clear the debug registers on the running
			 * CPU, otherwise they will end up affecting
			 * the next process we switch to.
			 */
			reset_dbregs();
		}
		clear_pcb_flags(pcb, PCB_DBREGS);
	}

	/*
	 * Drop the FP state if we hold it, so that the process gets a
	 * clean FP state if it uses the FPU again.
	 */
	fpstate_drop(td);
}