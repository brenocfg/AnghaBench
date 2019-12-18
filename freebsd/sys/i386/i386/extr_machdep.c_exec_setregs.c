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
typedef  int /*<<< orphan*/  u_long ;
struct trapframe {int tf_eflags; int /*<<< orphan*/  tf_ebx; int /*<<< orphan*/  tf_cs; void* tf_fs; void* tf_es; void* tf_ds; void* tf_ss; int /*<<< orphan*/  tf_esp; int /*<<< orphan*/  tf_eip; } ;
struct thread {TYPE_3__* td_proc; struct pcb* td_pcb; struct trapframe* td_frame; } ;
struct pcb {int pcb_flags; int /*<<< orphan*/  pcb_initial_npxcw; scalar_t__ pcb_dr7; scalar_t__ pcb_dr6; scalar_t__ pcb_dr3; scalar_t__ pcb_dr2; scalar_t__ pcb_dr1; scalar_t__ pcb_dr0; void* pcb_gs; } ;
struct image_params {int /*<<< orphan*/  ps_strings; int /*<<< orphan*/  entry_addr; } ;
typedef  int register_t ;
struct TYPE_8__ {scalar_t__ sv_psstrings; } ;
struct TYPE_5__ {int /*<<< orphan*/ * md_ldt; } ;
struct TYPE_7__ {TYPE_2__* p_sysent; TYPE_1__ p_md; } ;
struct TYPE_6__ {scalar_t__ sv_psstrings; } ;

/* Variables and functions */
 int PCB_DBREGS ; 
 int PSL_T ; 
 int PSL_USER ; 
 int /*<<< orphan*/  __INITIAL_NPXCW__ ; 
 int /*<<< orphan*/  _ucodesel ; 
 void* _udatasel ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 struct pcb* curpcb ; 
 int /*<<< orphan*/  dt_lock ; 
 TYPE_4__ elf32_freebsd_sysvec ; 
 int /*<<< orphan*/  fpstate_drop (struct thread*) ; 
 int /*<<< orphan*/  load_gs (void*) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_dbregs () ; 
 int /*<<< orphan*/  set_fsbase (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gsbase (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_priv_lcall_gate (TYPE_3__*) ; 
 int /*<<< orphan*/  user_ldt_free (struct thread*) ; 

void
exec_setregs(struct thread *td, struct image_params *imgp, u_long stack)
{
	struct trapframe *regs;
	struct pcb *pcb;
	register_t saved_eflags;

	regs = td->td_frame;
	pcb = td->td_pcb;

	/* Reset pc->pcb_gs and %gs before possibly invalidating it. */
	pcb->pcb_gs = _udatasel;
	load_gs(_udatasel);

	mtx_lock_spin(&dt_lock);
	if (td->td_proc->p_md.md_ldt != NULL)
		user_ldt_free(td);
	else
		mtx_unlock_spin(&dt_lock);

#ifdef COMPAT_43
	if (td->td_proc->p_sysent->sv_psstrings !=
	    elf32_freebsd_sysvec.sv_psstrings)
		setup_priv_lcall_gate(td->td_proc);
#endif
  
	/*
	 * Reset the fs and gs bases.  The values from the old address
	 * space do not make sense for the new program.  In particular,
	 * gsbase might be the TLS base for the old program but the new
	 * program has no TLS now.
	 */
	set_fsbase(td, 0);
	set_gsbase(td, 0);

	/* Make sure edx is 0x0 on entry. Linux binaries depend on it. */
	saved_eflags = regs->tf_eflags & PSL_T;
	bzero((char *)regs, sizeof(struct trapframe));
	regs->tf_eip = imgp->entry_addr;
	regs->tf_esp = stack;
	regs->tf_eflags = PSL_USER | saved_eflags;
	regs->tf_ss = _udatasel;
	regs->tf_ds = _udatasel;
	regs->tf_es = _udatasel;
	regs->tf_fs = _udatasel;
	regs->tf_cs = _ucodesel;

	/* PS_STRINGS value for BSD/OS binaries.  It is 0 for non-BSD/OS. */
	regs->tf_ebx = imgp->ps_strings;

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
		pcb->pcb_flags &= ~PCB_DBREGS;
        }

	pcb->pcb_initial_npxcw = __INITIAL_NPXCW__;

	/*
	 * Drop the FP state if we hold it, so that the process gets a
	 * clean FP state if it uses the FPU again.
	 */
	fpstate_drop(td);
}