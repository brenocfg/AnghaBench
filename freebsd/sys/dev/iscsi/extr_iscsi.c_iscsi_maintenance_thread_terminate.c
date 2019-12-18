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
struct iscsi_softc {int /*<<< orphan*/  sc_cv; int /*<<< orphan*/  sc_lock; int /*<<< orphan*/  sc_sessions; } ;
struct iscsi_session {int /*<<< orphan*/  is_login_cv; int /*<<< orphan*/  is_maintenance_cv; int /*<<< orphan*/  is_lock; int /*<<< orphan*/  is_conn; int /*<<< orphan*/  is_postponed; int /*<<< orphan*/  is_outstanding; int /*<<< orphan*/ * is_login_pdu; int /*<<< orphan*/  is_terminating; int /*<<< orphan*/  is_callout; struct iscsi_softc* is_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_SESSION_DEBUG (struct iscsi_session*,char*) ; 
 int /*<<< orphan*/  ISCSI_SESSION_LOCK (struct iscsi_session*) ; 
 int /*<<< orphan*/  ISCSI_SESSION_UNLOCK (struct iscsi_session*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_ISCSI ; 
 int /*<<< orphan*/  STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct iscsi_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct iscsi_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icl_conn_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icl_conn_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icl_pdu_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_next ; 
 int /*<<< orphan*/  iscsi_session_cleanup (struct iscsi_session*,int) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
iscsi_maintenance_thread_terminate(struct iscsi_session *is)
{
	struct iscsi_softc *sc;

	sc = is->is_softc;
	sx_xlock(&sc->sc_lock);
	TAILQ_REMOVE(&sc->sc_sessions, is, is_next);
	sx_xunlock(&sc->sc_lock);

	icl_conn_close(is->is_conn);
	callout_drain(&is->is_callout);

	ISCSI_SESSION_LOCK(is);

	KASSERT(is->is_terminating, ("is_terminating == false"));

#ifdef ICL_KERNEL_PROXY
	if (is->is_login_pdu != NULL) {
		icl_pdu_free(is->is_login_pdu);
		is->is_login_pdu = NULL;
	}
	cv_signal(&is->is_login_cv);
#endif

	iscsi_session_cleanup(is, true);

	KASSERT(TAILQ_EMPTY(&is->is_outstanding),
	    ("destroying session with active tasks"));
	KASSERT(STAILQ_EMPTY(&is->is_postponed),
	    ("destroying session with postponed PDUs"));

	ISCSI_SESSION_UNLOCK(is);

	icl_conn_free(is->is_conn);
	mtx_destroy(&is->is_lock);
	cv_destroy(&is->is_maintenance_cv);
#ifdef ICL_KERNEL_PROXY
	cv_destroy(&is->is_login_cv);
#endif

	ISCSI_SESSION_DEBUG(is, "terminated");
	free(is, M_ISCSI);

	/*
	 * The iscsi_unload() routine might be waiting.
	 */
	cv_signal(&sc->sc_cv);
}