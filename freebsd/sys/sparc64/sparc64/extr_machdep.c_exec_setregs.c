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
typedef  void* u_long ;
struct trapframe {int tf_tstate; scalar_t__ tf_tpc; scalar_t__ tf_tnpc; void** tf_out; } ;
struct thread {struct trapframe* td_frame; struct trapframe* td_pcb; struct proc* td_proc; } ;
struct TYPE_3__ {int /*<<< orphan*/ * md_utrap; int /*<<< orphan*/ * md_sigtramp; } ;
struct proc {TYPE_2__* p_sysent; TYPE_1__ p_md; } ;
struct pcb {int tf_tstate; scalar_t__ tf_tpc; scalar_t__ tf_tnpc; void** tf_out; } ;
struct image_params {scalar_t__ entry_addr; } ;
struct frame {int dummy; } ;
struct TYPE_4__ {void* sv_psstrings; } ;

/* Variables and functions */
 void* SPOFF ; 
 int TSTATE_IE ; 
 int TSTATE_MM_TSO ; 
 int TSTATE_PEF ; 
 int /*<<< orphan*/  bzero (struct trapframe*,int) ; 
 void* rounddown (void*,int) ; 
 int /*<<< orphan*/  utrap_free (int /*<<< orphan*/ *) ; 

void
exec_setregs(struct thread *td, struct image_params *imgp, u_long stack)
{
	struct trapframe *tf;
	struct pcb *pcb;
	struct proc *p;
	u_long sp;

	/* XXX no cpu_exec */
	p = td->td_proc;
	p->p_md.md_sigtramp = NULL;
	if (p->p_md.md_utrap != NULL) {
		utrap_free(p->p_md.md_utrap);
		p->p_md.md_utrap = NULL;
	}

	pcb = td->td_pcb;
	tf = td->td_frame;
	sp = rounddown(stack, 16);
	bzero(pcb, sizeof(*pcb));
	bzero(tf, sizeof(*tf));
	tf->tf_out[0] = stack;
	tf->tf_out[3] = p->p_sysent->sv_psstrings;
	tf->tf_out[6] = sp - SPOFF - sizeof(struct frame);
	tf->tf_tnpc = imgp->entry_addr + 4;
	tf->tf_tpc = imgp->entry_addr;
	/*
	 * While we could adhere to the memory model indicated in the ELF
	 * header, it turns out that just always using TSO performs best.
	 */
	tf->tf_tstate = TSTATE_IE | TSTATE_PEF | TSTATE_MM_TSO;
}