#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct trapframe {int dummy; } ;
struct TYPE_7__ {int md_spinlock_count; int /*<<< orphan*/  md_saved_cspr; } ;
struct thread {TYPE_2__ td_md; TYPE_3__* td_frame; TYPE_3__* td_pcb; } ;
struct pcb {int dummy; } ;
typedef  void* register_t ;
struct TYPE_6__ {int /*<<< orphan*/  sf_sp; void* sf_lr; void* sf_r5; void* sf_r4; } ;
struct TYPE_8__ {scalar_t__ tf_r0; int /*<<< orphan*/  tf_spsr; TYPE_1__ pcb_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSR_C ; 
 int /*<<< orphan*/  PSR_SVC32_MODE ; 
 int /*<<< orphan*/  STACKALIGN (TYPE_3__*) ; 
 int /*<<< orphan*/  bcopy (TYPE_3__*,TYPE_3__*,int) ; 
 scalar_t__ fork_return ; 
 scalar_t__ fork_trampoline ; 

void
cpu_copy_thread(struct thread *td, struct thread *td0)
{

	bcopy(td0->td_frame, td->td_frame, sizeof(struct trapframe));
	bcopy(td0->td_pcb, td->td_pcb, sizeof(struct pcb));

	td->td_pcb->pcb_regs.sf_r4 = (register_t)fork_return;
	td->td_pcb->pcb_regs.sf_r5 = (register_t)td;
	td->td_pcb->pcb_regs.sf_lr = (register_t)fork_trampoline;
	td->td_pcb->pcb_regs.sf_sp = STACKALIGN(td->td_frame);

	td->td_frame->tf_spsr &= ~PSR_C;
	td->td_frame->tf_r0 = 0;

	/* Setup to release spin count in fork_exit(). */
	td->td_md.md_spinlock_count = 1;
	td->td_md.md_saved_cspr = PSR_SVC32_MODE;
}