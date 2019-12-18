#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  sb_state; } ;
struct socket {int so_state; TYPE_4__ so_rcv; scalar_t__ so_pcb; } ;
struct TYPE_6__ {scalar_t__ (* sctp_ss_is_user_msgs_incomplete ) (struct sctp_tcb*,struct sctp_association*) ;} ;
struct sctp_association {int state; scalar_t__ stream_queue_cnt; int /*<<< orphan*/  sent_queue; int /*<<< orphan*/  send_queue; TYPE_1__ ss_functions; struct sctp_nets* primary_destination; struct sctp_nets* alternate; } ;
struct sctp_tcb {TYPE_2__* sctp_ep; struct sctp_association asoc; } ;
struct sctp_nets {int dummy; } ;
struct sctp_inpcb {int sctp_flags; int /*<<< orphan*/  sctp_asoc_list; } ;
struct mbuf {int dummy; } ;
struct TYPE_7__ {scalar_t__ last_abort_code; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTCONN ; 
 int EOPNOTSUPP ; 
 struct sctp_tcb* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SBS_CANTRCVMORE ; 
 int /*<<< orphan*/  SCTP_ADD_SUBSTATE (struct sctp_tcb*,int) ; 
 int /*<<< orphan*/  SCTP_CAUSE_USER_INITIATED_ABT ; 
 scalar_t__ SCTP_FROM_SCTP_USRREQ ; 
 scalar_t__ SCTP_GET_STATE (struct sctp_tcb*) ; 
 int /*<<< orphan*/  SCTP_INP_RLOCK (struct sctp_inpcb*) ; 
 int /*<<< orphan*/  SCTP_INP_RUNLOCK (struct sctp_inpcb*) ; 
 scalar_t__ SCTP_LOC_6 ; 
 int /*<<< orphan*/  SCTP_LTRACE_ERR_RET (struct sctp_inpcb*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  SCTP_OUTPUT_FROM_CLOSING ; 
 int SCTP_PCB_FLAGS_IN_TCPPOOL ; 
 int SCTP_PCB_FLAGS_TCPTYPE ; 
 int /*<<< orphan*/  SCTP_SET_STATE (struct sctp_tcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_SO_LOCKED ; 
 int SCTP_STATE_ABOUT_TO_BE_FREED ; 
 scalar_t__ SCTP_STATE_COOKIE_ECHOED ; 
 scalar_t__ SCTP_STATE_COOKIE_WAIT ; 
 scalar_t__ SCTP_STATE_OPEN ; 
 int SCTP_STATE_PARTIAL_MSG_LEFT ; 
 int SCTP_STATE_SHUTDOWN_PENDING ; 
 int /*<<< orphan*/  SCTP_STATE_SHUTDOWN_SENT ; 
 int /*<<< orphan*/  SCTP_STAT_DECR_GAUGE32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_TCB_LOCK (struct sctp_tcb*) ; 
 int /*<<< orphan*/  SCTP_TCB_UNLOCK (struct sctp_tcb*) ; 
 int /*<<< orphan*/  SCTP_TIMER_TYPE_SHUTDOWN ; 
 int /*<<< orphan*/  SCTP_TIMER_TYPE_SHUTDOWNGUARD ; 
 int /*<<< orphan*/  SOCKBUF_LOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  SOCKBUF_UNLOCK (TYPE_4__*) ; 
 int SS_ISCONNECTED ; 
 int SS_ISCONNECTING ; 
 int SS_ISDISCONNECTING ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_abort_an_association (TYPE_2__*,struct sctp_tcb*,struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_chunk_output (struct sctp_inpcb*,struct sctp_tcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mbuf* sctp_generate_cause (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sctp_send_shutdown (struct sctp_tcb*,struct sctp_nets*) ; 
 int /*<<< orphan*/  sctp_stop_timers_for_shutdown (struct sctp_tcb*) ; 
 int /*<<< orphan*/  sctp_timer_start (int /*<<< orphan*/ ,TYPE_2__*,struct sctp_tcb*,struct sctp_nets*) ; 
 int /*<<< orphan*/  sctps_currestab ; 
 int /*<<< orphan*/  socantsendmore (struct socket*) ; 
 scalar_t__ stub1 (struct sctp_tcb*,struct sctp_association*) ; 
 scalar_t__ stub2 (struct sctp_tcb*,struct sctp_association*) ; 

int
sctp_shutdown(struct socket *so)
{
	struct sctp_inpcb *inp;

	inp = (struct sctp_inpcb *)so->so_pcb;
	if (inp == NULL) {
		SCTP_LTRACE_ERR_RET(inp, NULL, NULL, SCTP_FROM_SCTP_USRREQ, EINVAL);
		return (EINVAL);
	}
	SCTP_INP_RLOCK(inp);
	/* For UDP model this is a invalid call */
	if (!((inp->sctp_flags & SCTP_PCB_FLAGS_TCPTYPE) ||
	    (inp->sctp_flags & SCTP_PCB_FLAGS_IN_TCPPOOL))) {
		/* Restore the flags that the soshutdown took away. */
		SOCKBUF_LOCK(&so->so_rcv);
		so->so_rcv.sb_state &= ~SBS_CANTRCVMORE;
		SOCKBUF_UNLOCK(&so->so_rcv);
		/* This proc will wakeup for read and do nothing (I hope) */
		SCTP_INP_RUNLOCK(inp);
		SCTP_LTRACE_ERR_RET(inp, NULL, NULL, SCTP_FROM_SCTP_USRREQ, EOPNOTSUPP);
		return (EOPNOTSUPP);
	} else {
		/*
		 * Ok, if we reach here its the TCP model and it is either a
		 * SHUT_WR or SHUT_RDWR. This means we put the shutdown flag
		 * against it.
		 */
		struct sctp_tcb *stcb;
		struct sctp_association *asoc;
		struct sctp_nets *netp;

		if ((so->so_state &
		    (SS_ISCONNECTED | SS_ISCONNECTING | SS_ISDISCONNECTING)) == 0) {
			SCTP_INP_RUNLOCK(inp);
			return (ENOTCONN);
		}
		socantsendmore(so);

		stcb = LIST_FIRST(&inp->sctp_asoc_list);
		if (stcb == NULL) {
			/*
			 * Ok, we hit the case that the shutdown call was
			 * made after an abort or something. Nothing to do
			 * now.
			 */
			SCTP_INP_RUNLOCK(inp);
			return (0);
		}
		SCTP_TCB_LOCK(stcb);
		asoc = &stcb->asoc;
		if (asoc->state & SCTP_STATE_ABOUT_TO_BE_FREED) {
			SCTP_TCB_UNLOCK(stcb);
			SCTP_INP_RUNLOCK(inp);
			return (0);
		}
		if ((SCTP_GET_STATE(stcb) != SCTP_STATE_COOKIE_WAIT) &&
		    (SCTP_GET_STATE(stcb) != SCTP_STATE_COOKIE_ECHOED) &&
		    (SCTP_GET_STATE(stcb) != SCTP_STATE_OPEN)) {
			/*
			 * If we are not in or before ESTABLISHED, there is
			 * no protocol action required.
			 */
			SCTP_TCB_UNLOCK(stcb);
			SCTP_INP_RUNLOCK(inp);
			return (0);
		}
		if (stcb->asoc.alternate) {
			netp = stcb->asoc.alternate;
		} else {
			netp = stcb->asoc.primary_destination;
		}
		if ((SCTP_GET_STATE(stcb) == SCTP_STATE_OPEN) &&
		    TAILQ_EMPTY(&asoc->send_queue) &&
		    TAILQ_EMPTY(&asoc->sent_queue) &&
		    (asoc->stream_queue_cnt == 0)) {
			if ((*asoc->ss_functions.sctp_ss_is_user_msgs_incomplete) (stcb, asoc)) {
				goto abort_anyway;
			}
			/* there is nothing queued to send, so I'm done... */
			SCTP_STAT_DECR_GAUGE32(sctps_currestab);
			SCTP_SET_STATE(stcb, SCTP_STATE_SHUTDOWN_SENT);
			sctp_stop_timers_for_shutdown(stcb);
			sctp_send_shutdown(stcb, netp);
			sctp_timer_start(SCTP_TIMER_TYPE_SHUTDOWN,
			    stcb->sctp_ep, stcb, netp);
		} else {
			/*
			 * We still got (or just got) data to send, so set
			 * SHUTDOWN_PENDING.
			 */
			SCTP_ADD_SUBSTATE(stcb, SCTP_STATE_SHUTDOWN_PENDING);
			if ((*asoc->ss_functions.sctp_ss_is_user_msgs_incomplete) (stcb, asoc)) {
				SCTP_ADD_SUBSTATE(stcb, SCTP_STATE_PARTIAL_MSG_LEFT);
			}
			if (TAILQ_EMPTY(&asoc->send_queue) &&
			    TAILQ_EMPTY(&asoc->sent_queue) &&
			    (asoc->state & SCTP_STATE_PARTIAL_MSG_LEFT)) {
				struct mbuf *op_err;

		abort_anyway:
				op_err = sctp_generate_cause(SCTP_CAUSE_USER_INITIATED_ABT, "");
				stcb->sctp_ep->last_abort_code = SCTP_FROM_SCTP_USRREQ + SCTP_LOC_6;
				SCTP_INP_RUNLOCK(inp);
				sctp_abort_an_association(stcb->sctp_ep, stcb,
				    op_err, SCTP_SO_LOCKED);
				return (0);
			}
		}
		sctp_timer_start(SCTP_TIMER_TYPE_SHUTDOWNGUARD, stcb->sctp_ep, stcb, netp);
		/*
		 * XXX: Why do this in the case where we have still data
		 * queued?
		 */
		sctp_chunk_output(inp, stcb, SCTP_OUTPUT_FROM_CLOSING, SCTP_SO_LOCKED);
		SCTP_TCB_UNLOCK(stcb);
		SCTP_INP_RUNLOCK(inp);
		return (0);
	}
}