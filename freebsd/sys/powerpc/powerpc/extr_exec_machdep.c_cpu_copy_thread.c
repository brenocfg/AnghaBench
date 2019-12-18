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
struct TYPE_7__ {int vscr; } ;
struct TYPE_5__ {scalar_t__ usr_vsid; } ;
struct TYPE_6__ {TYPE_1__ aim; } ;
struct trapframe {int cr; TYPE_3__ pcb_vec; TYPE_2__ pcb_cpu; void* pcb_lr; void** pcb_context; void* pcb_toc; void* pcb_sp; scalar_t__* fixreg; } ;
struct TYPE_8__ {int md_spinlock_count; int /*<<< orphan*/  md_saved_msr; } ;
struct thread {TYPE_4__ td_md; struct trapframe* td_frame; struct trapframe* td_pcb; } ;
struct pcb {int cr; TYPE_3__ pcb_vec; TYPE_2__ pcb_cpu; void* pcb_lr; void** pcb_context; void* pcb_toc; void* pcb_sp; scalar_t__* fixreg; } ;
struct callframe {void* cf_arg1; void* cf_arg0; void* cf_func; } ;
typedef  void* register_t ;

/* Variables and functions */
 size_t FIRSTARG ; 
 int SPEFSCR_FDBZE ; 
 int SPEFSCR_FINVE ; 
 int SPEFSCR_FOVFE ; 
 int SPEFSCR_FUNFE ; 
 int /*<<< orphan*/  bcopy (struct trapframe*,struct trapframe*,int) ; 
 scalar_t__ fork_return ; 
 scalar_t__ fork_trampoline ; 
 int /*<<< orphan*/  memset (struct callframe*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  psl_kernset ; 

void
cpu_copy_thread(struct thread *td, struct thread *td0)
{
	struct pcb *pcb2;
	struct trapframe *tf;
	struct callframe *cf;

	pcb2 = td->td_pcb;

	/* Copy the upcall pcb */
	bcopy(td0->td_pcb, pcb2, sizeof(*pcb2));

	/* Create a stack for the new thread */
	tf = td->td_frame;
	bcopy(td0->td_frame, tf, sizeof(struct trapframe));
	tf->fixreg[FIRSTARG] = 0;
	tf->fixreg[FIRSTARG + 1] = 0;
	tf->cr &= ~0x10000000;

	/* Set registers for trampoline to user mode. */
	cf = (struct callframe *)tf - 1;
	memset(cf, 0, sizeof(struct callframe));
	cf->cf_func = (register_t)fork_return;
	cf->cf_arg0 = (register_t)td;
	cf->cf_arg1 = (register_t)tf;

	pcb2->pcb_sp = (register_t)cf;
	#if defined(__powerpc64__) && (!defined(_CALL_ELF) || _CALL_ELF == 1)
	pcb2->pcb_lr = ((register_t *)fork_trampoline)[0];
	pcb2->pcb_toc = ((register_t *)fork_trampoline)[1];
	#else
	pcb2->pcb_lr = (register_t)fork_trampoline;
	pcb2->pcb_context[0] = pcb2->pcb_lr;
	#endif
	pcb2->pcb_cpu.aim.usr_vsid = 0;
#ifdef __SPE__
	pcb2->pcb_vec.vscr = SPEFSCR_FINVE | SPEFSCR_FDBZE |
	    SPEFSCR_FUNFE | SPEFSCR_FOVFE;
#endif

	/* Setup to release spin count in fork_exit(). */
	td->td_md.md_spinlock_count = 1;
	td->td_md.md_saved_msr = psl_kernset;
}