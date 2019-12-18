#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct socket {int dummy; } ;
struct TYPE_9__ {int state; scalar_t__ my_last_reported_rwnd; scalar_t__ refcnt; } ;
struct sctp_tcb {TYPE_3__ asoc; TYPE_1__* sctp_ep; scalar_t__ freed_by_sorcv_sincelast; struct socket* sctp_socket; } ;
struct TYPE_8__ {int sctp_flags; } ;

/* Variables and functions */
 scalar_t__ SCTP_FROM_SCTPUTIL ; 
 scalar_t__ SCTP_GET_STATE (struct sctp_tcb*) ; 
 int /*<<< orphan*/  SCTP_INP_DECR_REF (TYPE_1__*) ; 
 int /*<<< orphan*/  SCTP_INP_INCR_REF (TYPE_1__*) ; 
 int /*<<< orphan*/  SCTP_INP_READ_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  SCTP_INP_READ_UNLOCK (TYPE_1__*) ; 
 scalar_t__ SCTP_LOC_6 ; 
 int /*<<< orphan*/  SCTP_OUTPUT_FROM_USR_RCVD ; 
 int SCTP_PCB_FLAGS_SOCKET_ALLGONE ; 
 int SCTP_PCB_FLAGS_SOCKET_GONE ; 
 int /*<<< orphan*/  SCTP_SO_LOCKED ; 
 int SCTP_STATE_ABOUT_TO_BE_FREED ; 
 scalar_t__ SCTP_STATE_SHUTDOWN_ACK_SENT ; 
 int SCTP_STATE_SHUTDOWN_RECEIVED ; 
 int /*<<< orphan*/  SCTP_STAT_INCR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_TCB_LOCK (struct sctp_tcb*) ; 
 int /*<<< orphan*/  SCTP_TCB_UNLOCK (struct sctp_tcb*) ; 
 int /*<<< orphan*/  SCTP_TIMER_TYPE_RECV ; 
 int /*<<< orphan*/  atomic_add_int (scalar_t__*,int) ; 
 scalar_t__ sctp_calc_rwnd (struct sctp_tcb*,TYPE_3__*) ; 
 int /*<<< orphan*/  sctp_chunk_output (TYPE_1__*,struct sctp_tcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_send_sack (struct sctp_tcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_timer_stop (int /*<<< orphan*/ ,TYPE_1__*,struct sctp_tcb*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sctps_wu_sacks_sent ; 

__attribute__((used)) static void
sctp_user_rcvd(struct sctp_tcb *stcb, uint32_t *freed_so_far, int hold_rlock,
    uint32_t rwnd_req)
{
	/* User pulled some data, do we need a rwnd update? */
	int r_unlocked = 0;
	uint32_t dif, rwnd;
	struct socket *so = NULL;

	if (stcb == NULL)
		return;

	atomic_add_int(&stcb->asoc.refcnt, 1);

	if ((SCTP_GET_STATE(stcb) == SCTP_STATE_SHUTDOWN_ACK_SENT) ||
	    (stcb->asoc.state & (SCTP_STATE_ABOUT_TO_BE_FREED | SCTP_STATE_SHUTDOWN_RECEIVED))) {
		/* Pre-check If we are freeing no update */
		goto no_lock;
	}
	SCTP_INP_INCR_REF(stcb->sctp_ep);
	if ((stcb->sctp_ep->sctp_flags & SCTP_PCB_FLAGS_SOCKET_GONE) ||
	    (stcb->sctp_ep->sctp_flags & SCTP_PCB_FLAGS_SOCKET_ALLGONE)) {
		goto out;
	}
	so = stcb->sctp_socket;
	if (so == NULL) {
		goto out;
	}
	atomic_add_int(&stcb->freed_by_sorcv_sincelast, *freed_so_far);
	/* Have you have freed enough to look */
	*freed_so_far = 0;
	/* Yep, its worth a look and the lock overhead */

	/* Figure out what the rwnd would be */
	rwnd = sctp_calc_rwnd(stcb, &stcb->asoc);
	if (rwnd >= stcb->asoc.my_last_reported_rwnd) {
		dif = rwnd - stcb->asoc.my_last_reported_rwnd;
	} else {
		dif = 0;
	}
	if (dif >= rwnd_req) {
		if (hold_rlock) {
			SCTP_INP_READ_UNLOCK(stcb->sctp_ep);
			r_unlocked = 1;
		}
		if (stcb->asoc.state & SCTP_STATE_ABOUT_TO_BE_FREED) {
			/*
			 * One last check before we allow the guy possibly
			 * to get in. There is a race, where the guy has not
			 * reached the gate. In that case
			 */
			goto out;
		}
		SCTP_TCB_LOCK(stcb);
		if (stcb->asoc.state & SCTP_STATE_ABOUT_TO_BE_FREED) {
			/* No reports here */
			SCTP_TCB_UNLOCK(stcb);
			goto out;
		}
		SCTP_STAT_INCR(sctps_wu_sacks_sent);
		sctp_send_sack(stcb, SCTP_SO_LOCKED);

		sctp_chunk_output(stcb->sctp_ep, stcb,
		    SCTP_OUTPUT_FROM_USR_RCVD, SCTP_SO_LOCKED);
		/* make sure no timer is running */
		sctp_timer_stop(SCTP_TIMER_TYPE_RECV, stcb->sctp_ep, stcb, NULL,
		    SCTP_FROM_SCTPUTIL + SCTP_LOC_6);
		SCTP_TCB_UNLOCK(stcb);
	} else {
		/* Update how much we have pending */
		stcb->freed_by_sorcv_sincelast = dif;
	}
out:
	if (so && r_unlocked && hold_rlock) {
		SCTP_INP_READ_LOCK(stcb->sctp_ep);
	}

	SCTP_INP_DECR_REF(stcb->sctp_ep);
no_lock:
	atomic_add_int(&stcb->asoc.refcnt, -1);
	return;
}