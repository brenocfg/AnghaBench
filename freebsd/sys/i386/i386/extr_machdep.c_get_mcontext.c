#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct trapframe {int /*<<< orphan*/  tf_ss; int /*<<< orphan*/  tf_esp; int /*<<< orphan*/  tf_cs; int /*<<< orphan*/  tf_eip; int /*<<< orphan*/  tf_ecx; int /*<<< orphan*/  tf_ebx; int /*<<< orphan*/  tf_edx; int /*<<< orphan*/  tf_eax; int /*<<< orphan*/  tf_eflags; int /*<<< orphan*/  tf_isp; int /*<<< orphan*/  tf_ebp; int /*<<< orphan*/  tf_esi; int /*<<< orphan*/  tf_edi; int /*<<< orphan*/  tf_ds; int /*<<< orphan*/  tf_es; int /*<<< orphan*/  tf_fs; } ;
struct thread {TYPE_1__* td_pcb; struct trapframe* td_frame; } ;
struct segment_descriptor {int sd_hibase; int sd_lobase; } ;
struct TYPE_7__ {int mc_len; int mc_fsbase; int mc_gsbase; int /*<<< orphan*/  mc_spare2; scalar_t__ mc_xfpustate_len; scalar_t__ mc_xfpustate; scalar_t__ mc_flags; int /*<<< orphan*/  mc_ss; int /*<<< orphan*/  mc_esp; int /*<<< orphan*/  mc_cs; int /*<<< orphan*/  mc_eip; int /*<<< orphan*/  mc_ecx; int /*<<< orphan*/  mc_ebx; int /*<<< orphan*/  mc_edx; int /*<<< orphan*/  mc_eax; int /*<<< orphan*/  mc_eflags; int /*<<< orphan*/  mc_isp; int /*<<< orphan*/  mc_ebp; int /*<<< orphan*/  mc_esi; int /*<<< orphan*/  mc_edi; int /*<<< orphan*/  mc_ds; int /*<<< orphan*/  mc_es; int /*<<< orphan*/  mc_fs; int /*<<< orphan*/  mc_gs; int /*<<< orphan*/  mc_onstack; } ;
typedef  TYPE_2__ mcontext_t ;
struct TYPE_8__ {int /*<<< orphan*/  td_proc; } ;
struct TYPE_6__ {struct segment_descriptor pcb_gsd; struct segment_descriptor pcb_fsd; int /*<<< orphan*/  pcb_gs; } ;

/* Variables and functions */
 int GET_MC_CLEAR_RET ; 
 int /*<<< orphan*/  PROC_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSL_C ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 TYPE_5__* curthread ; 
 int /*<<< orphan*/  get_fpcontext (struct thread*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigonstack (int /*<<< orphan*/ ) ; 

int
get_mcontext(struct thread *td, mcontext_t *mcp, int flags)
{
	struct trapframe *tp;
	struct segment_descriptor *sdp;

	tp = td->td_frame;

	PROC_LOCK(curthread->td_proc);
	mcp->mc_onstack = sigonstack(tp->tf_esp);
	PROC_UNLOCK(curthread->td_proc);
	mcp->mc_gs = td->td_pcb->pcb_gs;
	mcp->mc_fs = tp->tf_fs;
	mcp->mc_es = tp->tf_es;
	mcp->mc_ds = tp->tf_ds;
	mcp->mc_edi = tp->tf_edi;
	mcp->mc_esi = tp->tf_esi;
	mcp->mc_ebp = tp->tf_ebp;
	mcp->mc_isp = tp->tf_isp;
	mcp->mc_eflags = tp->tf_eflags;
	if (flags & GET_MC_CLEAR_RET) {
		mcp->mc_eax = 0;
		mcp->mc_edx = 0;
		mcp->mc_eflags &= ~PSL_C;
	} else {
		mcp->mc_eax = tp->tf_eax;
		mcp->mc_edx = tp->tf_edx;
	}
	mcp->mc_ebx = tp->tf_ebx;
	mcp->mc_ecx = tp->tf_ecx;
	mcp->mc_eip = tp->tf_eip;
	mcp->mc_cs = tp->tf_cs;
	mcp->mc_esp = tp->tf_esp;
	mcp->mc_ss = tp->tf_ss;
	mcp->mc_len = sizeof(*mcp);
	get_fpcontext(td, mcp, NULL, 0);
	sdp = &td->td_pcb->pcb_fsd;
	mcp->mc_fsbase = sdp->sd_hibase << 24 | sdp->sd_lobase;
	sdp = &td->td_pcb->pcb_gsd;
	mcp->mc_gsbase = sdp->sd_hibase << 24 | sdp->sd_lobase;
	mcp->mc_flags = 0;
	mcp->mc_xfpustate = 0;
	mcp->mc_xfpustate_len = 0;
	bzero(mcp->mc_spare2, sizeof(mcp->mc_spare2));
	return (0);
}