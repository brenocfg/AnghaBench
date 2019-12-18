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
struct trapframe {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  code; } ;
struct thread {int td_dbgflags; TYPE_1__ td_sa; struct proc* td_proc; } ;
struct proc {int p_flag; int p_ptevents; } ;

/* Variables and functions */
 scalar_t__ KTRPOINT (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTR_SYSRET ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int PTRACE_SCX ; 
 int P_TRACED ; 
 int /*<<< orphan*/  SIGSTOP ; 
 int /*<<< orphan*/  SIGTRAP ; 
 int /*<<< orphan*/  SYS_fork ; 
 int /*<<< orphan*/  S_SCX ; 
 int TDB_BORN ; 
 int TDB_CHILD ; 
 int TDB_FSTP ; 
 int TDB_SCX ; 
 int TDB_STOPATFORK ; 
 int /*<<< orphan*/  _STOPEVENT (struct proc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktrsysret (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptracestop (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  userret (struct thread*,struct trapframe*) ; 

void
fork_return(struct thread *td, struct trapframe *frame)
{
	struct proc *p;

	p = td->td_proc;
	if (td->td_dbgflags & TDB_STOPATFORK) {
		PROC_LOCK(p);
		if ((p->p_flag & P_TRACED) != 0) {
			/*
			 * Inform the debugger if one is still present.
			 */
			td->td_dbgflags |= TDB_CHILD | TDB_SCX | TDB_FSTP;
			ptracestop(td, SIGSTOP, NULL);
			td->td_dbgflags &= ~(TDB_CHILD | TDB_SCX);
		} else {
			/*
			 * ... otherwise clear the request.
			 */
			td->td_dbgflags &= ~TDB_STOPATFORK;
		}
		PROC_UNLOCK(p);
	} else if (p->p_flag & P_TRACED || td->td_dbgflags & TDB_BORN) {
 		/*
		 * This is the start of a new thread in a traced
		 * process.  Report a system call exit event.
		 */
		PROC_LOCK(p);
		td->td_dbgflags |= TDB_SCX;
		_STOPEVENT(p, S_SCX, td->td_sa.code);
		if ((p->p_ptevents & PTRACE_SCX) != 0 ||
		    (td->td_dbgflags & TDB_BORN) != 0)
			ptracestop(td, SIGTRAP, NULL);
		td->td_dbgflags &= ~(TDB_SCX | TDB_BORN);
		PROC_UNLOCK(p);
	}

	userret(td, frame);

#ifdef KTRACE
	if (KTRPOINT(td, KTR_SYSRET))
		ktrsysret(SYS_fork, 0, 0);
#endif
}