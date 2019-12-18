#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ru_nsignals; } ;
struct thread {TYPE_1__ td_ru; } ;
struct sigacts {int /*<<< orphan*/  ps_sigreset; int /*<<< orphan*/  ps_signodefer; int /*<<< orphan*/ * ps_catchmask; int /*<<< orphan*/  ps_mtx; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  SIGADDSET (int /*<<< orphan*/ ,int) ; 
 scalar_t__ SIGISMEMBER (int /*<<< orphan*/ ,int) ; 
 int SIGPROCMASK_PROC_LOCKED ; 
 int SIGPROCMASK_PS_LOCKED ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 size_t _SIG_IDX (int) ; 
 int /*<<< orphan*/  kern_sigprocmask (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigdflt (struct sigacts*,int) ; 

__attribute__((used)) static void
postsig_done(int sig, struct thread *td, struct sigacts *ps)
{
	sigset_t mask;

	mtx_assert(&ps->ps_mtx, MA_OWNED);
	td->td_ru.ru_nsignals++;
	mask = ps->ps_catchmask[_SIG_IDX(sig)];
	if (!SIGISMEMBER(ps->ps_signodefer, sig))
		SIGADDSET(mask, sig);
	kern_sigprocmask(td, SIG_BLOCK, &mask, NULL,
	    SIGPROCMASK_PROC_LOCKED | SIGPROCMASK_PS_LOCKED);
	if (SIGISMEMBER(ps->ps_sigreset, sig))
		sigdflt(ps, sig);
}