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
struct thread {int td_xsig; int td_dbgflags; int /*<<< orphan*/  td_sigqueue; int /*<<< orphan*/ * td_wchan; int /*<<< orphan*/  td_tid; struct proc* td_proc; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock_object; } ;
struct proc {int p_flag; int p_flag2; int p_xsig; struct thread* p_xthread; scalar_t__ p_ptevents; int /*<<< orphan*/  p_pid; TYPE_1__ p_mtx; } ;
struct TYPE_8__ {int ksi_flags; int ksi_signo; } ;
typedef  TYPE_2__ ksiginfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTR4 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int KSI_HEAD ; 
 int KSI_PTRACE ; 
 int /*<<< orphan*/  KTR_PTRACE ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int P2_PTRACE_FSTP ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_SLOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_SUNLOCK (struct proc*) ; 
 scalar_t__ P_KILLED (struct proc*) ; 
 int P_SINGLE_EXIT ; 
 int P_STOPPED_SIG ; 
 int P_STOPPED_TRACE ; 
 int P_TRACED ; 
 int P_WEXIT ; 
 int SIGKILL ; 
 int TDB_EXIT ; 
 int TDB_FSTP ; 
 int TDB_STOPATFORK ; 
 int TDB_SUSPEND ; 
 int TDB_XSIG ; 
 int WARN_GIANTOK ; 
 int WARN_SLEEPOK ; 
 int /*<<< orphan*/  WITNESS_WARN (int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ksiginfo_init (TYPE_2__*) ; 
 int /*<<< orphan*/  sig_suspend_threads (struct thread*,struct proc*,int /*<<< orphan*/ ) ; 
 int sigprop (int) ; 
 scalar_t__ sigqueue_add (int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 struct thread* sigtd (struct proc*,int,int) ; 
 int /*<<< orphan*/  tdsendsignal (struct proc*,struct thread*,int,TYPE_2__*) ; 
 int /*<<< orphan*/  thread_suspend_switch (struct thread*,struct proc*) ; 

int
ptracestop(struct thread *td, int sig, ksiginfo_t *si)
{
	struct proc *p = td->td_proc;
	struct thread *td2;
	ksiginfo_t ksi;
	int prop;

	PROC_LOCK_ASSERT(p, MA_OWNED);
	KASSERT(!(p->p_flag & P_WEXIT), ("Stopping exiting process"));
	WITNESS_WARN(WARN_GIANTOK | WARN_SLEEPOK,
	    &p->p_mtx.lock_object, "Stopping for traced signal");

	td->td_xsig = sig;

	if (si == NULL || (si->ksi_flags & KSI_PTRACE) == 0) {
		td->td_dbgflags |= TDB_XSIG;
		CTR4(KTR_PTRACE, "ptracestop: tid %d (pid %d) flags %#x sig %d",
		    td->td_tid, p->p_pid, td->td_dbgflags, sig);
		PROC_SLOCK(p);
		while ((p->p_flag & P_TRACED) && (td->td_dbgflags & TDB_XSIG)) {
			if (P_KILLED(p)) {
				/*
				 * Ensure that, if we've been PT_KILLed, the
				 * exit status reflects that. Another thread
				 * may also be in ptracestop(), having just
				 * received the SIGKILL, but this thread was
				 * unsuspended first.
				 */
				td->td_dbgflags &= ~TDB_XSIG;
				td->td_xsig = SIGKILL;
				p->p_ptevents = 0;
				break;
			}
			if (p->p_flag & P_SINGLE_EXIT &&
			    !(td->td_dbgflags & TDB_EXIT)) {
				/*
				 * Ignore ptrace stops except for thread exit
				 * events when the process exits.
				 */
				td->td_dbgflags &= ~TDB_XSIG;
				PROC_SUNLOCK(p);
				return (0);
			}

			/*
			 * Make wait(2) work.  Ensure that right after the
			 * attach, the thread which was decided to become the
			 * leader of attach gets reported to the waiter.
			 * Otherwise, just avoid overwriting another thread's
			 * assignment to p_xthread.  If another thread has
			 * already set p_xthread, the current thread will get
			 * a chance to report itself upon the next iteration.
			 */
			if ((td->td_dbgflags & TDB_FSTP) != 0 ||
			    ((p->p_flag2 & P2_PTRACE_FSTP) == 0 &&
			    p->p_xthread == NULL)) {
				p->p_xsig = sig;
				p->p_xthread = td;

				/*
				 * If we are on sleepqueue already,
				 * let sleepqueue code decide if it
				 * needs to go sleep after attach.
				 */
				if (td->td_wchan == NULL)
					td->td_dbgflags &= ~TDB_FSTP;

				p->p_flag2 &= ~P2_PTRACE_FSTP;
				p->p_flag |= P_STOPPED_SIG | P_STOPPED_TRACE;
				sig_suspend_threads(td, p, 0);
			}
			if ((td->td_dbgflags & TDB_STOPATFORK) != 0) {
				td->td_dbgflags &= ~TDB_STOPATFORK;
			}
stopme:
			thread_suspend_switch(td, p);
			if (p->p_xthread == td)
				p->p_xthread = NULL;
			if (!(p->p_flag & P_TRACED))
				break;
			if (td->td_dbgflags & TDB_SUSPEND) {
				if (p->p_flag & P_SINGLE_EXIT)
					break;
				goto stopme;
			}
		}
		PROC_SUNLOCK(p);
	}

	if (si != NULL && sig == td->td_xsig) {
		/* Parent wants us to take the original signal unchanged. */
		si->ksi_flags |= KSI_HEAD;
		if (sigqueue_add(&td->td_sigqueue, sig, si) != 0)
			si->ksi_signo = 0;
	} else if (td->td_xsig != 0) {
		/*
		 * If parent wants us to take a new signal, then it will leave
		 * it in td->td_xsig; otherwise we just look for signals again.
		 */
		ksiginfo_init(&ksi);
		ksi.ksi_signo = td->td_xsig;
		ksi.ksi_flags |= KSI_PTRACE;
		prop = sigprop(td->td_xsig);
		td2 = sigtd(p, td->td_xsig, prop);
		tdsendsignal(p, td2, td->td_xsig, &ksi);
		if (td != td2)
			return (0);
	}

	return (td->td_xsig);
}