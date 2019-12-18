#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct trapframe {int srr1; void** fixreg; } ;
struct thread {int /*<<< orphan*/  td_proc; struct trapframe* td_frame; struct pcb* td_pcb; } ;
struct TYPE_7__ {struct trapframe* vr; int /*<<< orphan*/  vrsave; int /*<<< orphan*/  vscr; } ;
struct TYPE_6__ {TYPE_5__* fpr; struct trapframe fpscr; } ;
struct pcb {int pcb_flags; TYPE_2__ pcb_vec; TYPE_1__ pcb_fpu; } ;
typedef  void* register_t ;
struct TYPE_8__ {scalar_t__ mc_vers; int mc_len; int mc_srr1; int mc_flags; int /*<<< orphan*/ * mc_avec; int /*<<< orphan*/  mc_vrsave; int /*<<< orphan*/  mc_vscr; int /*<<< orphan*/ * mc_vsxfpreg; int /*<<< orphan*/ * mc_fpreg; int /*<<< orphan*/  mc_fpscr; int /*<<< orphan*/ * mc_frame; } ;
typedef  TYPE_3__ mcontext_t ;
struct TYPE_9__ {struct trapframe* vsr; struct trapframe fpr; } ;

/* Variables and functions */
 int EINVAL ; 
 int PCB_FPREGS ; 
 int PCB_FPU ; 
 int PCB_VEC ; 
 int PSL_FP ; 
 int /*<<< orphan*/  SV_LP64 ; 
 scalar_t__ SV_PROC_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _MC_AV_VALID ; 
 int _MC_FP_VALID ; 
 scalar_t__ _MC_VERSION ; 
 int /*<<< orphan*/  bzero (TYPE_5__*,int) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 int /*<<< orphan*/  enable_vec (struct thread*) ; 
 int /*<<< orphan*/  memcpy (struct trapframe*,int /*<<< orphan*/ *,int) ; 
 int psl_userstatic ; 

int
set_mcontext(struct thread *td, mcontext_t *mcp)
{
	struct pcb *pcb;
	struct trapframe *tf;
	register_t tls;
	int i;

	pcb = td->td_pcb;
	tf = td->td_frame;

	if (mcp->mc_vers != _MC_VERSION || mcp->mc_len != sizeof(*mcp))
		return (EINVAL);

	/*
	 * Don't let the user set privileged MSR bits
	 */
	if ((mcp->mc_srr1 & psl_userstatic) != (tf->srr1 & psl_userstatic)) {
		return (EINVAL);
	}

	/* Copy trapframe, preserving TLS pointer across context change */
	if (SV_PROC_FLAG(td->td_proc, SV_LP64))
		tls = tf->fixreg[13];
	else
		tls = tf->fixreg[2];
	memcpy(tf, mcp->mc_frame, sizeof(mcp->mc_frame));
	if (SV_PROC_FLAG(td->td_proc, SV_LP64))
		tf->fixreg[13] = tls;
	else
		tf->fixreg[2] = tls;

	/* Disable FPU */
	tf->srr1 &= ~PSL_FP;
	pcb->pcb_flags &= ~PCB_FPU;

	if (mcp->mc_flags & _MC_FP_VALID) {
		/* enable_fpu() will happen lazily on a fault */
		pcb->pcb_flags |= PCB_FPREGS;
		memcpy(&pcb->pcb_fpu.fpscr, &mcp->mc_fpscr, sizeof(double));
		bzero(pcb->pcb_fpu.fpr, sizeof(pcb->pcb_fpu.fpr));
		for (i = 0; i < 32; i++) {
			memcpy(&pcb->pcb_fpu.fpr[i].fpr, &mcp->mc_fpreg[i],
			    sizeof(double));
			memcpy(&pcb->pcb_fpu.fpr[i].vsr[2],
			    &mcp->mc_vsxfpreg[i], sizeof(double));
		}
	}

	if (mcp->mc_flags & _MC_AV_VALID) {
		if ((pcb->pcb_flags & PCB_VEC) != PCB_VEC) {
			critical_enter();
			enable_vec(td);
			critical_exit();
		}
		pcb->pcb_vec.vscr = mcp->mc_vscr;
		pcb->pcb_vec.vrsave = mcp->mc_vrsave;
		memcpy(pcb->pcb_vec.vr, mcp->mc_avec, sizeof(mcp->mc_avec));
	}

	return (0);
}