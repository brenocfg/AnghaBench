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
typedef  int uint32_t ;
struct TYPE_8__ {unsigned long* mc_gpr; int si_signo; int mc_len; int mc_srr0; int /*<<< orphan*/  mc_vers; } ;
struct TYPE_7__ {TYPE_2__ uc_mcontext; int /*<<< orphan*/  uc_sigmask; struct TYPE_7__* uc_link; } ;
typedef  TYPE_1__ ucontext_t ;
struct __mcontext {int dummy; } ;
typedef  TYPE_2__ siginfo_t ;
typedef  int /*<<< orphan*/  __sighandler_t ;

/* Variables and functions */
 int /*<<< orphan*/  _MC_VERSION ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  bcopy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 scalar_t__ ctx_wrapper ; 
 int /*<<< orphan*/  sigdelset (int /*<<< orphan*/ *,int) ; 

int
__signalcontext(ucontext_t *ucp, int sig, __sighandler_t *func)
{
	siginfo_t *sig_si;
	ucontext_t *sig_uc;
	uint32_t sp;

	/* Bail out if we don't have a valid ucontext pointer. */
	if (ucp == NULL)
		abort();

	/*
	 * Build a 16-byte-aligned signal frame
	 */
	sp = (ucp->uc_mcontext.mc_gpr[1] - sizeof(ucontext_t)) & ~15UL;
	sig_uc = (ucontext_t *)sp;
	bcopy(ucp, sig_uc, sizeof(*sig_uc));
	sp = (sp - sizeof(siginfo_t)) & ~15UL;
	sig_si = (siginfo_t *)sp;
	bzero(sig_si, sizeof(*sig_si));
	sig_si->si_signo = sig;

	/*
	 * Subtract 8 bytes from stack to allow for frameptr
	 */
	sp -= 2*sizeof(uint32_t);
	sp &= ~15UL;

	/*
	 * Setup the ucontext of the signal handler.
	 */
	bzero(&ucp->uc_mcontext, sizeof(ucp->uc_mcontext));
	ucp->uc_link = sig_uc;
	sigdelset(&ucp->uc_sigmask, sig);

	ucp->uc_mcontext.mc_vers = _MC_VERSION;
	ucp->uc_mcontext.mc_len = sizeof(struct __mcontext);
	ucp->uc_mcontext.mc_srr0 = (uint32_t) ctx_wrapper;
	ucp->uc_mcontext.mc_gpr[1] = (uint32_t) sp;
	ucp->uc_mcontext.mc_gpr[3] = (uint32_t) func;
	ucp->uc_mcontext.mc_gpr[4] = (uint32_t) sig;
	ucp->uc_mcontext.mc_gpr[5] = (uint32_t) sig_si;
	ucp->uc_mcontext.mc_gpr[6] = (uint32_t) sig_uc;

	return (0);
}