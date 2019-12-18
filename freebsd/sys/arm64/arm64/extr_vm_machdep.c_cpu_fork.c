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
struct trapframe {int pcb_fpflags; int tf_spsr; uintptr_t* pcb_x; uintptr_t pcb_sp; int /*<<< orphan*/  pcb_vfpcpu; int /*<<< orphan*/  pcb_fpustate; int /*<<< orphan*/ * pcb_fpusaved; scalar_t__* tf_x; void* pcb_tpidrro_el0; void* pcb_tpidr_el0; } ;
struct TYPE_2__ {int md_spinlock_count; int md_saved_daif; } ;
struct thread {int td_kstack_pages; TYPE_1__ td_md; struct trapframe* td_pcb; struct trapframe* td_frame; scalar_t__ td_kstack; } ;
struct proc {int dummy; } ;
struct pcb {int pcb_fpflags; int tf_spsr; uintptr_t* pcb_x; uintptr_t pcb_sp; int /*<<< orphan*/  pcb_vfpcpu; int /*<<< orphan*/  pcb_fpustate; int /*<<< orphan*/ * pcb_fpusaved; scalar_t__* tf_x; void* pcb_tpidrro_el0; void* pcb_tpidr_el0; } ;

/* Variables and functions */
 int DAIF_I_MASKED ; 
 int PAGE_SIZE ; 
 int PCB_FP_STARTED ; 
 size_t PCB_LR ; 
 int PSR_DAIF ; 
 int PSR_M_32 ; 
 void* READ_SPECIALREG (int /*<<< orphan*/ ) ; 
 int RFPROC ; 
 scalar_t__ STACKALIGN (struct trapframe*) ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int /*<<< orphan*/  bcopy (struct trapframe*,struct trapframe*,int) ; 
 struct thread* curthread ; 
 scalar_t__ fork_return ; 
 scalar_t__ fork_trampoline ; 
 int /*<<< orphan*/  tpidr_el0 ; 
 int /*<<< orphan*/  tpidrro_el0 ; 
 int /*<<< orphan*/  vfp_save_state (struct thread*,struct trapframe*) ; 

void
cpu_fork(struct thread *td1, struct proc *p2, struct thread *td2, int flags)
{
	struct pcb *pcb2;
	struct trapframe *tf;

	if ((flags & RFPROC) == 0)
		return;

	if (td1 == curthread) {
		/*
		 * Save the tpidr_el0 and the vfp state, these normally happen
		 * in cpu_switch, but if userland changes these then forks
		 * this may not have happened.
		 */
		td1->td_pcb->pcb_tpidr_el0 = READ_SPECIALREG(tpidr_el0);
		td1->td_pcb->pcb_tpidrro_el0 = READ_SPECIALREG(tpidrro_el0);
#ifdef VFP
		if ((td1->td_pcb->pcb_fpflags & PCB_FP_STARTED) != 0)
			vfp_save_state(td1, td1->td_pcb);
#endif
	}

	pcb2 = (struct pcb *)(td2->td_kstack +
	    td2->td_kstack_pages * PAGE_SIZE) - 1;

	td2->td_pcb = pcb2;
	bcopy(td1->td_pcb, pcb2, sizeof(*pcb2));

	tf = (struct trapframe *)STACKALIGN((struct trapframe *)pcb2 - 1);
	bcopy(td1->td_frame, tf, sizeof(*tf));
	tf->tf_x[0] = 0;
	tf->tf_x[1] = 0;
	tf->tf_spsr = td1->td_frame->tf_spsr & (PSR_M_32 | PSR_DAIF);

	td2->td_frame = tf;

	/* Set the return value registers for fork() */
	td2->td_pcb->pcb_x[8] = (uintptr_t)fork_return;
	td2->td_pcb->pcb_x[9] = (uintptr_t)td2;
	td2->td_pcb->pcb_x[PCB_LR] = (uintptr_t)fork_trampoline;
	td2->td_pcb->pcb_sp = (uintptr_t)td2->td_frame;
	td2->td_pcb->pcb_fpusaved = &td2->td_pcb->pcb_fpustate;
	td2->td_pcb->pcb_vfpcpu = UINT_MAX;

	/* Setup to release spin count in fork_exit(). */
	td2->td_md.md_spinlock_count = 1;
	td2->td_md.md_saved_daif = td1->td_md.md_saved_daif & ~DAIF_I_MASKED;
}