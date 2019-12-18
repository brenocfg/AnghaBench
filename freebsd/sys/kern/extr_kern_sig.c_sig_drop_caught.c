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
struct sigacts {int /*<<< orphan*/  ps_sigcatch; int /*<<< orphan*/  ps_mtx; } ;
struct proc {struct sigacts* p_sigacts; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 scalar_t__ SIGNOTEMPTY (int /*<<< orphan*/ ) ; 
 int SIGPROP_IGNORE ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sig_ffs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigdflt (struct sigacts*,int) ; 
 int sigprop (int) ; 
 int /*<<< orphan*/  sigqueue_delete_proc (struct proc*,int) ; 

void
sig_drop_caught(struct proc *p)
{
	int sig;
	struct sigacts *ps;

	ps = p->p_sigacts;
	PROC_LOCK_ASSERT(p, MA_OWNED);
	mtx_assert(&ps->ps_mtx, MA_OWNED);
	while (SIGNOTEMPTY(ps->ps_sigcatch)) {
		sig = sig_ffs(&ps->ps_sigcatch);
		sigdflt(ps, sig);
		if ((sigprop(sig) & SIGPROP_IGNORE) != 0)
			sigqueue_delete_proc(p, sig);
	}
}