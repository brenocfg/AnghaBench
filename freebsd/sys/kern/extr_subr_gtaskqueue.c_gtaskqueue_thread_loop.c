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
struct gtaskqueue {int tq_flags; int /*<<< orphan*/  tq_threads; int /*<<< orphan*/  tq_tcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASKQUEUE_CALLBACK_TYPE_INIT ; 
 int /*<<< orphan*/  TASKQUEUE_CALLBACK_TYPE_SHUTDOWN ; 
 int TQ_FLAGS_ACTIVE ; 
 int /*<<< orphan*/  TQ_LOCK (struct gtaskqueue*) ; 
 int /*<<< orphan*/  TQ_SLEEP (struct gtaskqueue*,struct gtaskqueue*,char*) ; 
 int /*<<< orphan*/  TQ_UNLOCK (struct gtaskqueue*) ; 
 int /*<<< orphan*/  gtaskqueue_run_callback (struct gtaskqueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtaskqueue_run_locked (struct gtaskqueue*) ; 
 int /*<<< orphan*/  kthread_exit () ; 
 int /*<<< orphan*/  wakeup_one (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gtaskqueue_thread_loop(void *arg)
{
	struct gtaskqueue **tqp, *tq;

	tqp = arg;
	tq = *tqp;
	gtaskqueue_run_callback(tq, TASKQUEUE_CALLBACK_TYPE_INIT);
	TQ_LOCK(tq);
	while ((tq->tq_flags & TQ_FLAGS_ACTIVE) != 0) {
		/* XXX ? */
		gtaskqueue_run_locked(tq);
		/*
		 * Because taskqueue_run() can drop tq_mutex, we need to
		 * check if the TQ_FLAGS_ACTIVE flag wasn't removed in the
		 * meantime, which means we missed a wakeup.
		 */
		if ((tq->tq_flags & TQ_FLAGS_ACTIVE) == 0)
			break;
		TQ_SLEEP(tq, tq, "-");
	}
	gtaskqueue_run_locked(tq);
	/*
	 * This thread is on its way out, so just drop the lock temporarily
	 * in order to call the shutdown callback.  This allows the callback
	 * to look at the taskqueue, even just before it dies.
	 */
	TQ_UNLOCK(tq);
	gtaskqueue_run_callback(tq, TASKQUEUE_CALLBACK_TYPE_SHUTDOWN);
	TQ_LOCK(tq);

	/* rendezvous with thread that asked us to terminate */
	tq->tq_tcount--;
	wakeup_one(tq->tq_threads);
	TQ_UNLOCK(tq);
	kthread_exit();
}