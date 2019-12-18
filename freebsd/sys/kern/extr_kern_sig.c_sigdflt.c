#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sigacts {int /*<<< orphan*/  ps_siginfo; int /*<<< orphan*/ * ps_sigact; int /*<<< orphan*/  ps_sigignore; int /*<<< orphan*/  ps_sigcatch; int /*<<< orphan*/  ps_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  SIGADDSET (int /*<<< orphan*/ ,int) ; 
 int SIGCONT ; 
 int /*<<< orphan*/  SIGDELSET (int /*<<< orphan*/ ,int) ; 
 int SIGPROP_IGNORE ; 
 int /*<<< orphan*/  SIG_DFL ; 
 size_t _SIG_IDX (int) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sigprop (int) ; 

__attribute__((used)) static void
sigdflt(struct sigacts *ps, int sig)
{

	mtx_assert(&ps->ps_mtx, MA_OWNED);
	SIGDELSET(ps->ps_sigcatch, sig);
	if ((sigprop(sig) & SIGPROP_IGNORE) != 0 && sig != SIGCONT)
		SIGADDSET(ps->ps_sigignore, sig);
	ps->ps_sigact[_SIG_IDX(sig)] = SIG_DFL;
	SIGDELSET(ps->ps_siginfo, sig);
}