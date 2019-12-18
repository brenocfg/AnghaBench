#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  rux_runtime; } ;
struct thread {scalar_t__ td_lastcpu; scalar_t__ td_oncpu; int td_slptick; int /*<<< orphan*/  td_sigmask; int /*<<< orphan*/  td_siglist; int /*<<< orphan*/  td_cow; TYPE_2__ td_rux; int /*<<< orphan*/  td_user_pri; int /*<<< orphan*/  td_pri_class; scalar_t__ td_kstack; int /*<<< orphan*/  td_pcb; int /*<<< orphan*/  td_tid; int /*<<< orphan*/  td_flags; int /*<<< orphan*/  td_base_pri; int /*<<< orphan*/  td_priority; int /*<<< orphan*/  td_wchan; int /*<<< orphan*/ * td_lockname; int /*<<< orphan*/ * td_name; int /*<<< orphan*/ * td_wmesg; struct proc* td_proc; } ;
struct proc {scalar_t__ p_state; int /*<<< orphan*/  p_numthreads; } ;
struct TYPE_3__ {int /*<<< orphan*/  pri_user; int /*<<< orphan*/  pri_class; int /*<<< orphan*/  pri_native; int /*<<< orphan*/  pri_level; } ;
struct kinfo_proc {scalar_t__ ki_lastcpu_old; scalar_t__ ki_oncpu_old; scalar_t__ ki_lastcpu; scalar_t__ ki_oncpu; int ki_slptime; int /*<<< orphan*/  ki_sigmask; int /*<<< orphan*/  ki_siglist; scalar_t__ ki_rqindex; int /*<<< orphan*/  ki_cow; int /*<<< orphan*/  ki_estcpu; int /*<<< orphan*/  ki_pctcpu; int /*<<< orphan*/  ki_runtime; int /*<<< orphan*/  ki_rusage; TYPE_1__ ki_pri; void* ki_kstack; int /*<<< orphan*/  ki_pcb; int /*<<< orphan*/  ki_numthreads; int /*<<< orphan*/  ki_tid; int /*<<< orphan*/  ki_tdflags; int /*<<< orphan*/  ki_wchan; int /*<<< orphan*/  ki_stat; int /*<<< orphan*/  ki_lockname; int /*<<< orphan*/  ki_kiflag; int /*<<< orphan*/  ki_moretdname; int /*<<< orphan*/  ki_tdname; int /*<<< orphan*/  ki_wmesg; struct thread* ki_tdaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  KI_LOCKBLOCK ; 
 scalar_t__ MAXCPU_OLD ; 
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ NOCPU ; 
 void* NOCPU_OLD ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_STATLOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_STATUNLOCK (struct proc*) ; 
 scalar_t__ PRS_NORMAL ; 
 scalar_t__ PRS_ZOMBIE ; 
 scalar_t__ P_SHOULDSTOP (struct proc*) ; 
 int /*<<< orphan*/  SIDL ; 
 int /*<<< orphan*/  SLOCK ; 
 int /*<<< orphan*/  SRUN ; 
 int /*<<< orphan*/  SSLEEP ; 
 int /*<<< orphan*/  SSTOP ; 
 int /*<<< orphan*/  SWAIT ; 
 int /*<<< orphan*/  SZOMB ; 
 scalar_t__ TD_CAN_RUN (struct thread*) ; 
 scalar_t__ TD_IS_RUNNING (struct thread*) ; 
 scalar_t__ TD_IS_SLEEPING (struct thread*) ; 
 scalar_t__ TD_ON_LOCK (struct thread*) ; 
 scalar_t__ TD_ON_RUNQ (struct thread*) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cputick2usec (int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  rufetchtd (struct thread*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sched_estcpu (struct thread*) ; 
 int /*<<< orphan*/  sched_pctcpu (struct thread*) ; 
 int strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 
 int ticks ; 

__attribute__((used)) static void
fill_kinfo_thread(struct thread *td, struct kinfo_proc *kp, int preferthread)
{
	struct proc *p;

	p = td->td_proc;
	kp->ki_tdaddr = td;
	PROC_LOCK_ASSERT(p, MA_OWNED);

	if (preferthread)
		PROC_STATLOCK(p);
	thread_lock(td);
	if (td->td_wmesg != NULL)
		strlcpy(kp->ki_wmesg, td->td_wmesg, sizeof(kp->ki_wmesg));
	else
		bzero(kp->ki_wmesg, sizeof(kp->ki_wmesg));
	if (strlcpy(kp->ki_tdname, td->td_name, sizeof(kp->ki_tdname)) >=
	    sizeof(kp->ki_tdname)) {
		strlcpy(kp->ki_moretdname,
		    td->td_name + sizeof(kp->ki_tdname) - 1,
		    sizeof(kp->ki_moretdname));
	} else {
		bzero(kp->ki_moretdname, sizeof(kp->ki_moretdname));
	}
	if (TD_ON_LOCK(td)) {
		kp->ki_kiflag |= KI_LOCKBLOCK;
		strlcpy(kp->ki_lockname, td->td_lockname,
		    sizeof(kp->ki_lockname));
	} else {
		kp->ki_kiflag &= ~KI_LOCKBLOCK;
		bzero(kp->ki_lockname, sizeof(kp->ki_lockname));
	}

	if (p->p_state == PRS_NORMAL) { /* approximate. */
		if (TD_ON_RUNQ(td) ||
		    TD_CAN_RUN(td) ||
		    TD_IS_RUNNING(td)) {
			kp->ki_stat = SRUN;
		} else if (P_SHOULDSTOP(p)) {
			kp->ki_stat = SSTOP;
		} else if (TD_IS_SLEEPING(td)) {
			kp->ki_stat = SSLEEP;
		} else if (TD_ON_LOCK(td)) {
			kp->ki_stat = SLOCK;
		} else {
			kp->ki_stat = SWAIT;
		}
	} else if (p->p_state == PRS_ZOMBIE) {
		kp->ki_stat = SZOMB;
	} else {
		kp->ki_stat = SIDL;
	}

	/* Things in the thread */
	kp->ki_wchan = td->td_wchan;
	kp->ki_pri.pri_level = td->td_priority;
	kp->ki_pri.pri_native = td->td_base_pri;

	/*
	 * Note: legacy fields; clamp at the old NOCPU value and/or
	 * the maximum u_char CPU value.
	 */
	if (td->td_lastcpu == NOCPU)
		kp->ki_lastcpu_old = NOCPU_OLD;
	else if (td->td_lastcpu > MAXCPU_OLD)
		kp->ki_lastcpu_old = MAXCPU_OLD;
	else
		kp->ki_lastcpu_old = td->td_lastcpu;

	if (td->td_oncpu == NOCPU)
		kp->ki_oncpu_old = NOCPU_OLD;
	else if (td->td_oncpu > MAXCPU_OLD)
		kp->ki_oncpu_old = MAXCPU_OLD;
	else
		kp->ki_oncpu_old = td->td_oncpu;

	kp->ki_lastcpu = td->td_lastcpu;
	kp->ki_oncpu = td->td_oncpu;
	kp->ki_tdflags = td->td_flags;
	kp->ki_tid = td->td_tid;
	kp->ki_numthreads = p->p_numthreads;
	kp->ki_pcb = td->td_pcb;
	kp->ki_kstack = (void *)td->td_kstack;
	kp->ki_slptime = (ticks - td->td_slptick) / hz;
	kp->ki_pri.pri_class = td->td_pri_class;
	kp->ki_pri.pri_user = td->td_user_pri;

	if (preferthread) {
		rufetchtd(td, &kp->ki_rusage);
		kp->ki_runtime = cputick2usec(td->td_rux.rux_runtime);
		kp->ki_pctcpu = sched_pctcpu(td);
		kp->ki_estcpu = sched_estcpu(td);
		kp->ki_cow = td->td_cow;
	}

	/* We can't get this anymore but ps etc never used it anyway. */
	kp->ki_rqindex = 0;

	if (preferthread)
		kp->ki_siglist = td->td_siglist;
	kp->ki_sigmask = td->td_sigmask;
	thread_unlock(td);
	if (preferthread)
		PROC_STATUNLOCK(p);
}