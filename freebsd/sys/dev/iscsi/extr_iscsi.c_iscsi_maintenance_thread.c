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
struct iscsi_session {int is_reconnecting; int is_terminating; int /*<<< orphan*/  is_lock; int /*<<< orphan*/  is_maintenance_cv; int /*<<< orphan*/  is_maxcmdsn; int /*<<< orphan*/  is_cmdsn; int /*<<< orphan*/  is_postponed; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_SESSION_LOCK (struct iscsi_session*) ; 
 int /*<<< orphan*/  ISCSI_SESSION_UNLOCK (struct iscsi_session*) ; 
 scalar_t__ ISCSI_SNGT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iscsi_maintenance_thread_reconnect (struct iscsi_session*) ; 
 int /*<<< orphan*/  iscsi_maintenance_thread_terminate (struct iscsi_session*) ; 
 int /*<<< orphan*/  iscsi_session_send_postponed (struct iscsi_session*) ; 
 int /*<<< orphan*/  kthread_exit () ; 

__attribute__((used)) static void
iscsi_maintenance_thread(void *arg)
{
	struct iscsi_session *is = arg;

	ISCSI_SESSION_LOCK(is);
	for (;;) {
		if (is->is_reconnecting == false &&
		    is->is_terminating == false &&
		    (STAILQ_EMPTY(&is->is_postponed) ||
		     ISCSI_SNGT(is->is_cmdsn, is->is_maxcmdsn)))
			cv_wait(&is->is_maintenance_cv, &is->is_lock);

		/* Terminate supersedes reconnect. */
		if (is->is_terminating) {
			ISCSI_SESSION_UNLOCK(is);
			iscsi_maintenance_thread_terminate(is);
			kthread_exit();
			return;
		}

		if (is->is_reconnecting) {
			ISCSI_SESSION_UNLOCK(is);
			iscsi_maintenance_thread_reconnect(is);
			ISCSI_SESSION_LOCK(is);
			continue;
		}

		iscsi_session_send_postponed(is);
	}
	ISCSI_SESSION_UNLOCK(is);
}