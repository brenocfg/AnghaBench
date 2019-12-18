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
struct trapframe {int dummy; } ;
struct TYPE_2__ {int md_spinlock_count; int md_saved_flags; } ;
struct thread {TYPE_1__ td_md; struct pcb* td_frame; struct pcb* td_pcb; } ;
struct pcb {int pcb_flags; int pcb_esi; int pcb_esp; int pcb_ebx; int /*<<< orphan*/ * pcb_ext; int /*<<< orphan*/  pcb_gs; scalar_t__ pcb_eip; scalar_t__ pcb_ebp; scalar_t__ pcb_edi; int /*<<< orphan*/  tf_eflags; struct pcb* pcb_save; } ;

/* Variables and functions */
 int PCB_KERNNPX ; 
 int PCB_NPXINITDONE ; 
 int PCB_NPXUSERINITDONE ; 
 int PSL_I ; 
 int PSL_KERNEL ; 
 int /*<<< orphan*/  PSL_T ; 
 int /*<<< orphan*/  bcopy (struct pcb*,struct pcb*,int) ; 
 int cpu_max_ext_state_size ; 
 scalar_t__ fork_return ; 
 scalar_t__ fork_trampoline ; 
 struct pcb* get_pcb_user_save_pcb (struct pcb*) ; 
 struct pcb* get_pcb_user_save_td (struct thread*) ; 
 int /*<<< orphan*/  rgs () ; 
 scalar_t__ setidt_disp ; 

void
cpu_copy_thread(struct thread *td, struct thread *td0)
{
	struct pcb *pcb2;

	/* Point the pcb to the top of the stack. */
	pcb2 = td->td_pcb;

	/*
	 * Copy the upcall pcb.  This loads kernel regs.
	 * Those not loaded individually below get their default
	 * values here.
	 */
	bcopy(td0->td_pcb, pcb2, sizeof(*pcb2));
	pcb2->pcb_flags &= ~(PCB_NPXINITDONE | PCB_NPXUSERINITDONE |
	    PCB_KERNNPX);
	pcb2->pcb_save = get_pcb_user_save_pcb(pcb2);
	bcopy(get_pcb_user_save_td(td0), pcb2->pcb_save,
	    cpu_max_ext_state_size);

	/*
	 * Create a new fresh stack for the new thread.
	 */
	bcopy(td0->td_frame, td->td_frame, sizeof(struct trapframe));

	/* If the current thread has the trap bit set (i.e. a debugger had
	 * single stepped the process to the system call), we need to clear
	 * the trap flag from the new frame. Otherwise, the new thread will
	 * receive a (likely unexpected) SIGTRAP when it executes the first
	 * instruction after returning to userland.
	 */
	td->td_frame->tf_eflags &= ~PSL_T;

	/*
	 * Set registers for trampoline to user mode.  Leave space for the
	 * return address on stack.  These are the kernel mode register values.
	 */
	pcb2->pcb_edi = 0;
	pcb2->pcb_esi = (int)fork_return;		    /* trampoline arg */
	pcb2->pcb_ebp = 0;
	pcb2->pcb_esp = (int)td->td_frame - sizeof(void *); /* trampoline arg */
	pcb2->pcb_ebx = (int)td;			    /* trampoline arg */
	pcb2->pcb_eip = (int)fork_trampoline + setidt_disp;
	pcb2->pcb_gs = rgs();
	/*
	 * If we didn't copy the pcb, we'd need to do the following registers:
	 * pcb2->pcb_cr3:	cloned above.
	 * pcb2->pcb_dr*:	cloned above.
	 * pcb2->pcb_savefpu:	cloned above.
	 * pcb2->pcb_flags:	cloned above.
	 * pcb2->pcb_onfault:	cloned above (always NULL here?).
	 * pcb2->pcb_gs:	cloned above.
	 * pcb2->pcb_ext:	cleared below.
	 */
	pcb2->pcb_ext = NULL;

	/* Setup to release spin count in fork_exit(). */
	td->td_md.md_spinlock_count = 1;
	td->td_md.md_saved_flags = PSL_KERNEL | PSL_I;
}