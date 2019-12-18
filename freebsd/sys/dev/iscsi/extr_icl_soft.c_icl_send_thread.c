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
struct icl_pdu_stailq {int dummy; } ;
struct icl_conn {int ic_check_send_space; int ic_send_running; int /*<<< orphan*/  ic_send_cv; struct icl_pdu_stailq ic_to_send; int /*<<< orphan*/  ic_lock; scalar_t__ ic_disconnecting; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICL_CONN_LOCK (struct icl_conn*) ; 
 int /*<<< orphan*/  ICL_CONN_UNLOCK (struct icl_conn*) ; 
 int /*<<< orphan*/  STAILQ_CONCAT (struct icl_pdu_stailq*,struct icl_pdu_stailq*) ; 
 scalar_t__ STAILQ_EMPTY (struct icl_pdu_stailq*) ; 
 int /*<<< orphan*/  STAILQ_INIT (struct icl_pdu_stailq*) ; 
 int /*<<< orphan*/  STAILQ_SWAP (struct icl_pdu_stailq*,struct icl_pdu_stailq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icl_conn_send_pdus (struct icl_conn*,struct icl_pdu_stailq*) ; 
 int /*<<< orphan*/  icl_pdu ; 
 int /*<<< orphan*/  kthread_exit () ; 

__attribute__((used)) static void
icl_send_thread(void *arg)
{
	struct icl_conn *ic;
	struct icl_pdu_stailq queue;

	ic = arg;

	STAILQ_INIT(&queue);

	ICL_CONN_LOCK(ic);
	for (;;) {
		for (;;) {
			/*
			 * If the local queue is empty, populate it from
			 * the main one.  This way the icl_conn_send_pdus()
			 * can go through all the queued PDUs without holding
			 * any locks.
			 */
			if (STAILQ_EMPTY(&queue))
				STAILQ_SWAP(&ic->ic_to_send, &queue, icl_pdu);

			ic->ic_check_send_space = false;
			ICL_CONN_UNLOCK(ic);
			icl_conn_send_pdus(ic, &queue);
			ICL_CONN_LOCK(ic);

			/*
			 * The icl_soupcall_send() was called since the last
			 * call to sbspace(); go around;
			 */
			if (ic->ic_check_send_space)
				continue;

			/*
			 * Local queue is empty, but we still have PDUs
			 * in the main one; go around.
			 */
			if (STAILQ_EMPTY(&queue) &&
			    !STAILQ_EMPTY(&ic->ic_to_send))
				continue;

			/*
			 * There might be some stuff in the local queue,
			 * which didn't get sent due to not having enough send
			 * space.  Wait for socket upcall.
			 */
			break;
		}

		if (ic->ic_disconnecting) {
			//ICL_DEBUG("terminating");
			break;
		}

		cv_wait(&ic->ic_send_cv, ic->ic_lock);
	}

	/*
	 * We're exiting; move PDUs back to the main queue, so they can
	 * get freed properly.  At this point ordering doesn't matter.
	 */
	STAILQ_CONCAT(&ic->ic_to_send, &queue);

	ic->ic_send_running = false;
	cv_signal(&ic->ic_send_cv);
	ICL_CONN_UNLOCK(ic);
	kthread_exit();
}