#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct sctp_tcb {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/ * tqe_prev; int /*<<< orphan*/ * tqe_next; } ;
struct TYPE_11__ {TYPE_3__ next_spoke; scalar_t__ priority; } ;
struct TYPE_12__ {TYPE_4__ prio; } ;
struct sctp_stream_out {TYPE_5__ ss_params; } ;
struct TYPE_8__ {int /*<<< orphan*/  wheel; } ;
struct TYPE_13__ {int /*<<< orphan*/ * last_out_stream; TYPE_1__ out; } ;
struct sctp_association {TYPE_6__ ss_data; } ;
struct TYPE_9__ {int /*<<< orphan*/  next_spoke; } ;
struct TYPE_14__ {TYPE_2__ prio; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_TCB_SEND_LOCK (struct sctp_tcb*) ; 
 int /*<<< orphan*/  SCTP_TCB_SEND_UNLOCK (struct sctp_tcb*) ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct sctp_stream_out* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct sctp_stream_out*,int /*<<< orphan*/ ) ; 
 TYPE_7__ ss_params ; 

__attribute__((used)) static void
sctp_ss_prio_clear(struct sctp_tcb *stcb, struct sctp_association *asoc,
    int clear_values, int holds_lock)
{
	if (holds_lock == 0) {
		SCTP_TCB_SEND_LOCK(stcb);
	}
	while (!TAILQ_EMPTY(&asoc->ss_data.out.wheel)) {
		struct sctp_stream_out *strq;

		strq = TAILQ_FIRST(&asoc->ss_data.out.wheel);
		if (clear_values) {
			strq->ss_params.prio.priority = 0;
		}
		TAILQ_REMOVE(&asoc->ss_data.out.wheel, strq, ss_params.prio.next_spoke);
		strq->ss_params.prio.next_spoke.tqe_next = NULL;
		strq->ss_params.prio.next_spoke.tqe_prev = NULL;

	}
	asoc->ss_data.last_out_stream = NULL;
	if (holds_lock == 0) {
		SCTP_TCB_SEND_UNLOCK(stcb);
	}
	return;
}