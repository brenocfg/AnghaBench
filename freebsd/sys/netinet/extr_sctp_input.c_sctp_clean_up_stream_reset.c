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
struct sctp_tmit_chunk {int /*<<< orphan*/ * data; int /*<<< orphan*/  whoTo; } ;
struct sctp_association {int /*<<< orphan*/  ctrl_queue_cnt; int /*<<< orphan*/  control_send_queue; struct sctp_tmit_chunk* str_reset; } ;
struct sctp_tcb {int /*<<< orphan*/  sctp_ep; struct sctp_association asoc; } ;

/* Variables and functions */
 scalar_t__ SCTP_FROM_SCTP_INPUT ; 
 scalar_t__ SCTP_LOC_28 ; 
 int /*<<< orphan*/  SCTP_SO_NOT_LOCKED ; 
 int /*<<< orphan*/  SCTP_TIMER_TYPE_STRRESET ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct sctp_tmit_chunk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_free_a_chunk (struct sctp_tcb*,struct sctp_tmit_chunk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_m_freem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_next ; 
 int /*<<< orphan*/  sctp_timer_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sctp_tcb*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
sctp_clean_up_stream_reset(struct sctp_tcb *stcb)
{
	struct sctp_association *asoc;
	struct sctp_tmit_chunk *chk;

	asoc = &stcb->asoc;
	chk = asoc->str_reset;
	if (chk == NULL) {
		return;
	}
	asoc->str_reset = NULL;
	sctp_timer_stop(SCTP_TIMER_TYPE_STRRESET, stcb->sctp_ep, stcb,
	    chk->whoTo, SCTP_FROM_SCTP_INPUT + SCTP_LOC_28);
	TAILQ_REMOVE(&asoc->control_send_queue, chk, sctp_next);
	asoc->ctrl_queue_cnt--;
	if (chk->data) {
		sctp_m_freem(chk->data);
		chk->data = NULL;
	}
	sctp_free_a_chunk(stcb, chk, SCTP_SO_NOT_LOCKED);
}