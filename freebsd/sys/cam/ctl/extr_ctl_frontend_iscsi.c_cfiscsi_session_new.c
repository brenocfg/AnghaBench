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
struct cfiscsi_softc {int /*<<< orphan*/  lock; int /*<<< orphan*/  sessions; scalar_t__ last_session_id; } ;
struct cfiscsi_session {int cs_ctl_initid; int cs_handoff_in_progress; int /*<<< orphan*/  cs_callout; scalar_t__ cs_id; TYPE_1__* cs_conn; int /*<<< orphan*/  cs_lock; int /*<<< orphan*/  cs_login_cv; int /*<<< orphan*/  cs_maintenance_cv; int /*<<< orphan*/  cs_waiting_for_data_out; int /*<<< orphan*/  cs_outstanding_ctl_pdus; } ;
struct TYPE_2__ {struct cfiscsi_session* ic_prv0; int /*<<< orphan*/  ic_error; int /*<<< orphan*/  ic_receive; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFISCSI_SESSION_WARN (struct cfiscsi_session*,char*,int) ; 
 int /*<<< orphan*/  CFISCSI_WARN (char*) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_CFISCSI ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct cfiscsi_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct cfiscsi_session*) ; 
 int /*<<< orphan*/  cfiscsi_callout ; 
 int /*<<< orphan*/  cfiscsi_error_callback ; 
 int /*<<< orphan*/  cfiscsi_maintenance_thread ; 
 int /*<<< orphan*/  cfiscsi_receive_callback ; 
 int /*<<< orphan*/  cs_next ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free (struct cfiscsi_session*,int /*<<< orphan*/ ) ; 
 int hz ; 
 TYPE_1__* icl_new_conn (char const*,int,char*,int /*<<< orphan*/ *) ; 
 int kthread_add (int /*<<< orphan*/ ,struct cfiscsi_session*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct cfiscsi_session* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cfiscsi_session *
cfiscsi_session_new(struct cfiscsi_softc *softc, const char *offload)
{
	struct cfiscsi_session *cs;
	int error;

	cs = malloc(sizeof(*cs), M_CFISCSI, M_NOWAIT | M_ZERO);
	if (cs == NULL) {
		CFISCSI_WARN("malloc failed");
		return (NULL);
	}
	cs->cs_ctl_initid = -1;

	refcount_init(&cs->cs_outstanding_ctl_pdus, 0);
	TAILQ_INIT(&cs->cs_waiting_for_data_out);
	mtx_init(&cs->cs_lock, "cfiscsi_lock", NULL, MTX_DEF);
	cv_init(&cs->cs_maintenance_cv, "cfiscsi_mt");
#ifdef ICL_KERNEL_PROXY
	cv_init(&cs->cs_login_cv, "cfiscsi_login");
#endif

	/*
	 * The purpose of this is to avoid racing with session shutdown.
	 * Otherwise we could have the maintenance thread call icl_conn_close()
	 * before we call icl_conn_handoff().
	 */
	cs->cs_handoff_in_progress = true;

	cs->cs_conn = icl_new_conn(offload, false, "cfiscsi", &cs->cs_lock);
	if (cs->cs_conn == NULL) {
		free(cs, M_CFISCSI);
		return (NULL);
	}
	cs->cs_conn->ic_receive = cfiscsi_receive_callback;
	cs->cs_conn->ic_error = cfiscsi_error_callback;
	cs->cs_conn->ic_prv0 = cs;

	error = kthread_add(cfiscsi_maintenance_thread, cs, NULL, NULL, 0, 0, "cfiscsimt");
	if (error != 0) {
		CFISCSI_SESSION_WARN(cs, "kthread_add(9) failed with error %d", error);
		free(cs, M_CFISCSI);
		return (NULL);
	}

	mtx_lock(&softc->lock);
	cs->cs_id = ++softc->last_session_id;
	TAILQ_INSERT_TAIL(&softc->sessions, cs, cs_next);
	mtx_unlock(&softc->lock);

	/*
	 * Start pinging the initiator.
	 */
	callout_init(&cs->cs_callout, 1);
	callout_reset(&cs->cs_callout, 1 * hz, cfiscsi_callout, cs);

	return (cs);
}