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
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* sctp_ss_add_to_stream ) (struct sctp_tcb*,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ;} ;
struct TYPE_8__ {size_t streamoutcnt; int /*<<< orphan*/ * strmout; TYPE_3__ ss_functions; } ;
struct sctp_tcb {TYPE_4__ asoc; } ;
struct TYPE_5__ {int /*<<< orphan*/  wheel; } ;
struct TYPE_6__ {TYPE_1__ out; int /*<<< orphan*/ * last_out_stream; int /*<<< orphan*/ * locked_on_sending; } ;
struct sctp_association {TYPE_2__ ss_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_TCB_SEND_LOCK (struct sctp_tcb*) ; 
 int /*<<< orphan*/  SCTP_TCB_SEND_UNLOCK (struct sctp_tcb*) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct sctp_tcb*,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
sctp_ss_default_init(struct sctp_tcb *stcb, struct sctp_association *asoc,
    int holds_lock)
{
	uint16_t i;

	if (holds_lock == 0) {
		SCTP_TCB_SEND_LOCK(stcb);
	}
	asoc->ss_data.locked_on_sending = NULL;
	asoc->ss_data.last_out_stream = NULL;
	TAILQ_INIT(&asoc->ss_data.out.wheel);
	/*
	 * If there is data in the stream queues already, the scheduler of
	 * an existing association has been changed. We need to add all
	 * stream queues to the wheel.
	 */
	for (i = 0; i < stcb->asoc.streamoutcnt; i++) {
		stcb->asoc.ss_functions.sctp_ss_add_to_stream(stcb, &stcb->asoc,
		    &stcb->asoc.strmout[i],
		    NULL, 1);
	}
	if (holds_lock == 0) {
		SCTP_TCB_SEND_UNLOCK(stcb);
	}
	return;
}