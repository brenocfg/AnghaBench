#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ isc_enable; scalar_t__ isc_discovery; } ;
struct iscsi_session {int is_connected; int is_reconnecting; int is_login_phase; int is_waiting_for_iscsid; TYPE_2__* is_softc; scalar_t__ is_timeout; int /*<<< orphan*/  is_reason; TYPE_1__ is_conf; int /*<<< orphan*/  is_postponed; int /*<<< orphan*/  is_outstanding; int /*<<< orphan*/  is_login_cv; int /*<<< orphan*/ * is_login_pdu; int /*<<< orphan*/  is_conn; } ;
struct TYPE_4__ {int /*<<< orphan*/  sc_cv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_SESSION_DEBUG (struct iscsi_session*,char*) ; 
 int /*<<< orphan*/  ISCSI_SESSION_LOCK (struct iscsi_session*) ; 
 int /*<<< orphan*/  ISCSI_SESSION_UNLOCK (struct iscsi_session*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 scalar_t__ fail_on_disconnection ; 
 int /*<<< orphan*/  icl_conn_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icl_pdu_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iscsi_session_cleanup (struct iscsi_session*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
iscsi_maintenance_thread_reconnect(struct iscsi_session *is)
{

	icl_conn_close(is->is_conn);

	ISCSI_SESSION_LOCK(is);

	is->is_connected = false;
	is->is_reconnecting = false;
	is->is_login_phase = false;

#ifdef ICL_KERNEL_PROXY
	if (is->is_login_pdu != NULL) {
		icl_pdu_free(is->is_login_pdu);
		is->is_login_pdu = NULL;
	}
	cv_signal(&is->is_login_cv);
#endif
 
	if (fail_on_disconnection) {
		ISCSI_SESSION_DEBUG(is, "connection failed, destroying devices");
		iscsi_session_cleanup(is, true);
	} else {
		iscsi_session_cleanup(is, false);
	}
 
	KASSERT(TAILQ_EMPTY(&is->is_outstanding),
	    ("destroying session with active tasks"));
	KASSERT(STAILQ_EMPTY(&is->is_postponed),
	    ("destroying session with postponed PDUs"));

	if (is->is_conf.isc_enable == 0 && is->is_conf.isc_discovery == 0) {
		ISCSI_SESSION_UNLOCK(is);
		return;
	}

	/*
	 * Request immediate reconnection from iscsid(8).
	 */
	//ISCSI_SESSION_DEBUG(is, "waking up iscsid(8)");
	is->is_waiting_for_iscsid = true;
	strlcpy(is->is_reason, "Waiting for iscsid(8)", sizeof(is->is_reason));
	is->is_timeout = 0;
	ISCSI_SESSION_UNLOCK(is);
	cv_signal(&is->is_softc->sc_cv);
}