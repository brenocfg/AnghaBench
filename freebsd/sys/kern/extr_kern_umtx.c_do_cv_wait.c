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
typedef  scalar_t__ uint32_t ;
typedef  int u_long ;
struct umutex {int dummy; } ;
struct umtx_q {int uq_flags; int /*<<< orphan*/  uq_key; TYPE_1__* uq_cur_queue; } ;
struct ucond {int /*<<< orphan*/  c_has_waiters; int /*<<< orphan*/  c_clockid; int /*<<< orphan*/  c_flags; } ;
struct timespec {int dummy; } ;
struct thread {struct umtx_q* td_umtxq; } ;
struct abs_timeout {int dummy; } ;
struct TYPE_2__ {int length; } ;

/* Variables and functions */
 scalar_t__ CLOCK_REALTIME ; 
 scalar_t__ CLOCK_THREAD_CPUTIME_ID ; 
 int CVWAIT_ABSTIME ; 
 int CVWAIT_CLOCKID ; 
 int EFAULT ; 
 int EINTR ; 
 int EINVAL ; 
 int ERESTART ; 
 int /*<<< orphan*/  GET_SHARE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_CV ; 
 int UQF_UMTXQ ; 
 int /*<<< orphan*/  abs_timeout_init (struct abs_timeout*,scalar_t__,int,struct timespec*) ; 
 int do_unlock_umutex (struct thread*,struct umutex*,int) ; 
 int fueword32 (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  suword32 (int /*<<< orphan*/ *,int) ; 
 int umtx_key_get (struct ucond*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umtx_key_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umtxq_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umtxq_insert (struct umtx_q*) ; 
 int /*<<< orphan*/  umtxq_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umtxq_remove (struct umtx_q*) ; 
 int umtxq_sleep (struct umtx_q*,char*,struct abs_timeout*) ; 
 int /*<<< orphan*/  umtxq_unbusy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umtxq_unbusy_unlocked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umtxq_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
do_cv_wait(struct thread *td, struct ucond *cv, struct umutex *m,
    struct timespec *timeout, u_long wflags)
{
	struct abs_timeout timo;
	struct umtx_q *uq;
	uint32_t flags, clockid, hasw;
	int error;

	uq = td->td_umtxq;
	error = fueword32(&cv->c_flags, &flags);
	if (error == -1)
		return (EFAULT);
	error = umtx_key_get(cv, TYPE_CV, GET_SHARE(flags), &uq->uq_key);
	if (error != 0)
		return (error);

	if ((wflags & CVWAIT_CLOCKID) != 0) {
		error = fueword32(&cv->c_clockid, &clockid);
		if (error == -1) {
			umtx_key_release(&uq->uq_key);
			return (EFAULT);
		}
		if (clockid < CLOCK_REALTIME ||
		    clockid >= CLOCK_THREAD_CPUTIME_ID) {
			/* hmm, only HW clock id will work. */
			umtx_key_release(&uq->uq_key);
			return (EINVAL);
		}
	} else {
		clockid = CLOCK_REALTIME;
	}

	umtxq_lock(&uq->uq_key);
	umtxq_busy(&uq->uq_key);
	umtxq_insert(uq);
	umtxq_unlock(&uq->uq_key);

	/*
	 * Set c_has_waiters to 1 before releasing user mutex, also
	 * don't modify cache line when unnecessary.
	 */
	error = fueword32(&cv->c_has_waiters, &hasw);
	if (error == 0 && hasw == 0)
		suword32(&cv->c_has_waiters, 1);

	umtxq_unbusy_unlocked(&uq->uq_key);

	error = do_unlock_umutex(td, m, false);

	if (timeout != NULL)
		abs_timeout_init(&timo, clockid, (wflags & CVWAIT_ABSTIME) != 0,
		    timeout);
	
	umtxq_lock(&uq->uq_key);
	if (error == 0) {
		error = umtxq_sleep(uq, "ucond", timeout == NULL ?
		    NULL : &timo);
	}

	if ((uq->uq_flags & UQF_UMTXQ) == 0)
		error = 0;
	else {
		/*
		 * This must be timeout,interrupted by signal or
		 * surprious wakeup, clear c_has_waiter flag when
		 * necessary.
		 */
		umtxq_busy(&uq->uq_key);
		if ((uq->uq_flags & UQF_UMTXQ) != 0) {
			int oldlen = uq->uq_cur_queue->length;
			umtxq_remove(uq);
			if (oldlen == 1) {
				umtxq_unlock(&uq->uq_key);
				suword32(&cv->c_has_waiters, 0);
				umtxq_lock(&uq->uq_key);
			}
		}
		umtxq_unbusy(&uq->uq_key);
		if (error == ERESTART)
			error = EINTR;
	}

	umtxq_unlock(&uq->uq_key);
	umtx_key_release(&uq->uq_key);
	return (error);
}