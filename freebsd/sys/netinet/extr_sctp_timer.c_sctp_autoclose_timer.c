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
struct timeval {scalar_t__ tv_sec; } ;
struct sctp_association {int sctp_autoclose_ticks; struct sctp_nets* primary_destination; struct sctp_nets* alternate; int /*<<< orphan*/  sent_queue; int /*<<< orphan*/  send_queue; struct timeval time_last_sent; struct timeval time_last_rcvd; } ;
struct sctp_tcb {struct sctp_inpcb* sctp_ep; struct sctp_association asoc; } ;
struct sctp_nets {int dummy; } ;
struct sctp_inpcb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_GETTIME_TIMEVAL (struct timeval*) ; 
 scalar_t__ SCTP_GET_STATE (struct sctp_tcb*) ; 
 int /*<<< orphan*/  SCTP_OUTPUT_FROM_AUTOCLOSE_TMR ; 
 int /*<<< orphan*/  SCTP_PCB_FLAGS_AUTOCLOSE ; 
 int /*<<< orphan*/  SCTP_SET_STATE (struct sctp_tcb*,scalar_t__) ; 
 int /*<<< orphan*/  SCTP_SO_NOT_LOCKED ; 
 scalar_t__ SCTP_STATE_OPEN ; 
 scalar_t__ SCTP_STATE_SHUTDOWN_RECEIVED ; 
 scalar_t__ SCTP_STATE_SHUTDOWN_SENT ; 
 int /*<<< orphan*/  SCTP_STAT_DECR_GAUGE32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_TIMER_TYPE_AUTOCLOSE ; 
 int /*<<< orphan*/  SCTP_TIMER_TYPE_SHUTDOWN ; 
 int /*<<< orphan*/  SCTP_TIMER_TYPE_SHUTDOWNGUARD ; 
 int SEC_TO_TICKS (scalar_t__) ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_chunk_output (struct sctp_inpcb*,struct sctp_tcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sctp_is_feature_on (struct sctp_inpcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_send_shutdown (struct sctp_tcb*,struct sctp_nets*) ; 
 int /*<<< orphan*/  sctp_stop_timers_for_shutdown (struct sctp_tcb*) ; 
 int /*<<< orphan*/  sctp_timer_start (int /*<<< orphan*/ ,struct sctp_inpcb*,struct sctp_tcb*,struct sctp_nets*) ; 
 int /*<<< orphan*/  sctps_currestab ; 

void
sctp_autoclose_timer(struct sctp_inpcb *inp,
    struct sctp_tcb *stcb,
    struct sctp_nets *net)
{
	struct timeval tn, *tim_touse;
	struct sctp_association *asoc;
	int ticks_gone_by;

	(void)SCTP_GETTIME_TIMEVAL(&tn);
	if (stcb->asoc.sctp_autoclose_ticks &&
	    sctp_is_feature_on(inp, SCTP_PCB_FLAGS_AUTOCLOSE)) {
		/* Auto close is on */
		asoc = &stcb->asoc;
		/* pick the time to use */
		if (asoc->time_last_rcvd.tv_sec >
		    asoc->time_last_sent.tv_sec) {
			tim_touse = &asoc->time_last_rcvd;
		} else {
			tim_touse = &asoc->time_last_sent;
		}
		/* Now has long enough transpired to autoclose? */
		ticks_gone_by = SEC_TO_TICKS(tn.tv_sec - tim_touse->tv_sec);
		if ((ticks_gone_by > 0) &&
		    (ticks_gone_by >= (int)asoc->sctp_autoclose_ticks)) {
			/*
			 * autoclose time has hit, call the output routine,
			 * which should do nothing just to be SURE we don't
			 * have hanging data. We can then safely check the
			 * queues and know that we are clear to send
			 * shutdown
			 */
			sctp_chunk_output(inp, stcb, SCTP_OUTPUT_FROM_AUTOCLOSE_TMR, SCTP_SO_NOT_LOCKED);
			/* Are we clean? */
			if (TAILQ_EMPTY(&asoc->send_queue) &&
			    TAILQ_EMPTY(&asoc->sent_queue)) {
				/*
				 * there is nothing queued to send, so I'm
				 * done...
				 */
				if (SCTP_GET_STATE(stcb) != SCTP_STATE_SHUTDOWN_SENT) {
					/* only send SHUTDOWN 1st time thru */
					struct sctp_nets *netp;

					if ((SCTP_GET_STATE(stcb) == SCTP_STATE_OPEN) ||
					    (SCTP_GET_STATE(stcb) == SCTP_STATE_SHUTDOWN_RECEIVED)) {
						SCTP_STAT_DECR_GAUGE32(sctps_currestab);
					}
					SCTP_SET_STATE(stcb, SCTP_STATE_SHUTDOWN_SENT);
					sctp_stop_timers_for_shutdown(stcb);
					if (stcb->asoc.alternate) {
						netp = stcb->asoc.alternate;
					} else {
						netp = stcb->asoc.primary_destination;
					}
					sctp_send_shutdown(stcb, netp);
					sctp_timer_start(SCTP_TIMER_TYPE_SHUTDOWN,
					    stcb->sctp_ep, stcb,
					    netp);
					sctp_timer_start(SCTP_TIMER_TYPE_SHUTDOWNGUARD,
					    stcb->sctp_ep, stcb,
					    netp);
				}
			}
		} else {
			/*
			 * No auto close at this time, reset t-o to check
			 * later
			 */
			int tmp;

			/* fool the timer startup to use the time left */
			tmp = asoc->sctp_autoclose_ticks;
			asoc->sctp_autoclose_ticks -= ticks_gone_by;
			sctp_timer_start(SCTP_TIMER_TYPE_AUTOCLOSE, inp, stcb,
			    net);
			/* restore the real tick value */
			asoc->sctp_autoclose_ticks = tmp;
		}
	}
}