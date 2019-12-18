#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct socket {int dummy; } ;
struct sctp_association {int state; int /*<<< orphan*/  sent_queue; int /*<<< orphan*/  send_queue; int /*<<< orphan*/  time_entered; int /*<<< orphan*/  refcnt; TYPE_2__* control_pdapi; struct sctp_stream_in* strmin; } ;
struct sctp_tcb {int /*<<< orphan*/  sctp_ep; scalar_t__ sctp_socket; struct sctp_association asoc; } ;
struct sctp_stream_in {int /*<<< orphan*/  inqueue; int /*<<< orphan*/  uno_inqueue; } ;
struct TYPE_4__ {int /*<<< orphan*/  chunk_length; } ;
struct sctp_shutdown_chunk {TYPE_1__ ch; } ;
struct sctp_nets {int dummy; } ;
struct TYPE_5__ {scalar_t__ on_strm_q; size_t sinfo_stream; int end_added; int pdapi_aborted; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTPDBG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SCTP_DEBUG_INPUT2 ; 
 scalar_t__ SCTP_FROM_SCTP_INPUT ; 
 int /*<<< orphan*/  SCTP_GETTIME_TIMEVAL (int /*<<< orphan*/ *) ; 
 int SCTP_GET_STATE (struct sctp_tcb*) ; 
 int /*<<< orphan*/  SCTP_INP_READ_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_INP_READ_UNLOCK (int /*<<< orphan*/ ) ; 
 struct socket* SCTP_INP_SO (int /*<<< orphan*/ ) ; 
 scalar_t__ SCTP_LOC_9 ; 
 int /*<<< orphan*/  SCTP_NOTIFY_PEER_SHUTDOWN ; 
 scalar_t__ SCTP_ON_ORDERED ; 
 scalar_t__ SCTP_ON_UNORDERED ; 
 int /*<<< orphan*/  SCTP_SET_STATE (struct sctp_tcb*,int) ; 
 int /*<<< orphan*/  SCTP_SOCKET_LOCK (struct socket*,int) ; 
 int /*<<< orphan*/  SCTP_SOCKET_UNLOCK (struct socket*,int) ; 
 int /*<<< orphan*/  SCTP_SO_NOT_LOCKED ; 
 int SCTP_STATE_CLOSED_SOCKET ; 
 int SCTP_STATE_COOKIE_ECHOED ; 
 int SCTP_STATE_COOKIE_WAIT ; 
 int SCTP_STATE_OPEN ; 
 int SCTP_STATE_SHUTDOWN_ACK_SENT ; 
 int SCTP_STATE_SHUTDOWN_RECEIVED ; 
 int SCTP_STATE_SHUTDOWN_SENT ; 
 int /*<<< orphan*/  SCTP_STAT_DECR_GAUGE32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_TCB_LOCK (struct sctp_tcb*) ; 
 int /*<<< orphan*/  SCTP_TCB_UNLOCK (struct sctp_tcb*) ; 
 int /*<<< orphan*/  SCTP_TIMER_TYPE_SHUTDOWN ; 
 int /*<<< orphan*/  SCTP_TIMER_TYPE_SHUTDOWNACK ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_subtract_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  next_instrm ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,TYPE_2__*,scalar_t__) ; 
 int sctp_is_there_unsent_data (struct sctp_tcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_send_shutdown_ack (struct sctp_tcb*,struct sctp_nets*) ; 
 int /*<<< orphan*/  sctp_sorwakeup (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sctp_stop_timers_for_shutdown (struct sctp_tcb*) ; 
 int /*<<< orphan*/  sctp_timer_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sctp_tcb*,struct sctp_nets*) ; 
 int /*<<< orphan*/  sctp_timer_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sctp_tcb*,struct sctp_nets*,scalar_t__) ; 
 int /*<<< orphan*/  sctp_ulp_notify (int /*<<< orphan*/ ,struct sctp_tcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_update_acked (struct sctp_tcb*,struct sctp_shutdown_chunk*,int*) ; 
 int /*<<< orphan*/  sctps_currestab ; 

__attribute__((used)) static void
sctp_handle_shutdown(struct sctp_shutdown_chunk *cp,
    struct sctp_tcb *stcb, struct sctp_nets *net, int *abort_flag)
{
	struct sctp_association *asoc;
	int some_on_streamwheel;
	int old_state;
#if defined(__APPLE__) || defined(SCTP_SO_LOCK_TESTING)
	struct socket *so;
#endif

	SCTPDBG(SCTP_DEBUG_INPUT2,
	    "sctp_handle_shutdown: handling SHUTDOWN\n");
	if (stcb == NULL)
		return;
	asoc = &stcb->asoc;
	if ((SCTP_GET_STATE(stcb) == SCTP_STATE_COOKIE_WAIT) ||
	    (SCTP_GET_STATE(stcb) == SCTP_STATE_COOKIE_ECHOED)) {
		return;
	}
	if (ntohs(cp->ch.chunk_length) != sizeof(struct sctp_shutdown_chunk)) {
		/* Shutdown NOT the expected size */
		return;
	}
	old_state = SCTP_GET_STATE(stcb);
	sctp_update_acked(stcb, cp, abort_flag);
	if (*abort_flag) {
		return;
	}
	if (asoc->control_pdapi) {
		/*
		 * With a normal shutdown we assume the end of last record.
		 */
		SCTP_INP_READ_LOCK(stcb->sctp_ep);
		if (asoc->control_pdapi->on_strm_q) {
			struct sctp_stream_in *strm;

			strm = &asoc->strmin[asoc->control_pdapi->sinfo_stream];
			if (asoc->control_pdapi->on_strm_q == SCTP_ON_UNORDERED) {
				/* Unordered */
				TAILQ_REMOVE(&strm->uno_inqueue, asoc->control_pdapi, next_instrm);
				asoc->control_pdapi->on_strm_q = 0;
			} else if (asoc->control_pdapi->on_strm_q == SCTP_ON_ORDERED) {
				/* Ordered */
				TAILQ_REMOVE(&strm->inqueue, asoc->control_pdapi, next_instrm);
				asoc->control_pdapi->on_strm_q = 0;
#ifdef INVARIANTS
			} else {
				panic("Unknown state on ctrl:%p on_strm_q:%d",
				    asoc->control_pdapi,
				    asoc->control_pdapi->on_strm_q);
#endif
			}
		}
		asoc->control_pdapi->end_added = 1;
		asoc->control_pdapi->pdapi_aborted = 1;
		asoc->control_pdapi = NULL;
		SCTP_INP_READ_UNLOCK(stcb->sctp_ep);
#if defined(__APPLE__) || defined(SCTP_SO_LOCK_TESTING)
		so = SCTP_INP_SO(stcb->sctp_ep);
		atomic_add_int(&stcb->asoc.refcnt, 1);
		SCTP_TCB_UNLOCK(stcb);
		SCTP_SOCKET_LOCK(so, 1);
		SCTP_TCB_LOCK(stcb);
		atomic_subtract_int(&stcb->asoc.refcnt, 1);
		if (stcb->asoc.state & SCTP_STATE_CLOSED_SOCKET) {
			/* assoc was freed while we were unlocked */
			SCTP_SOCKET_UNLOCK(so, 1);
			return;
		}
#endif
		if (stcb->sctp_socket) {
			sctp_sorwakeup(stcb->sctp_ep, stcb->sctp_socket);
		}
#if defined(__APPLE__) || defined(SCTP_SO_LOCK_TESTING)
		SCTP_SOCKET_UNLOCK(so, 1);
#endif
	}
	/* goto SHUTDOWN_RECEIVED state to block new requests */
	if (stcb->sctp_socket) {
		if ((SCTP_GET_STATE(stcb) != SCTP_STATE_SHUTDOWN_RECEIVED) &&
		    (SCTP_GET_STATE(stcb) != SCTP_STATE_SHUTDOWN_ACK_SENT) &&
		    (SCTP_GET_STATE(stcb) != SCTP_STATE_SHUTDOWN_SENT)) {
			SCTP_SET_STATE(stcb, SCTP_STATE_SHUTDOWN_RECEIVED);
			/*
			 * notify upper layer that peer has initiated a
			 * shutdown
			 */
			sctp_ulp_notify(SCTP_NOTIFY_PEER_SHUTDOWN, stcb, 0, NULL, SCTP_SO_NOT_LOCKED);

			/* reset time */
			(void)SCTP_GETTIME_TIMEVAL(&asoc->time_entered);
		}
	}
	if (SCTP_GET_STATE(stcb) == SCTP_STATE_SHUTDOWN_SENT) {
		/*
		 * stop the shutdown timer, since we WILL move to
		 * SHUTDOWN-ACK-SENT.
		 */
		sctp_timer_stop(SCTP_TIMER_TYPE_SHUTDOWN, stcb->sctp_ep, stcb,
		    net, SCTP_FROM_SCTP_INPUT + SCTP_LOC_9);
	}
	/* Now is there unsent data on a stream somewhere? */
	some_on_streamwheel = sctp_is_there_unsent_data(stcb, SCTP_SO_NOT_LOCKED);

	if (!TAILQ_EMPTY(&asoc->send_queue) ||
	    !TAILQ_EMPTY(&asoc->sent_queue) ||
	    some_on_streamwheel) {
		/* By returning we will push more data out */
		return;
	} else {
		/* no outstanding data to send, so move on... */
		/* send SHUTDOWN-ACK */
		/* move to SHUTDOWN-ACK-SENT state */
		if ((SCTP_GET_STATE(stcb) == SCTP_STATE_OPEN) ||
		    (SCTP_GET_STATE(stcb) == SCTP_STATE_SHUTDOWN_RECEIVED)) {
			SCTP_STAT_DECR_GAUGE32(sctps_currestab);
		}
		if (SCTP_GET_STATE(stcb) != SCTP_STATE_SHUTDOWN_ACK_SENT) {
			SCTP_SET_STATE(stcb, SCTP_STATE_SHUTDOWN_ACK_SENT);
			sctp_stop_timers_for_shutdown(stcb);
			sctp_send_shutdown_ack(stcb, net);
			sctp_timer_start(SCTP_TIMER_TYPE_SHUTDOWNACK,
			    stcb->sctp_ep, stcb, net);
		} else if (old_state == SCTP_STATE_SHUTDOWN_ACK_SENT) {
			sctp_send_shutdown_ack(stcb, net);
		}
	}
}