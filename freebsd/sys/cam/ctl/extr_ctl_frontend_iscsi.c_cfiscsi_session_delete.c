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
struct cfiscsi_softc {int /*<<< orphan*/  sessions_cv; int /*<<< orphan*/  lock; int /*<<< orphan*/  sessions; } ;
struct cfiscsi_session {scalar_t__ cs_outstanding_ctl_pdus; int /*<<< orphan*/  cs_conn; int /*<<< orphan*/ * cs_target; int /*<<< orphan*/  cs_waiting_for_data_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_CFISCSI ; 
 int TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct cfiscsi_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfiscsi_session_unregister_initiator (struct cfiscsi_session*) ; 
 struct cfiscsi_softc cfiscsi_softc ; 
 int /*<<< orphan*/  cfiscsi_target_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cs_next ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct cfiscsi_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icl_conn_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icl_conn_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cfiscsi_session_delete(struct cfiscsi_session *cs)
{
	struct cfiscsi_softc *softc;

	softc = &cfiscsi_softc;

	KASSERT(cs->cs_outstanding_ctl_pdus == 0,
	    ("destroying session with outstanding CTL pdus"));
	KASSERT(TAILQ_EMPTY(&cs->cs_waiting_for_data_out),
	    ("destroying session with non-empty queue"));

	mtx_lock(&softc->lock);
	TAILQ_REMOVE(&softc->sessions, cs, cs_next);
	mtx_unlock(&softc->lock);

	cfiscsi_session_unregister_initiator(cs);
	if (cs->cs_target != NULL)
		cfiscsi_target_release(cs->cs_target);
	icl_conn_close(cs->cs_conn);
	icl_conn_free(cs->cs_conn);
	free(cs, M_CFISCSI);
	cv_signal(&softc->sessions_cv);
}