#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sctp_tcb {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * tqe_prev; int /*<<< orphan*/ * tqe_next; } ;
struct sctp_stream_queue_pending {TYPE_1__ ss_next; } ;
struct TYPE_5__ {int /*<<< orphan*/  list; } ;
struct TYPE_6__ {TYPE_2__ out; } ;
struct sctp_association {TYPE_3__ ss_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_TCB_SEND_LOCK (struct sctp_tcb*) ; 
 int /*<<< orphan*/  SCTP_TCB_SEND_UNLOCK (struct sctp_tcb*) ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct sctp_stream_queue_pending* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct sctp_stream_queue_pending*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ss_next ; 

__attribute__((used)) static void
sctp_ss_fcfs_clear(struct sctp_tcb *stcb, struct sctp_association *asoc,
    int clear_values, int holds_lock)
{
	struct sctp_stream_queue_pending *sp;

	if (clear_values) {
		if (holds_lock == 0) {
			SCTP_TCB_SEND_LOCK(stcb);
		}
		while (!TAILQ_EMPTY(&asoc->ss_data.out.list)) {
			sp = TAILQ_FIRST(&asoc->ss_data.out.list);
			TAILQ_REMOVE(&asoc->ss_data.out.list, sp, ss_next);
			sp->ss_next.tqe_next = NULL;
			sp->ss_next.tqe_prev = NULL;
		}
		if (holds_lock == 0) {
			SCTP_TCB_SEND_UNLOCK(stcb);
		}
	}
	return;
}