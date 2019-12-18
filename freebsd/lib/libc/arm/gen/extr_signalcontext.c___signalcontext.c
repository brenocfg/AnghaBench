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
struct TYPE_6__ {scalar_t__* __gregs; } ;
struct TYPE_8__ {int /*<<< orphan*/  uc_sigmask; int /*<<< orphan*/ * uc_link; TYPE_1__ uc_mcontext; } ;
typedef  TYPE_3__ ucontext_t ;
struct TYPE_7__ {int si_signo; } ;
struct sigframe {int /*<<< orphan*/  sf_uc; TYPE_2__ sf_si; } ;
typedef  int /*<<< orphan*/  __sighandler_t ;
typedef  scalar_t__ __greg_t ;

/* Variables and functions */
 size_t _REG_FP ; 
 size_t _REG_PC ; 
 size_t _REG_R0 ; 
 size_t _REG_R1 ; 
 size_t _REG_R2 ; 
 size_t _REG_R4 ; 
 size_t _REG_R5 ; 
 size_t _REG_SP ; 
 scalar_t__ _ctx_start ; 
 int /*<<< orphan*/  bcopy (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bzero (struct sigframe*,int) ; 
 int /*<<< orphan*/  sigdelset (int /*<<< orphan*/ *,int) ; 

int
__signalcontext(ucontext_t *ucp, int sig, __sighandler_t *func)
{
	struct sigframe *sfp;
	__greg_t *gr = ucp->uc_mcontext.__gregs;
	unsigned int *sp;

	sp = (unsigned int *)gr[_REG_SP];

	sfp = (struct sigframe *)sp - 1;
	
	bzero(sfp, sizeof(*sfp));
	bcopy(ucp, &sfp->sf_uc, sizeof(*ucp));
	sfp->sf_si.si_signo = sig;

	gr[_REG_SP] = (__greg_t)sfp;
	/* Wipe out frame pointer. */
	gr[_REG_FP] = 0;
	/* Arrange for return via the trampoline code. */
	gr[_REG_PC] = (__greg_t)_ctx_start;
	gr[_REG_R4] = (__greg_t)func;
	gr[_REG_R5] = (__greg_t)ucp;
	gr[_REG_R0] = (__greg_t)sig;
	gr[_REG_R1] = (__greg_t)&sfp->sf_si;
	gr[_REG_R2] = (__greg_t)&sfp->sf_uc;

	ucp->uc_link = &sfp->sf_uc;
	sigdelset(&ucp->uc_sigmask, sig);

	return (0);
}