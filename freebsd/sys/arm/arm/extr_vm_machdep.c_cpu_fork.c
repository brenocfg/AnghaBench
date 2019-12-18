#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct trapframe {scalar_t__ tf_r1; scalar_t__ tf_r0; int /*<<< orphan*/  tf_spsr; } ;
struct TYPE_7__ {int md_spinlock_count; void* md_tp; int /*<<< orphan*/  md_saved_cspr; } ;
struct thread {int td_kstack_pages; TYPE_3__ td_md; struct trapframe* td_frame; TYPE_1__* td_proc; struct pcb* td_pcb; scalar_t__ td_kstack; } ;
struct TYPE_8__ {int /*<<< orphan*/  fpscr; } ;
struct TYPE_6__ {void* sf_tpidrurw; int /*<<< orphan*/  sf_sp; void* sf_lr; void* sf_r5; void* sf_r4; } ;
struct pcb {int pcb_vfpcpu; TYPE_4__ pcb_vfpstate; TYPE_2__ pcb_regs; } ;
struct proc {int /*<<< orphan*/  p_vmspace; struct pcb p_md; } ;
struct mdproc {int pcb_vfpcpu; TYPE_4__ pcb_vfpstate; TYPE_2__ pcb_regs; } ;
typedef  void* register_t ;
struct TYPE_5__ {struct pcb p_md; } ;

/* Variables and functions */
 scalar_t__ ARM_TP_ADDRESS ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PSR_C ; 
 int /*<<< orphan*/  PSR_SVC32_MODE ; 
 int RFPROC ; 
 int /*<<< orphan*/  STACKALIGN (struct trapframe*) ; 
 int /*<<< orphan*/  bcopy (struct pcb*,struct pcb*,int) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 struct thread* curthread ; 
 scalar_t__ fork_return ; 
 scalar_t__ fork_trampoline ; 
 scalar_t__ get_tls () ; 
 int /*<<< orphan*/  initial_fpscr ; 
 int /*<<< orphan*/  pmap_set_pcb_pagedir (int /*<<< orphan*/ ,struct pcb*) ; 
 int /*<<< orphan*/  vfp_store (TYPE_4__*,int) ; 
 int /*<<< orphan*/  vmspace_pmap (int /*<<< orphan*/ ) ; 

void
cpu_fork(struct thread *td1, struct proc *p2, struct thread *td2, int flags)
{
	struct pcb *pcb2;
	struct trapframe *tf;
	struct mdproc *mdp2;

	if ((flags & RFPROC) == 0)
		return;

	/* Point the pcb to the top of the stack */
	pcb2 = (struct pcb *)
	    (td2->td_kstack + td2->td_kstack_pages * PAGE_SIZE) - 1;
#ifdef VFP
	/* Store actual state of VFP */
	if (curthread == td1) {
		critical_enter();
		vfp_store(&td1->td_pcb->pcb_vfpstate, false);
		critical_exit();
	}
#endif
	td2->td_pcb = pcb2;

	/* Clone td1's pcb */
	bcopy(td1->td_pcb, pcb2, sizeof(*pcb2));

	/* Point to mdproc and then copy over td1's contents */
	mdp2 = &p2->p_md;
	bcopy(&td1->td_proc->p_md, mdp2, sizeof(*mdp2));

	/* Point the frame to the stack in front of pcb and copy td1's frame */
	td2->td_frame = (struct trapframe *)pcb2 - 1;
	*td2->td_frame = *td1->td_frame;

	/*
	 * Create a new fresh stack for the new process.
	 * Copy the trap frame for the return to user mode as if from a
	 * syscall.  This copies most of the user mode register values.
	 */
	pmap_set_pcb_pagedir(vmspace_pmap(p2->p_vmspace), pcb2);
	pcb2->pcb_regs.sf_r4 = (register_t)fork_return;
	pcb2->pcb_regs.sf_r5 = (register_t)td2;
	pcb2->pcb_regs.sf_lr = (register_t)fork_trampoline;
	pcb2->pcb_regs.sf_sp = STACKALIGN(td2->td_frame);
#if __ARM_ARCH >= 6
	pcb2->pcb_regs.sf_tpidrurw = (register_t)get_tls();
#endif

	pcb2->pcb_vfpcpu = -1;
	pcb2->pcb_vfpstate.fpscr = initial_fpscr;

	tf = td2->td_frame;
	tf->tf_spsr &= ~PSR_C;
	tf->tf_r0 = 0;
	tf->tf_r1 = 0;


	/* Setup to release spin count in fork_exit(). */
	td2->td_md.md_spinlock_count = 1;
	td2->td_md.md_saved_cspr = PSR_SVC32_MODE;
#if __ARM_ARCH < 6
	td2->td_md.md_tp = *(register_t *)ARM_TP_ADDRESS;
#endif
}