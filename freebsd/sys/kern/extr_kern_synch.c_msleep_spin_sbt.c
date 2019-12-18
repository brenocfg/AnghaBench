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
struct thread {int /*<<< orphan*/  td_name; TYPE_1__* td_proc; int /*<<< orphan*/  td_tid; } ;
struct mtx {int /*<<< orphan*/  lock_object; } ;
typedef  int /*<<< orphan*/  sbintime_t ;
struct TYPE_2__ {int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR5 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,void*) ; 
 int /*<<< orphan*/  DROP_GIANT () ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ KTRPOINT (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTR_CSW ; 
 int /*<<< orphan*/  KTR_PROC ; 
 int MA_NOTRECURSED ; 
 int MA_OWNED ; 
 int /*<<< orphan*/  PICKUP_GIANT () ; 
 scalar_t__ SCHEDULER_STOPPED_TD (struct thread*) ; 
 int /*<<< orphan*/  SLEEPQ_SLEEP ; 
 int /*<<< orphan*/  TD_IS_RUNNING (struct thread*) ; 
 int WARN_GIANTOK ; 
 int WARN_SLEEPOK ; 
 int /*<<< orphan*/  WITNESS_RESTORE (int /*<<< orphan*/ *,struct mtx*) ; 
 int /*<<< orphan*/  WITNESS_SAVE (int /*<<< orphan*/ *,struct mtx*) ; 
 int /*<<< orphan*/  WITNESS_SAVE_DECL (struct mtx*) ; 
 int /*<<< orphan*/  WITNESS_WARN (int,int /*<<< orphan*/ *,char*,char const*) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  ktrcsw (int,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  mtx_assert (struct mtx*,int) ; 
 int /*<<< orphan*/  mtx_lock_spin (struct mtx*) ; 
 int /*<<< orphan*/  mtx_unlock_spin (struct mtx*) ; 
 int /*<<< orphan*/  sleepq_add (void*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleepq_lock (void*) ; 
 int /*<<< orphan*/  sleepq_release (void*) ; 
 int /*<<< orphan*/  sleepq_set_timeout_sbt (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int sleepq_timedwait (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleepq_wait (void*,int /*<<< orphan*/ ) ; 

int
msleep_spin_sbt(void *ident, struct mtx *mtx, const char *wmesg,
    sbintime_t sbt, sbintime_t pr, int flags)
{
	struct thread *td;
	int rval;
	WITNESS_SAVE_DECL(mtx);

	td = curthread;
	KASSERT(mtx != NULL, ("sleeping without a mutex"));
	KASSERT(ident != NULL, ("msleep_spin_sbt: NULL ident"));
	KASSERT(TD_IS_RUNNING(td), ("msleep_spin_sbt: curthread not running"));

	if (SCHEDULER_STOPPED_TD(td))
		return (0);

	sleepq_lock(ident);
	CTR5(KTR_PROC, "msleep_spin: thread %ld (pid %ld, %s) on %s (%p)",
	    td->td_tid, td->td_proc->p_pid, td->td_name, wmesg, ident);

	DROP_GIANT();
	mtx_assert(mtx, MA_OWNED | MA_NOTRECURSED);
	WITNESS_SAVE(&mtx->lock_object, mtx);
	mtx_unlock_spin(mtx);

	/*
	 * We put ourselves on the sleep queue and start our timeout.
	 */
	sleepq_add(ident, &mtx->lock_object, wmesg, SLEEPQ_SLEEP, 0);
	if (sbt != 0)
		sleepq_set_timeout_sbt(ident, sbt, pr, flags);

	/*
	 * Can't call ktrace with any spin locks held so it can lock the
	 * ktrace_mtx lock, and WITNESS_WARN considers it an error to hold
	 * any spin lock.  Thus, we have to drop the sleepq spin lock while
	 * we handle those requests.  This is safe since we have placed our
	 * thread on the sleep queue already.
	 */
#ifdef KTRACE
	if (KTRPOINT(td, KTR_CSW)) {
		sleepq_release(ident);
		ktrcsw(1, 0, wmesg);
		sleepq_lock(ident);
	}
#endif
#ifdef WITNESS
	sleepq_release(ident);
	WITNESS_WARN(WARN_GIANTOK | WARN_SLEEPOK, NULL, "Sleeping on \"%s\"",
	    wmesg);
	sleepq_lock(ident);
#endif
	if (sbt != 0)
		rval = sleepq_timedwait(ident, 0);
	else {
		sleepq_wait(ident, 0);
		rval = 0;
	}
#ifdef KTRACE
	if (KTRPOINT(td, KTR_CSW))
		ktrcsw(0, 0, wmesg);
#endif
	PICKUP_GIANT();
	mtx_lock_spin(mtx);
	WITNESS_RESTORE(&mtx->lock_object, mtx);
	return (rval);
}