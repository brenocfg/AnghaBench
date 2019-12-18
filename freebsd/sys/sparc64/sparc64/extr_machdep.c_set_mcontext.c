#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct trapframe {int tf_fprs; int /*<<< orphan*/  tf_y; int /*<<< orphan*/  tf_tstate; int /*<<< orphan*/  tf_tpc; int /*<<< orphan*/  tf_tnpc; int /*<<< orphan*/  tf_gsr; int /*<<< orphan*/  tf_fsr; int /*<<< orphan*/ * tf_out; int /*<<< orphan*/ * tf_global; } ;
struct thread {struct pcb* td_pcb; struct trapframe* td_frame; } ;
struct pcb {int /*<<< orphan*/  pcb_flags; int /*<<< orphan*/  pcb_ufp; } ;
struct TYPE_3__ {long _mc_flags; int _mc_fprs; int /*<<< orphan*/  mc_fp; int /*<<< orphan*/  _mc_y; int /*<<< orphan*/  _mc_tstate; int /*<<< orphan*/  _mc_tpc; int /*<<< orphan*/  _mc_tnpc; int /*<<< orphan*/  _mc_gsr; int /*<<< orphan*/  _mc_fsr; int /*<<< orphan*/ * mc_out; int /*<<< orphan*/ * mc_global; } ;
typedef  TYPE_1__ mcontext_t ;

/* Variables and functions */
 int EINVAL ; 
 int FPRS_FEF ; 
 int /*<<< orphan*/  PCB_FEF ; 
 int /*<<< orphan*/  TSTATE_SECURE (int /*<<< orphan*/ ) ; 
 long _MC_VERSION ; 
 long _MC_VERSION_BITS ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  flushw () ; 

int
set_mcontext(struct thread *td, mcontext_t *mc)
{
	struct trapframe *tf;
	struct pcb *pcb;

	if (!TSTATE_SECURE(mc->_mc_tstate) ||
	    (mc->_mc_flags & ((1L << _MC_VERSION_BITS) - 1)) != _MC_VERSION)
		return (EINVAL);
	tf = td->td_frame;
	pcb = td->td_pcb;
	/* Make sure the windows are spilled first. */
	flushw();
	/*
	 * Copy the registers which will be restored by tl0_ret() to the
	 * trapframe.
	 * Note that we skip %g7 which is used as the userland TLS register
	 * and %wstate.
	 */
	tf->tf_global[1] = mc->mc_global[1];
	tf->tf_global[2] = mc->mc_global[2];
	tf->tf_global[3] = mc->mc_global[3];
	tf->tf_global[4] = mc->mc_global[4];
	tf->tf_global[5] = mc->mc_global[5];
	tf->tf_global[6] = mc->mc_global[6];
	tf->tf_out[0] = mc->mc_out[0];
	tf->tf_out[1] = mc->mc_out[1];
	tf->tf_out[2] = mc->mc_out[2];
	tf->tf_out[3] = mc->mc_out[3];
	tf->tf_out[4] = mc->mc_out[4];
	tf->tf_out[5] = mc->mc_out[5];
	tf->tf_out[6] = mc->mc_out[6];
	tf->tf_out[7] = mc->mc_out[7];
	tf->tf_fprs = mc->_mc_fprs;
	tf->tf_fsr = mc->_mc_fsr;
	tf->tf_gsr = mc->_mc_gsr;
	tf->tf_tnpc = mc->_mc_tnpc;
	tf->tf_tpc = mc->_mc_tpc;
	tf->tf_tstate = mc->_mc_tstate;
	tf->tf_y = mc->_mc_y;
	if ((mc->_mc_fprs & FPRS_FEF) != 0) {
		tf->tf_fprs = 0;
		bcopy(mc->mc_fp, pcb->pcb_ufp, sizeof(pcb->pcb_ufp));
		pcb->pcb_flags |= PCB_FEF;
	}
	return (0);
}