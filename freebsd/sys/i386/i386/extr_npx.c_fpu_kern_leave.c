#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct thread {struct pcb* td_pcb; } ;
struct pcb {scalar_t__ pcb_save; int pcb_flags; } ;
struct fpu_kern_ctx {int flags; scalar_t__ prev; } ;

/* Variables and functions */
 int FPU_KERN_CTX_DUMMY ; 
 int FPU_KERN_CTX_INUSE ; 
 int FPU_KERN_CTX_NPXINITDONE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PCB_KERNNPX ; 
 int PCB_NPXINITDONE ; 
 int PCB_NPXUSERINITDONE ; 
 int /*<<< orphan*/  PCB_USER_FPU (struct pcb*) ; 
 scalar_t__ PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 scalar_t__ curthread ; 
 int /*<<< orphan*/  fpcurthread ; 
 scalar_t__ get_pcb_user_save_pcb (struct pcb*) ; 
 scalar_t__ is_fpu_kern_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  npxdrop () ; 

int
fpu_kern_leave(struct thread *td, struct fpu_kern_ctx *ctx)
{
	struct pcb *pcb;

	KASSERT((ctx->flags & FPU_KERN_CTX_INUSE) != 0,
	    ("leaving not inuse ctx"));
	ctx->flags &= ~FPU_KERN_CTX_INUSE;

	if (is_fpu_kern_thread(0) && (ctx->flags & FPU_KERN_CTX_DUMMY) != 0)
		return (0);
	pcb = td->td_pcb;
	critical_enter();
	if (curthread == PCPU_GET(fpcurthread))
		npxdrop();
	pcb->pcb_save = ctx->prev;
	if (pcb->pcb_save == get_pcb_user_save_pcb(pcb)) {
		if ((pcb->pcb_flags & PCB_NPXUSERINITDONE) != 0)
			pcb->pcb_flags |= PCB_NPXINITDONE;
		else
			pcb->pcb_flags &= ~PCB_NPXINITDONE;
		pcb->pcb_flags &= ~PCB_KERNNPX;
	} else {
		if ((ctx->flags & FPU_KERN_CTX_NPXINITDONE) != 0)
			pcb->pcb_flags |= PCB_NPXINITDONE;
		else
			pcb->pcb_flags &= ~PCB_NPXINITDONE;
		KASSERT(!PCB_USER_FPU(pcb), ("unpaired fpu_kern_leave"));
	}
	critical_exit();
	return (0);
}