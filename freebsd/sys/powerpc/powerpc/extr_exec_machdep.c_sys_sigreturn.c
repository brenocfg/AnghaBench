#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * mc_gpr; int /*<<< orphan*/  mc_srr0; } ;
struct TYPE_4__ {TYPE_2__ uc_mcontext; int /*<<< orphan*/  uc_sigmask; } ;
typedef  TYPE_1__ ucontext_t ;
typedef  int /*<<< orphan*/  uc ;
struct thread {int dummy; } ;
struct sigreturn_args {int /*<<< orphan*/  sigcntxp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR1 (int /*<<< orphan*/ ,char*,struct thread*) ; 
 int /*<<< orphan*/  CTR2 (int /*<<< orphan*/ ,char*,struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTR3 (int /*<<< orphan*/ ,char*,struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EFAULT ; 
 int EJUSTRETURN ; 
 int /*<<< orphan*/  KTR_SIG ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 scalar_t__ copyin (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  kern_sigprocmask (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int set_mcontext (struct thread*,TYPE_2__*) ; 

int
sys_sigreturn(struct thread *td, struct sigreturn_args *uap)
{
	ucontext_t uc;
	int error;

	CTR2(KTR_SIG, "sigreturn: td=%p ucp=%p", td, uap->sigcntxp);

	if (copyin(uap->sigcntxp, &uc, sizeof(uc)) != 0) {
		CTR1(KTR_SIG, "sigreturn: efault td=%p", td);
		return (EFAULT);
	}

	error = set_mcontext(td, &uc.uc_mcontext);
	if (error != 0)
		return (error);

	kern_sigprocmask(td, SIG_SETMASK, &uc.uc_sigmask, NULL, 0);

	CTR3(KTR_SIG, "sigreturn: return td=%p pc=%#x sp=%#x",
	     td, uc.uc_mcontext.mc_srr0, uc.uc_mcontext.mc_gpr[1]);

	return (EJUSTRETURN);
}