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
struct thread {int dummy; } ;
struct lock_object {int dummy; } ;
struct lock_class {int lc_flags; int (* lc_unlock ) (struct lock_object*) ;int /*<<< orphan*/  (* lc_lock ) (struct lock_object*,int) ;} ;
struct cv {int /*<<< orphan*/  cv_description; } ;
typedef  int /*<<< orphan*/  sbintime_t ;
struct TYPE_3__ {struct lock_object lock_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  CV_ASSERT (struct cv*,struct lock_object*,struct thread*) ; 
 int /*<<< orphan*/  CV_WAITERS_INC (struct cv*) ; 
 int /*<<< orphan*/  DROP_GIANT () ; 
 TYPE_1__ Giant ; 
 scalar_t__ KTRPOINT (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTR_CSW ; 
 int LC_SLEEPABLE ; 
 struct lock_class* LOCK_CLASS (struct lock_object*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PICKUP_GIANT () ; 
 scalar_t__ SCHEDULER_STOPPED_TD (struct thread*) ; 
 int SLEEPQ_CONDVAR ; 
 int SLEEPQ_INTERRUPTIBLE ; 
 int WARN_GIANTOK ; 
 int WARN_SLEEPOK ; 
 int /*<<< orphan*/  WITNESS_RESTORE (struct lock_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WITNESS_SAVE (struct lock_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WITNESS_SAVE_DECL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WITNESS_WARN (int,struct lock_object*,char*,int /*<<< orphan*/ ) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  cv_wmesg (struct cv*) ; 
 int /*<<< orphan*/  ktrcsw (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_witness ; 
 int /*<<< orphan*/  mtx_assert (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleepq_add (struct cv*,struct lock_object*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleepq_lock (struct cv*) ; 
 int /*<<< orphan*/  sleepq_release (struct cv*) ; 
 int /*<<< orphan*/  sleepq_set_timeout_sbt (struct cv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int sleepq_timedwait_sig (struct cv*,int /*<<< orphan*/ ) ; 
 int stub1 (struct lock_object*) ; 
 int /*<<< orphan*/  stub2 (struct lock_object*,int) ; 

int
_cv_timedwait_sig_sbt(struct cv *cvp, struct lock_object *lock,
    sbintime_t sbt, sbintime_t pr, int flags)
{
	WITNESS_SAVE_DECL(lock_witness);
	struct lock_class *class;
	struct thread *td;
	int lock_state, rval;

	td = curthread;
	lock_state = 0;
#ifdef KTRACE
	if (KTRPOINT(td, KTR_CSW))
		ktrcsw(1, 0, cv_wmesg(cvp));
#endif
	CV_ASSERT(cvp, lock, td);
	WITNESS_WARN(WARN_GIANTOK | WARN_SLEEPOK, lock,
	    "Waiting on \"%s\"", cvp->cv_description);
	class = LOCK_CLASS(lock);

	if (SCHEDULER_STOPPED_TD(td))
		return (0);

	sleepq_lock(cvp);

	CV_WAITERS_INC(cvp);
	if (lock == &Giant.lock_object)
		mtx_assert(&Giant, MA_OWNED);
	DROP_GIANT();

	sleepq_add(cvp, lock, cvp->cv_description, SLEEPQ_CONDVAR |
	    SLEEPQ_INTERRUPTIBLE, 0);
	sleepq_set_timeout_sbt(cvp, sbt, pr, flags);
	if (lock != &Giant.lock_object) {
		if (class->lc_flags & LC_SLEEPABLE)
			sleepq_release(cvp);
		WITNESS_SAVE(lock, lock_witness);
		lock_state = class->lc_unlock(lock);
		if (class->lc_flags & LC_SLEEPABLE)
			sleepq_lock(cvp);
	}
	rval = sleepq_timedwait_sig(cvp, 0);

#ifdef KTRACE
	if (KTRPOINT(td, KTR_CSW))
		ktrcsw(0, 0, cv_wmesg(cvp));
#endif
	PICKUP_GIANT();
	if (lock != &Giant.lock_object) {
		class->lc_lock(lock, lock_state);
		WITNESS_RESTORE(lock, lock_witness);
	}

	return (rval);
}