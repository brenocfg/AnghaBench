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
struct thread {int /*<<< orphan*/  td_tid; } ;
struct futex_waiter {int fw_locked; struct futex_queue* fw_queue; int /*<<< orphan*/  fw_wait; int /*<<< orphan*/  fw_donated; int /*<<< orphan*/  fw_tid; } ;
struct futex_queue {int /*<<< orphan*/  fq_count; int /*<<< orphan*/  fq_list; } ;
struct futex_lock {int /*<<< orphan*/  fl_waitcount; } ;
typedef  int /*<<< orphan*/  sbintime_t ;
typedef  scalar_t__ cloudabi_timestamp_t ;
typedef  int /*<<< orphan*/  cloudabi_clockid_t ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct futex_waiter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_REMOVE (int /*<<< orphan*/ *,struct futex_waiter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ UINT64_MAX ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,char*) ; 
 int cv_timedwait_sig_sbt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cv_wait_sig (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  futex_global_lock ; 
 int /*<<< orphan*/  futex_lock_assert (struct futex_lock*) ; 
 int futex_queue_convert_timestamp (struct thread*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  futex_queue_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  futex_waiter ; 
 int /*<<< orphan*/  fw_next ; 

__attribute__((used)) static int
futex_queue_sleep(struct futex_queue *fq, struct futex_lock *fl,
    struct futex_waiter *fw, struct thread *td, cloudabi_clockid_t clock_id,
    cloudabi_timestamp_t timeout, cloudabi_timestamp_t precision, bool abstime)
{
	sbintime_t sbttimeout, sbtprecision;
	int error;

	/* Initialize futex_waiter object. */
	fw->fw_tid = td->td_tid;
	fw->fw_locked = false;
	futex_queue_init(&fw->fw_donated);

	if (timeout != UINT64_MAX) {
		/* Convert timeout duration. */
		error = futex_queue_convert_timestamp(td, clock_id, timeout,
		    precision, &sbttimeout, &sbtprecision, abstime);
		if (error != 0)
			return (error);
	}

	/* Place object in the queue. */
	fw->fw_queue = fq;
	STAILQ_INSERT_TAIL(&fq->fq_list, fw, fw_next);
	++fq->fq_count;

	cv_init(&fw->fw_wait, "futex");
	++fl->fl_waitcount;

	futex_lock_assert(fl);
	if (timeout == UINT64_MAX) {
		/* Wait without a timeout. */
		error = cv_wait_sig(&fw->fw_wait, &futex_global_lock);
	} else {
		/* Wait respecting the timeout. */
		error = cv_timedwait_sig_sbt(&fw->fw_wait, &futex_global_lock,
		    sbttimeout, sbtprecision, 0);
		futex_lock_assert(fl);
		if (error == EWOULDBLOCK &&
		    fw->fw_queue != NULL && fw->fw_queue != fq) {
			/*
			 * We got signalled on a condition variable, but
			 * observed a timeout while waiting to reacquire
			 * the lock. In other words, we didn't actually
			 * time out. Go back to sleep and wait for the
			 * lock to be reacquired.
			 */
			error = cv_wait_sig(&fw->fw_wait, &futex_global_lock);
		}
	}
	futex_lock_assert(fl);

	--fl->fl_waitcount;
	cv_destroy(&fw->fw_wait);

	fq = fw->fw_queue;
	if (fq == NULL) {
		/* Thread got dequeued, so we've slept successfully. */
		return (0);
	}

	/* Thread is still enqueued. Remove it. */
	KASSERT(error != 0, ("Woken up thread is still enqueued"));
	STAILQ_REMOVE(&fq->fq_list, fw, futex_waiter, fw_next);
	--fq->fq_count;
	return (error == EWOULDBLOCK ? ETIMEDOUT : error);
}