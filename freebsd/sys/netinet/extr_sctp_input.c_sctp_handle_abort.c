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
typedef  int uint16_t ;
struct socket {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  refcnt; } ;
struct sctp_tcb {int /*<<< orphan*/  sctp_ep; TYPE_2__ asoc; } ;
struct sctp_nets {int dummy; } ;
struct sctp_error_cause {int /*<<< orphan*/  code; } ;
struct sctp_chunkhdr {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  chunk_flags; int /*<<< orphan*/  chunk_length; } ;
struct sctp_abort_chunk {TYPE_1__ ch; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTPDBG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  SCTP_ADD_SUBSTATE (struct sctp_tcb*,int /*<<< orphan*/ ) ; 
 int SCTP_CAUSE_NAT_COLLIDING_STATE ; 
 int SCTP_CAUSE_NAT_MISSING_STATE ; 
 int /*<<< orphan*/  SCTP_DEBUG_INPUT2 ; 
 scalar_t__ SCTP_FROM_SCTP_INPUT ; 
 scalar_t__ SCTP_GET_STATE (struct sctp_tcb*) ; 
 struct socket* SCTP_INP_SO (int /*<<< orphan*/ ) ; 
 scalar_t__ SCTP_LOC_7 ; 
 scalar_t__ SCTP_LOC_8 ; 
 int /*<<< orphan*/  SCTP_NORMAL_PROC ; 
 int /*<<< orphan*/  SCTP_SOCKET_LOCK (struct socket*,int) ; 
 int /*<<< orphan*/  SCTP_SOCKET_UNLOCK (struct socket*,int) ; 
 int /*<<< orphan*/  SCTP_SO_NOT_LOCKED ; 
 scalar_t__ SCTP_STATE_OPEN ; 
 scalar_t__ SCTP_STATE_SHUTDOWN_RECEIVED ; 
 int /*<<< orphan*/  SCTP_STATE_WAS_ABORTED ; 
 int /*<<< orphan*/  SCTP_STAT_DECR_GAUGE32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_STAT_INCR_COUNTER32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_TCB_LOCK (struct sctp_tcb*) ; 
 int /*<<< orphan*/  SCTP_TCB_UNLOCK (struct sctp_tcb*) ; 
 int /*<<< orphan*/  SCTP_TIMER_TYPE_RECV ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_subtract_int (int /*<<< orphan*/ *,int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_abort_notification (struct sctp_tcb*,int,int,struct sctp_abort_chunk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_free_assoc (int /*<<< orphan*/ ,struct sctp_tcb*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ sctp_handle_nat_colliding_state (struct sctp_tcb*) ; 
 scalar_t__ sctp_handle_nat_missing_state (struct sctp_tcb*,struct sctp_nets*) ; 
 int /*<<< orphan*/  sctp_print_out_track_log (struct sctp_tcb*) ; 
 int /*<<< orphan*/  sctp_timer_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sctp_tcb*,struct sctp_nets*,scalar_t__) ; 
 int /*<<< orphan*/  sctps_aborted ; 
 int /*<<< orphan*/  sctps_currestab ; 

__attribute__((used)) static int
sctp_handle_abort(struct sctp_abort_chunk *abort,
    struct sctp_tcb *stcb, struct sctp_nets *net)
{
#if defined(__APPLE__) || defined(SCTP_SO_LOCK_TESTING)
	struct socket *so;
#endif
	uint16_t len;
	uint16_t error;

	SCTPDBG(SCTP_DEBUG_INPUT2, "sctp_handle_abort: handling ABORT\n");
	if (stcb == NULL)
		return (0);

	len = ntohs(abort->ch.chunk_length);
	if (len >= sizeof(struct sctp_chunkhdr) + sizeof(struct sctp_error_cause)) {
		/*
		 * Need to check the cause codes for our two magic nat
		 * aborts which don't kill the assoc necessarily.
		 */
		struct sctp_error_cause *cause;

		cause = (struct sctp_error_cause *)(abort + 1);
		error = ntohs(cause->code);
		if (error == SCTP_CAUSE_NAT_COLLIDING_STATE) {
			SCTPDBG(SCTP_DEBUG_INPUT2, "Received Colliding state abort flags:%x\n",
			    abort->ch.chunk_flags);
			if (sctp_handle_nat_colliding_state(stcb)) {
				return (0);
			}
		} else if (error == SCTP_CAUSE_NAT_MISSING_STATE) {
			SCTPDBG(SCTP_DEBUG_INPUT2, "Received missing state abort flags:%x\n",
			    abort->ch.chunk_flags);
			if (sctp_handle_nat_missing_state(stcb, net)) {
				return (0);
			}
		}
	} else {
		error = 0;
	}
	/* stop any receive timers */
	sctp_timer_stop(SCTP_TIMER_TYPE_RECV, stcb->sctp_ep, stcb, net,
	    SCTP_FROM_SCTP_INPUT + SCTP_LOC_7);
	/* notify user of the abort and clean up... */
	sctp_abort_notification(stcb, 1, error, abort, SCTP_SO_NOT_LOCKED);
	/* free the tcb */
	SCTP_STAT_INCR_COUNTER32(sctps_aborted);
	if ((SCTP_GET_STATE(stcb) == SCTP_STATE_OPEN) ||
	    (SCTP_GET_STATE(stcb) == SCTP_STATE_SHUTDOWN_RECEIVED)) {
		SCTP_STAT_DECR_GAUGE32(sctps_currestab);
	}
#ifdef SCTP_ASOCLOG_OF_TSNS
	sctp_print_out_track_log(stcb);
#endif
#if defined(__APPLE__) || defined(SCTP_SO_LOCK_TESTING)
	so = SCTP_INP_SO(stcb->sctp_ep);
	atomic_add_int(&stcb->asoc.refcnt, 1);
	SCTP_TCB_UNLOCK(stcb);
	SCTP_SOCKET_LOCK(so, 1);
	SCTP_TCB_LOCK(stcb);
	atomic_subtract_int(&stcb->asoc.refcnt, 1);
#endif
	SCTP_ADD_SUBSTATE(stcb, SCTP_STATE_WAS_ABORTED);
	(void)sctp_free_assoc(stcb->sctp_ep, stcb, SCTP_NORMAL_PROC,
	    SCTP_FROM_SCTP_INPUT + SCTP_LOC_8);
#if defined(__APPLE__) || defined(SCTP_SO_LOCK_TESTING)
	SCTP_SOCKET_UNLOCK(so, 1);
#endif
	SCTPDBG(SCTP_DEBUG_INPUT2, "sctp_handle_abort: finished\n");
	return (1);
}