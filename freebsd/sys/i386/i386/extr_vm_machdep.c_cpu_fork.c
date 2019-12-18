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
struct trapframe {int tf_edx; int pcb_esi; int pcb_esp; int pcb_ebx; struct proc_ldt* md_ldt; scalar_t__ pcb_ext; scalar_t__ pcb_eip; scalar_t__ pcb_ebp; scalar_t__ pcb_edi; int /*<<< orphan*/  pcb_cr3; int /*<<< orphan*/  tf_eflags; scalar_t__ tf_eax; struct trapframe* pcb_save; int /*<<< orphan*/  pcb_gs; } ;
struct TYPE_2__ {int md_spinlock_count; int md_saved_flags; } ;
struct thread {TYPE_1__ td_md; struct trapframe* td_frame; struct trapframe* td_pcb; struct proc* td_proc; } ;
struct proc_ldt {int ldt_refcnt; int /*<<< orphan*/  ldt_len; } ;
struct proc {int p_pfsflags; int /*<<< orphan*/  p_vmspace; struct trapframe p_md; } ;
struct pcb {int tf_edx; int pcb_esi; int pcb_esp; int pcb_ebx; struct proc_ldt* md_ldt; scalar_t__ pcb_ext; scalar_t__ pcb_eip; scalar_t__ pcb_ebp; scalar_t__ pcb_edi; int /*<<< orphan*/  pcb_cr3; int /*<<< orphan*/  tf_eflags; scalar_t__ tf_eax; struct pcb* pcb_save; int /*<<< orphan*/  pcb_gs; } ;
struct mdproc {int tf_edx; int pcb_esi; int pcb_esp; int pcb_ebx; struct proc_ldt* md_ldt; scalar_t__ pcb_ext; scalar_t__ pcb_eip; scalar_t__ pcb_ebp; scalar_t__ pcb_edi; int /*<<< orphan*/  pcb_cr3; int /*<<< orphan*/  tf_eflags; scalar_t__ tf_eax; struct mdproc* pcb_save; int /*<<< orphan*/  pcb_gs; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 struct thread* PCPU_GET (int /*<<< orphan*/ ) ; 
 int PF_FORK ; 
 int /*<<< orphan*/  PSL_C ; 
 int PSL_I ; 
 int PSL_KERNEL ; 
 int /*<<< orphan*/  PSL_T ; 
 int RFMEM ; 
 int RFPROC ; 
 scalar_t__ VM86_STACK_SPACE ; 
 int /*<<< orphan*/  bcopy (struct trapframe*,struct trapframe*,int) ; 
 int cpu_max_ext_state_size ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  dt_lock ; 
 scalar_t__ fork_return ; 
 scalar_t__ fork_trampoline ; 
 int /*<<< orphan*/  fpcurthread ; 
 struct trapframe* get_pcb_td (struct thread*) ; 
 struct trapframe* get_pcb_user_save_pcb (struct trapframe*) ; 
 struct trapframe* get_pcb_user_save_td (struct thread*) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  npxsave (struct trapframe*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pmap_get_cr3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgs () ; 
 int /*<<< orphan*/  set_user_ldt (struct trapframe*) ; 
 scalar_t__ setidt_disp ; 
 void* user_ldt_alloc (struct trapframe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user_ldt_deref (struct proc_ldt*) ; 
 int /*<<< orphan*/  vmspace_pmap (int /*<<< orphan*/ ) ; 

void
cpu_fork(struct thread *td1, struct proc *p2, struct thread *td2, int flags)
{
	struct proc *p1;
	struct pcb *pcb2;
	struct mdproc *mdp2;

	p1 = td1->td_proc;
	if ((flags & RFPROC) == 0) {
		if ((flags & RFMEM) == 0) {
			/* unshare user LDT */
			struct mdproc *mdp1 = &p1->p_md;
			struct proc_ldt *pldt, *pldt1;

			mtx_lock_spin(&dt_lock);
			if ((pldt1 = mdp1->md_ldt) != NULL &&
			    pldt1->ldt_refcnt > 1) {
				pldt = user_ldt_alloc(mdp1, pldt1->ldt_len);
				if (pldt == NULL)
					panic("could not copy LDT");
				mdp1->md_ldt = pldt;
				set_user_ldt(mdp1);
				user_ldt_deref(pldt1);
			} else
				mtx_unlock_spin(&dt_lock);
		}
		return;
	}

	/* Ensure that td1's pcb is up to date. */
	if (td1 == curthread)
		td1->td_pcb->pcb_gs = rgs();
	critical_enter();
	if (PCPU_GET(fpcurthread) == td1)
		npxsave(td1->td_pcb->pcb_save);
	critical_exit();

	/* Point the pcb to the top of the stack */
	pcb2 = get_pcb_td(td2);
	td2->td_pcb = pcb2;

	/* Copy td1's pcb */
	bcopy(td1->td_pcb, pcb2, sizeof(*pcb2));

	/* Properly initialize pcb_save */
	pcb2->pcb_save = get_pcb_user_save_pcb(pcb2);
	bcopy(get_pcb_user_save_td(td1), get_pcb_user_save_pcb(pcb2),
	    cpu_max_ext_state_size);

	/* Point mdproc and then copy over td1's contents */
	mdp2 = &p2->p_md;
	bcopy(&p1->p_md, mdp2, sizeof(*mdp2));

	/*
	 * Create a new fresh stack for the new process.
	 * Copy the trap frame for the return to user mode as if from a
	 * syscall.  This copies most of the user mode register values.
	 * The -VM86_STACK_SPACE (-16) is so we can expand the trapframe
	 * if we go to vm86.
	 */
	td2->td_frame = (struct trapframe *)((caddr_t)td2->td_pcb -
	    VM86_STACK_SPACE) - 1;
	bcopy(td1->td_frame, td2->td_frame, sizeof(struct trapframe));

	td2->td_frame->tf_eax = 0;		/* Child returns zero */
	td2->td_frame->tf_eflags &= ~PSL_C;	/* success */
	td2->td_frame->tf_edx = 1;

	/*
	 * If the parent process has the trap bit set (i.e. a debugger had
	 * single stepped the process to the system call), we need to clear
	 * the trap flag from the new frame unless the debugger had set PF_FORK
	 * on the parent.  Otherwise, the child will receive a (likely
	 * unexpected) SIGTRAP when it executes the first instruction after
	 * returning  to userland.
	 */
	if ((p1->p_pfsflags & PF_FORK) == 0)
		td2->td_frame->tf_eflags &= ~PSL_T;

	/*
	 * Set registers for trampoline to user mode.  Leave space for the
	 * return address on stack.  These are the kernel mode register values.
	 */
	pcb2->pcb_cr3 = pmap_get_cr3(vmspace_pmap(p2->p_vmspace));
	pcb2->pcb_edi = 0;
	pcb2->pcb_esi = (int)fork_return;	/* fork_trampoline argument */
	pcb2->pcb_ebp = 0;
	pcb2->pcb_esp = (int)td2->td_frame - sizeof(void *);
	pcb2->pcb_ebx = (int)td2;		/* fork_trampoline argument */
	pcb2->pcb_eip = (int)fork_trampoline + setidt_disp;
	/*-
	 * pcb2->pcb_dr*:	cloned above.
	 * pcb2->pcb_savefpu:	cloned above.
	 * pcb2->pcb_flags:	cloned above.
	 * pcb2->pcb_onfault:	cloned above (always NULL here?).
	 * pcb2->pcb_gs:	cloned above.
	 * pcb2->pcb_ext:	cleared below.
	 */

	/*
	 * XXX don't copy the i/o pages.  this should probably be fixed.
	 */
	pcb2->pcb_ext = 0;

	/* Copy the LDT, if necessary. */
	mtx_lock_spin(&dt_lock);
	if (mdp2->md_ldt != NULL) {
		if (flags & RFMEM) {
			mdp2->md_ldt->ldt_refcnt++;
		} else {
			mdp2->md_ldt = user_ldt_alloc(mdp2,
			    mdp2->md_ldt->ldt_len);
			if (mdp2->md_ldt == NULL)
				panic("could not copy LDT");
		}
	}
	mtx_unlock_spin(&dt_lock);

	/* Setup to release spin count in fork_exit(). */
	td2->td_md.md_spinlock_count = 1;
	td2->td_md.md_saved_flags = PSL_KERNEL | PSL_I;

	/*
	 * Now, cpu_switch() can schedule the new process.
	 * pcb_esp is loaded pointing to the cpu_switch() stack frame
	 * containing the return address when exiting cpu_switch.
	 * This will normally be to fork_trampoline(), which will have
	 * %ebx loaded with the new proc's pointer.  fork_trampoline()
	 * will set up a stack to call fork_return(p, frame); to complete
	 * the return to user-mode.
	 */
}