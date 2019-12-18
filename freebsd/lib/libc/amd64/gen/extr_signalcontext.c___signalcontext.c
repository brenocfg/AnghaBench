#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_8__ {int mc_rsp; int si_signo; int mc_len; void* mc_rip; void* mc_rbx; void* mc_rbp; void* mc_rdx; void* mc_rsi; void* mc_rdi; int /*<<< orphan*/  mc_ownedfp; int /*<<< orphan*/  mc_fpformat; } ;
struct TYPE_7__ {TYPE_2__ uc_mcontext; int /*<<< orphan*/  uc_sigmask; struct TYPE_7__* uc_link; } ;
typedef  TYPE_1__ ucontext_t ;
typedef  TYPE_2__ siginfo_t ;
typedef  void* register_t ;
typedef  int /*<<< orphan*/  mcontext_t ;
typedef  int /*<<< orphan*/  __sighandler_t ;

/* Variables and functions */
 int /*<<< orphan*/  _MC_FPFMT_NODEV ; 
 int /*<<< orphan*/  _MC_FPOWNED_NONE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  bcopy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 scalar_t__ sigctx_wrapper ; 
 int /*<<< orphan*/  sigdelset (int /*<<< orphan*/ *,int) ; 

int
__signalcontext(ucontext_t *ucp, int sig, __sighandler_t *func)
{
	uint64_t *args;
	siginfo_t *sig_si;
	ucontext_t *sig_uc;
	uint64_t sp;

	/* Bail out if we don't have a valid ucontext pointer. */
	if (ucp == NULL)
		abort();

	/*
	 * Build a signal frame and copy the arguments of signal handler
	 * 'func' onto the stack and do the funky stack alignment.
	 * This means that we need an 8-byte-odd alignment since the ABI expects
	 * the return address to be pushed, thus breaking the 16 byte alignment.
	 */
	sp = (ucp->uc_mcontext.mc_rsp - 128 - sizeof(ucontext_t)) & ~15UL;
	sig_uc = (ucontext_t *)sp;
	bcopy(ucp, sig_uc, sizeof(*sig_uc));
	sp = (sp - sizeof(siginfo_t)) & ~15UL;
	sig_si = (siginfo_t *)sp;
	bzero(sig_si, sizeof(*sig_si));
	sig_si->si_signo = sig;
	sp -= 3 * sizeof(uint64_t);
	args = (uint64_t *)sp;
	args[0] = sig;
	args[1] = (intptr_t)sig_si;
	args[2] = (intptr_t)sig_uc;
	sp -= 16;

	/*
	 * Setup the ucontext of the signal handler.
	 */
	bzero(&ucp->uc_mcontext, sizeof(ucp->uc_mcontext));
	ucp->uc_mcontext.mc_fpformat = _MC_FPFMT_NODEV;
	ucp->uc_mcontext.mc_ownedfp = _MC_FPOWNED_NONE;
	ucp->uc_link = sig_uc;
	sigdelset(&ucp->uc_sigmask, sig);

	ucp->uc_mcontext.mc_len = sizeof(mcontext_t);
	ucp->uc_mcontext.mc_rdi = (register_t)ucp;
	ucp->uc_mcontext.mc_rsi = (register_t)func;
	ucp->uc_mcontext.mc_rdx = (register_t)args;
	ucp->uc_mcontext.mc_rbp = (register_t)sp;
	ucp->uc_mcontext.mc_rbx = (register_t)sp;
	ucp->uc_mcontext.mc_rsp = (register_t)sp;
	ucp->uc_mcontext.mc_rip = (register_t)sigctx_wrapper;
	return (0);
}