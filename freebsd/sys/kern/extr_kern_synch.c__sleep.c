#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct thread {int /*<<< orphan*/  td_name; TYPE_1__* td_proc; int /*<<< orphan*/  td_tid; } ;
struct lock_object {int dummy; } ;
struct lock_class {uintptr_t (* lc_unlock ) (struct lock_object*) ;int lc_flags; int /*<<< orphan*/  (* lc_lock ) (struct lock_object*,uintptr_t) ;} ;
typedef  int /*<<< orphan*/  sbintime_t ;
struct TYPE_6__ {struct lock_object lock_object; } ;
struct TYPE_5__ {int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR5 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,void*) ; 
 int /*<<< orphan*/  DROP_GIANT () ; 
 TYPE_2__ Giant ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ KTRPOINT (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTR_CSW ; 
 int /*<<< orphan*/  KTR_PROC ; 
 int LC_SLEEPABLE ; 
 struct lock_class* LOCK_CLASS (struct lock_object*) ; 
 int MAXCPU ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int PCATCH ; 
 int PDROP ; 
 int /*<<< orphan*/  PICKUP_GIANT () ; 
 int PRIMASK ; 
 scalar_t__ SCHEDULER_STOPPED_TD (struct thread*) ; 
 int SLEEPQ_INTERRUPTIBLE ; 
 int SLEEPQ_PAUSE ; 
 int SLEEPQ_SLEEP ; 
 int TD_IS_RUNNING (struct thread*) ; 
 int /*<<< orphan*/  TD_ON_SLEEPQ (struct thread*) ; 
 int WARN_GIANTOK ; 
 int WARN_SLEEPOK ; 
 int /*<<< orphan*/  WITNESS_RESTORE (struct lock_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WITNESS_SAVE (struct lock_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WITNESS_SAVE_DECL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WITNESS_WARN (int,struct lock_object*,char*,char const*) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  ktrcsw (int,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  lock_witness ; 
 int /*<<< orphan*/  mtx_assert (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ mtx_owned (TYPE_2__*) ; 
 int /*<<< orphan*/ * pause_wchan ; 
 int /*<<< orphan*/  sleepq_add (void*,struct lock_object*,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleepq_lock (void*) ; 
 int /*<<< orphan*/  sleepq_release (void*) ; 
 int /*<<< orphan*/  sleepq_set_timeout_sbt (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int sleepq_timedwait (void*,int) ; 
 int sleepq_timedwait_sig (void*,int) ; 
 int /*<<< orphan*/  sleepq_wait (void*,int) ; 
 int sleepq_wait_sig (void*,int) ; 
 uintptr_t stub1 (struct lock_object*) ; 
 uintptr_t stub2 (struct lock_object*) ; 
 uintptr_t stub3 (struct lock_object*) ; 
 int /*<<< orphan*/  stub4 (struct lock_object*,uintptr_t) ; 

int
_sleep(void *ident, struct lock_object *lock, int priority,
    const char *wmesg, sbintime_t sbt, sbintime_t pr, int flags)
{
	struct thread *td;
	struct lock_class *class;
	uintptr_t lock_state;
	int catch, pri, rval, sleepq_flags;
	WITNESS_SAVE_DECL(lock_witness);

	td = curthread;
#ifdef KTRACE
	if (KTRPOINT(td, KTR_CSW))
		ktrcsw(1, 0, wmesg);
#endif
	WITNESS_WARN(WARN_GIANTOK | WARN_SLEEPOK, lock,
	    "Sleeping on \"%s\"", wmesg);
	KASSERT(sbt != 0 || mtx_owned(&Giant) || lock != NULL,
	    ("sleeping without a lock"));
	KASSERT(ident != NULL, ("_sleep: NULL ident"));
	KASSERT(TD_IS_RUNNING(td), ("_sleep: curthread not running"));
	if (priority & PDROP)
		KASSERT(lock != NULL && lock != &Giant.lock_object,
		    ("PDROP requires a non-Giant lock"));
	if (lock != NULL)
		class = LOCK_CLASS(lock);
	else
		class = NULL;

	if (SCHEDULER_STOPPED_TD(td)) {
		if (lock != NULL && priority & PDROP)
			class->lc_unlock(lock);
		return (0);
	}
	catch = priority & PCATCH;
	pri = priority & PRIMASK;

	KASSERT(!TD_ON_SLEEPQ(td), ("recursive sleep"));

	if ((uint8_t *)ident >= &pause_wchan[0] &&
	    (uint8_t *)ident <= &pause_wchan[MAXCPU - 1])
		sleepq_flags = SLEEPQ_PAUSE;
	else
		sleepq_flags = SLEEPQ_SLEEP;
	if (catch)
		sleepq_flags |= SLEEPQ_INTERRUPTIBLE;

	sleepq_lock(ident);
	CTR5(KTR_PROC, "sleep: thread %ld (pid %ld, %s) on %s (%p)",
	    td->td_tid, td->td_proc->p_pid, td->td_name, wmesg, ident);

	if (lock == &Giant.lock_object)
		mtx_assert(&Giant, MA_OWNED);
	DROP_GIANT();
	if (lock != NULL && lock != &Giant.lock_object &&
	    !(class->lc_flags & LC_SLEEPABLE)) {
		WITNESS_SAVE(lock, lock_witness);
		lock_state = class->lc_unlock(lock);
	} else
		/* GCC needs to follow the Yellow Brick Road */
		lock_state = -1;

	/*
	 * We put ourselves on the sleep queue and start our timeout
	 * before calling thread_suspend_check, as we could stop there,
	 * and a wakeup or a SIGCONT (or both) could occur while we were
	 * stopped without resuming us.  Thus, we must be ready for sleep
	 * when cursig() is called.  If the wakeup happens while we're
	 * stopped, then td will no longer be on a sleep queue upon
	 * return from cursig().
	 */
	sleepq_add(ident, lock, wmesg, sleepq_flags, 0);
	if (sbt != 0)
		sleepq_set_timeout_sbt(ident, sbt, pr, flags);
	if (lock != NULL && class->lc_flags & LC_SLEEPABLE) {
		sleepq_release(ident);
		WITNESS_SAVE(lock, lock_witness);
		lock_state = class->lc_unlock(lock);
		sleepq_lock(ident);
	}
	if (sbt != 0 && catch)
		rval = sleepq_timedwait_sig(ident, pri);
	else if (sbt != 0)
		rval = sleepq_timedwait(ident, pri);
	else if (catch)
		rval = sleepq_wait_sig(ident, pri);
	else {
		sleepq_wait(ident, pri);
		rval = 0;
	}
#ifdef KTRACE
	if (KTRPOINT(td, KTR_CSW))
		ktrcsw(0, 0, wmesg);
#endif
	PICKUP_GIANT();
	if (lock != NULL && lock != &Giant.lock_object && !(priority & PDROP)) {
		class->lc_lock(lock, lock_state);
		WITNESS_RESTORE(lock, lock_witness);
	}
	return (rval);
}