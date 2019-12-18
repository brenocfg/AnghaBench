#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct sctp_tmit_chunk {int /*<<< orphan*/  whoTo; } ;
struct TYPE_15__ {scalar_t__ num_send_timers_up; scalar_t__ sent_queue_cnt; int /*<<< orphan*/  sent_queue; TYPE_7__* deleted_primary; TYPE_5__* primary_destination; } ;
struct sctp_tcb {int /*<<< orphan*/  sctp_ep; TYPE_6__ asoc; } ;
struct sctp_nets {int dest_state; } ;
struct TYPE_10__ {int /*<<< orphan*/  sa; } ;
struct TYPE_11__ {TYPE_1__ _l_addr; } ;
struct TYPE_16__ {TYPE_2__ ro; } ;
struct TYPE_12__ {int /*<<< orphan*/  sa; } ;
struct TYPE_13__ {TYPE_3__ _l_addr; } ;
struct TYPE_14__ {TYPE_4__ ro; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTPDBG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SCTPDBG_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int SCTP_ADDR_UNCONFIRMED ; 
 int /*<<< orphan*/  SCTP_DEBUG_ASCONF1 ; 
 scalar_t__ SCTP_FROM_SCTP_ASCONF ; 
 int /*<<< orphan*/  SCTP_INP_DECR_REF (int /*<<< orphan*/ ) ; 
 scalar_t__ SCTP_LOC_3 ; 
 int /*<<< orphan*/  SCTP_OUTPUT_FROM_T3 ; 
 int /*<<< orphan*/  SCTP_SO_NOT_LOCKED ; 
 int /*<<< orphan*/  SCTP_TCB_LOCK_ASSERT (struct sctp_tcb*) ; 
 int /*<<< orphan*/  SCTP_TIMER_TYPE_SEND ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct sctp_tmit_chunk* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_auditing (int,int /*<<< orphan*/ ,struct sctp_tcb*,TYPE_7__*) ; 
 int /*<<< orphan*/  sctp_chunk_output (int /*<<< orphan*/ ,struct sctp_tcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sctp_t3rxt_timer (int /*<<< orphan*/ ,struct sctp_tcb*,TYPE_7__*) ; 
 int /*<<< orphan*/  sctp_timer_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sctp_tcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_timer_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sctp_tcb*,TYPE_7__*,scalar_t__) ; 

void
sctp_assoc_immediate_retrans(struct sctp_tcb *stcb, struct sctp_nets *dstnet)
{
	int error;

	if (dstnet->dest_state & SCTP_ADDR_UNCONFIRMED) {
		return;
	}
	if (stcb->asoc.deleted_primary == NULL) {
		return;
	}

	if (!TAILQ_EMPTY(&stcb->asoc.sent_queue)) {
		SCTPDBG(SCTP_DEBUG_ASCONF1, "assoc_immediate_retrans: Deleted primary is ");
		SCTPDBG_ADDR(SCTP_DEBUG_ASCONF1, &stcb->asoc.deleted_primary->ro._l_addr.sa);
		SCTPDBG(SCTP_DEBUG_ASCONF1, "Current Primary is ");
		SCTPDBG_ADDR(SCTP_DEBUG_ASCONF1, &stcb->asoc.primary_destination->ro._l_addr.sa);
		sctp_timer_stop(SCTP_TIMER_TYPE_SEND, stcb->sctp_ep, stcb,
		    stcb->asoc.deleted_primary,
		    SCTP_FROM_SCTP_ASCONF + SCTP_LOC_3);
		stcb->asoc.num_send_timers_up--;
		if (stcb->asoc.num_send_timers_up < 0) {
			stcb->asoc.num_send_timers_up = 0;
		}
		SCTP_TCB_LOCK_ASSERT(stcb);
		error = sctp_t3rxt_timer(stcb->sctp_ep, stcb,
		    stcb->asoc.deleted_primary);
		if (error) {
			SCTP_INP_DECR_REF(stcb->sctp_ep);
			return;
		}
		SCTP_TCB_LOCK_ASSERT(stcb);
#ifdef SCTP_AUDITING_ENABLED
		sctp_auditing(4, stcb->sctp_ep, stcb, stcb->asoc.deleted_primary);
#endif
		sctp_chunk_output(stcb->sctp_ep, stcb, SCTP_OUTPUT_FROM_T3, SCTP_SO_NOT_LOCKED);
		if ((stcb->asoc.num_send_timers_up == 0) &&
		    (stcb->asoc.sent_queue_cnt > 0)) {
			struct sctp_tmit_chunk *chk;

			chk = TAILQ_FIRST(&stcb->asoc.sent_queue);
			sctp_timer_start(SCTP_TIMER_TYPE_SEND, stcb->sctp_ep,
			    stcb, chk->whoTo);
		}
	}
	return;
}