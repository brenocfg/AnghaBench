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
struct cfiscsi_session {int cs_terminating; int cs_handoff_in_progress; int /*<<< orphan*/  cs_conn; int /*<<< orphan*/  cs_callout; int /*<<< orphan*/  cs_lock; int /*<<< orphan*/  cs_maintenance_cv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFISCSI_SESSION_DEBUG (struct cfiscsi_session*,char*) ; 
 int /*<<< orphan*/  CFISCSI_SESSION_LOCK (struct cfiscsi_session*) ; 
 int /*<<< orphan*/  CFISCSI_SESSION_UNLOCK (struct cfiscsi_session*) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfiscsi_session_delete (struct cfiscsi_session*) ; 
 int /*<<< orphan*/  cfiscsi_session_terminate_tasks (struct cfiscsi_session*) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  icl_conn_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_exit () ; 

__attribute__((used)) static void
cfiscsi_maintenance_thread(void *arg)
{
	struct cfiscsi_session *cs;

	cs = arg;

	for (;;) {
		CFISCSI_SESSION_LOCK(cs);
		if (cs->cs_terminating == false || cs->cs_handoff_in_progress)
			cv_wait(&cs->cs_maintenance_cv, &cs->cs_lock);
		CFISCSI_SESSION_UNLOCK(cs);

		if (cs->cs_terminating && cs->cs_handoff_in_progress == false) {

			/*
			 * We used to wait up to 30 seconds to deliver queued
			 * PDUs to the initiator.  We also tried hard to deliver
			 * SCSI Responses for the aborted PDUs.  We don't do
			 * that anymore.  We might need to revisit that.
			 */
			callout_drain(&cs->cs_callout);
			icl_conn_close(cs->cs_conn);

			/*
			 * At this point ICL receive thread is no longer
			 * running; no new tasks can be queued.
			 */
			cfiscsi_session_terminate_tasks(cs);
			cfiscsi_session_delete(cs);
			kthread_exit();
			return;
		}
		CFISCSI_SESSION_DEBUG(cs, "nothing to do");
	}
}