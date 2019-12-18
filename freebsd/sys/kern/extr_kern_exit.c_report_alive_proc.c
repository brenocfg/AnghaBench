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
struct thread {int /*<<< orphan*/ * td_retval; struct proc* td_proc; } ;
struct proc {void* p_xsig; int /*<<< orphan*/  p_pid; int /*<<< orphan*/  p_ksi; int /*<<< orphan*/  p_flag; } ;
struct TYPE_3__ {int si_code; void* si_status; } ;
typedef  TYPE_1__ siginfo_t ;

/* Variables and functions */
 int CLD_CONTINUED ; 
 int CLD_STOPPED ; 
 int CLD_TRAPPED ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  P_CONTINUED ; 
 int /*<<< orphan*/  P_WAITED ; 
 int /*<<< orphan*/  SA_XLOCKED ; 
 void* SIGCONT ; 
 int WNOWAIT ; 
 void* W_STOPCODE (void*) ; 
 int /*<<< orphan*/  proctree_lock ; 
 int /*<<< orphan*/  sigqueue_take (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
report_alive_proc(struct thread *td, struct proc *p, siginfo_t *siginfo,
    int *status, int options, int si_code)
{
	bool cont;

	PROC_LOCK_ASSERT(p, MA_OWNED);
	sx_assert(&proctree_lock, SA_XLOCKED);
	MPASS(si_code == CLD_TRAPPED || si_code == CLD_STOPPED ||
	    si_code == CLD_CONTINUED);

	cont = si_code == CLD_CONTINUED;
	if ((options & WNOWAIT) == 0) {
		if (cont)
			p->p_flag &= ~P_CONTINUED;
		else
			p->p_flag |= P_WAITED;
		PROC_LOCK(td->td_proc);
		sigqueue_take(p->p_ksi);
		PROC_UNLOCK(td->td_proc);
	}
	sx_xunlock(&proctree_lock);
	if (siginfo != NULL) {
		siginfo->si_code = si_code;
		siginfo->si_status = cont ? SIGCONT : p->p_xsig;
	}
	if (status != NULL)
		*status = cont ? SIGCONT : W_STOPCODE(p->p_xsig);
	PROC_UNLOCK(p);
	td->td_retval[0] = p->p_pid;
}