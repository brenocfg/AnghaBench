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
typedef  int /*<<< orphan*/  u_long ;
struct trapframe {int tf_rflags; int /*<<< orphan*/  tf_flags; int /*<<< orphan*/  tf_gs; int /*<<< orphan*/  tf_fs; void* tf_es; void* tf_ds; int /*<<< orphan*/  tf_rbx; int /*<<< orphan*/  tf_cs; void* tf_ss; int /*<<< orphan*/  tf_rsp; int /*<<< orphan*/  tf_rip; } ;
struct thread {TYPE_2__* td_proc; struct pcb* td_pcb; struct trapframe* td_frame; } ;
struct pcb {int /*<<< orphan*/  pcb_initial_fpucw; scalar_t__ pcb_gsbase; scalar_t__ pcb_fsbase; } ;
struct image_params {int /*<<< orphan*/  ps_strings; int /*<<< orphan*/  entry_addr; } ;
typedef  int register_t ;
struct TYPE_3__ {int /*<<< orphan*/ * md_ldt; } ;
struct TYPE_4__ {TYPE_1__ p_md; } ;

/* Variables and functions */
 int PCB_32BIT ; 
 int PCB_FULL_IRET ; 
 int PSL_T ; 
 int PSL_USER ; 
 int /*<<< orphan*/  TF_HASSEGS ; 
 int /*<<< orphan*/  __INITIAL_FPUCW_I386__ ; 
 int /*<<< orphan*/  _ucode32sel ; 
 void* _udatasel ; 
 int /*<<< orphan*/  _ufssel ; 
 int /*<<< orphan*/  _ugssel ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  fpstate_drop (struct thread*) ; 
 int /*<<< orphan*/  set_pcb_flags (struct pcb*,int) ; 
 int /*<<< orphan*/  setup_lcall_gate () ; 
 int /*<<< orphan*/  user_ldt_free (struct thread*) ; 

void
ia32_setregs(struct thread *td, struct image_params *imgp, u_long stack)
{
	struct trapframe *regs;
	struct pcb *pcb;
	register_t saved_rflags;

	regs = td->td_frame;
	pcb = td->td_pcb;

	if (td->td_proc->p_md.md_ldt != NULL)
		user_ldt_free(td);
#ifdef COMPAT_43
	setup_lcall_gate();
#endif

	pcb->pcb_fsbase = 0;
	pcb->pcb_gsbase = 0;
	pcb->pcb_initial_fpucw = __INITIAL_FPUCW_I386__;

	saved_rflags = regs->tf_rflags & PSL_T;
	bzero((char *)regs, sizeof(struct trapframe));
	regs->tf_rip = imgp->entry_addr;
	regs->tf_rsp = stack;
	regs->tf_rflags = PSL_USER | saved_rflags;
	regs->tf_ss = _udatasel;
	regs->tf_cs = _ucode32sel;
	regs->tf_rbx = imgp->ps_strings;
	regs->tf_ds = _udatasel;
	regs->tf_es = _udatasel;
	regs->tf_fs = _ufssel;
	regs->tf_gs = _ugssel;
	regs->tf_flags = TF_HASSEGS;

	fpstate_drop(td);

	/* Return via doreti so that we can change to a different %cs */
	set_pcb_flags(pcb, PCB_32BIT | PCB_FULL_IRET);
}