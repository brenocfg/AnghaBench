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
struct taskqueue {int tq_flags; int /*<<< orphan*/  tq_threads; int /*<<< orphan*/  tq_tcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASKQUEUE_CALLBACK_TYPE_INIT ; 
 int /*<<< orphan*/  TASKQUEUE_CALLBACK_TYPE_SHUTDOWN ; 
 int TQ_FLAGS_ACTIVE ; 
 int /*<<< orphan*/  TQ_LOCK (struct taskqueue*) ; 
 int /*<<< orphan*/  TQ_SLEEP (struct taskqueue*,struct taskqueue*,char*) ; 
 int /*<<< orphan*/  TQ_UNLOCK (struct taskqueue*) ; 
 int /*<<< orphan*/  kthread_exit () ; 
 int /*<<< orphan*/  taskqueue_run_callback (struct taskqueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_run_locked (struct taskqueue*) ; 
 int /*<<< orphan*/  wakeup_one (int /*<<< orphan*/ ) ; 

void
taskqueue_thread_loop(void *arg)
{
	struct taskqueue **tqp, *tq;

	tqp = arg;
	tq = *tqp;
	taskqueue_run_callback(tq, TASKQUEUE_CALLBACK_TYPE_INIT);
	TQ_LOCK(tq);
	while ((tq->tq_flags & TQ_FLAGS_ACTIVE) != 0) {
		/* XXX ? */
		taskqueue_run_locked(tq);
		/*
		 * Because taskqueue_run() can drop tq_mutex, we need to
		 * check if the TQ_FLAGS_ACTIVE flag wasn't removed in the
		 * meantime, which means we missed a wakeup.
		 */
		if ((tq->tq_flags & TQ_FLAGS_ACTIVE) == 0)
			break;
		TQ_SLEEP(tq, tq, "-");
	}
	taskqueue_run_locked(tq);
	/*
	 * This thread is on its way out, so just drop the lock temporarily
	 * in order to call the shutdown callback.  This allows the callback
	 * to look at the taskqueue, even just before it dies.
	 */
	TQ_UNLOCK(tq);
	taskqueue_run_callback(tq, TASKQUEUE_CALLBACK_TYPE_SHUTDOWN);
	TQ_LOCK(tq);

	/* rendezvous with thread that asked us to terminate */
	tq->tq_tcount--;
	wakeup_one(tq->tq_threads);
	TQ_UNLOCK(tq);
	kthread_exit();
}