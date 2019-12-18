#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  _mc_tstate; int /*<<< orphan*/  _mc_sp; int /*<<< orphan*/  _mc_tpc; } ;
struct TYPE_5__ {int /*<<< orphan*/  uc_sigmask; TYPE_2__ uc_mcontext; } ;
typedef  TYPE_1__ ucontext_t ;
typedef  int /*<<< orphan*/  uc ;
struct thread {struct proc* td_proc; } ;
struct sigreturn_args {int /*<<< orphan*/  sigcntxp; } ;
struct proc {int dummy; } ;
typedef  TYPE_2__ mcontext_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTR1 (int /*<<< orphan*/ ,char*,struct thread*) ; 
 int /*<<< orphan*/  CTR2 (int /*<<< orphan*/ ,char*,struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTR4 (int /*<<< orphan*/ ,char*,struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EFAULT ; 
 int EJUSTRETURN ; 
 int /*<<< orphan*/  KTR_SIG ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  SIGILL ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 scalar_t__ copyin (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  kern_sigprocmask (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ rwindow_save (struct thread*) ; 
 int set_mcontext (struct thread*,TYPE_2__*) ; 
 int /*<<< orphan*/  sigexit (struct thread*,int /*<<< orphan*/ ) ; 

int
sys_sigreturn(struct thread *td, struct sigreturn_args *uap)
{
	struct proc *p;
	mcontext_t *mc;
	ucontext_t uc;
	int error;

	p = td->td_proc;
	if (rwindow_save(td)) {
		PROC_LOCK(p);
		sigexit(td, SIGILL);
	}

	CTR2(KTR_SIG, "sigreturn: td=%p ucp=%p", td, uap->sigcntxp);
	if (copyin(uap->sigcntxp, &uc, sizeof(uc)) != 0) {
		CTR1(KTR_SIG, "sigreturn: efault td=%p", td);
		return (EFAULT);
	}

	mc = &uc.uc_mcontext;
	error = set_mcontext(td, mc);
	if (error != 0)
		return (error);

	kern_sigprocmask(td, SIG_SETMASK, &uc.uc_sigmask, NULL, 0);

	CTR4(KTR_SIG, "sigreturn: return td=%p pc=%#lx sp=%#lx tstate=%#lx",
	    td, mc->_mc_tpc, mc->_mc_sp, mc->_mc_tstate);
	return (EJUSTRETURN);
}