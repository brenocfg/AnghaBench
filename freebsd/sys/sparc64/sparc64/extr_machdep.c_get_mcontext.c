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
struct pcb {int pcb_flags; int /*<<< orphan*/  pcb_ufp; } ;
struct TYPE_3__ {int _mc_fprs; int /*<<< orphan*/  mc_fp; int /*<<< orphan*/  _mc_y; int /*<<< orphan*/  _mc_tstate; int /*<<< orphan*/  _mc_tpc; int /*<<< orphan*/  _mc_tnpc; int /*<<< orphan*/  _mc_gsr; int /*<<< orphan*/  _mc_fsr; int /*<<< orphan*/ * mc_out; int /*<<< orphan*/ * mc_global; int /*<<< orphan*/  _mc_flags; } ;
typedef  TYPE_1__ mcontext_t ;

/* Variables and functions */
 int FPRS_FEF ; 
 int GET_MC_CLEAR_RET ; 
 int PCB_FEF ; 
 int /*<<< orphan*/  _MC_VERSION ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 int /*<<< orphan*/  savefpctx (int /*<<< orphan*/ ) ; 

int
get_mcontext(struct thread *td, mcontext_t *mc, int flags)
{
	struct trapframe *tf;
	struct pcb *pcb;

	tf = td->td_frame;
	pcb = td->td_pcb;
	/*
	 * Copy the registers which will be restored by tl0_ret() from the
	 * trapframe.
	 * Note that we skip %g7 which is used as the userland TLS register
	 * and %wstate.
	 */
	mc->_mc_flags = _MC_VERSION;
	mc->mc_global[1] = tf->tf_global[1];
	mc->mc_global[2] = tf->tf_global[2];
	mc->mc_global[3] = tf->tf_global[3];
	mc->mc_global[4] = tf->tf_global[4];
	mc->mc_global[5] = tf->tf_global[5];
	mc->mc_global[6] = tf->tf_global[6];
	if (flags & GET_MC_CLEAR_RET) {
		mc->mc_out[0] = 0;
		mc->mc_out[1] = 0;
	} else {
		mc->mc_out[0] = tf->tf_out[0];
		mc->mc_out[1] = tf->tf_out[1];
	}
	mc->mc_out[2] = tf->tf_out[2];
	mc->mc_out[3] = tf->tf_out[3];
	mc->mc_out[4] = tf->tf_out[4];
	mc->mc_out[5] = tf->tf_out[5];
	mc->mc_out[6] = tf->tf_out[6];
	mc->mc_out[7] = tf->tf_out[7];
	mc->_mc_fprs = tf->tf_fprs;
	mc->_mc_fsr = tf->tf_fsr;
	mc->_mc_gsr = tf->tf_gsr;
	mc->_mc_tnpc = tf->tf_tnpc;
	mc->_mc_tpc = tf->tf_tpc;
	mc->_mc_tstate = tf->tf_tstate;
	mc->_mc_y = tf->tf_y;
	critical_enter();
	if ((tf->tf_fprs & FPRS_FEF) != 0) {
		savefpctx(pcb->pcb_ufp);
		tf->tf_fprs &= ~FPRS_FEF;
		pcb->pcb_flags |= PCB_FEF;
	}
	if ((pcb->pcb_flags & PCB_FEF) != 0) {
		bcopy(pcb->pcb_ufp, mc->mc_fp, sizeof(mc->mc_fp));
		mc->_mc_fprs |= FPRS_FEF;
	}
	critical_exit();
	return (0);
}