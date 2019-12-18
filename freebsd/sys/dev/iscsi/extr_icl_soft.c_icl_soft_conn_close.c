#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * sb_upcall; } ;
struct socket {TYPE_1__ so_rcv; TYPE_1__ so_snd; } ;
struct icl_pdu {int dummy; } ;
struct icl_conn {int ic_disconnecting; int /*<<< orphan*/  ic_to_send; struct icl_pdu* ic_receive_pdu; struct socket* ic_socket; int /*<<< orphan*/  ic_lock; int /*<<< orphan*/  ic_send_cv; int /*<<< orphan*/  ic_receive_cv; scalar_t__ ic_send_running; scalar_t__ ic_receive_running; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICL_CONN_LOCK (struct icl_conn*) ; 
 int /*<<< orphan*/  ICL_CONN_UNLOCK (struct icl_conn*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SOCKBUF_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  SOCKBUF_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  SO_RCV ; 
 int /*<<< orphan*/  SO_SND ; 
 int /*<<< orphan*/  STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct icl_pdu* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icl_soft_conn_pdu_free (struct icl_conn*,struct icl_pdu*) ; 
 int /*<<< orphan*/  ip_next ; 
 int /*<<< orphan*/  soclose (struct socket*) ; 
 int /*<<< orphan*/  soupcall_clear (struct socket*,int /*<<< orphan*/ ) ; 

void
icl_soft_conn_close(struct icl_conn *ic)
{
	struct icl_pdu *pdu;
	struct socket *so;

	ICL_CONN_LOCK(ic);

	/*
	 * Wake up the threads, so they can properly terminate.
	 */
	ic->ic_disconnecting = true;
	while (ic->ic_receive_running || ic->ic_send_running) {
		cv_signal(&ic->ic_receive_cv);
		cv_signal(&ic->ic_send_cv);
		cv_wait(&ic->ic_send_cv, ic->ic_lock);
	}

	/* Some other thread could close the connection same time. */
	so = ic->ic_socket;
	if (so == NULL) {
		ICL_CONN_UNLOCK(ic);
		return;
	}
	ic->ic_socket = NULL;

	/*
	 * Deregister socket upcalls.
	 */
	ICL_CONN_UNLOCK(ic);
	SOCKBUF_LOCK(&so->so_snd);
	if (so->so_snd.sb_upcall != NULL)
		soupcall_clear(so, SO_SND);
	SOCKBUF_UNLOCK(&so->so_snd);
	SOCKBUF_LOCK(&so->so_rcv);
	if (so->so_rcv.sb_upcall != NULL)
		soupcall_clear(so, SO_RCV);
	SOCKBUF_UNLOCK(&so->so_rcv);
	soclose(so);
	ICL_CONN_LOCK(ic);

	if (ic->ic_receive_pdu != NULL) {
		//ICL_DEBUG("freeing partially received PDU");
		icl_soft_conn_pdu_free(ic, ic->ic_receive_pdu);
		ic->ic_receive_pdu = NULL;
	}

	/*
	 * Remove any outstanding PDUs from the send queue.
	 */
	while (!STAILQ_EMPTY(&ic->ic_to_send)) {
		pdu = STAILQ_FIRST(&ic->ic_to_send);
		STAILQ_REMOVE_HEAD(&ic->ic_to_send, ip_next);
		icl_soft_conn_pdu_free(ic, pdu);
	}

	KASSERT(STAILQ_EMPTY(&ic->ic_to_send),
	    ("destroying session with non-empty send queue"));
	ICL_CONN_UNLOCK(ic);
}