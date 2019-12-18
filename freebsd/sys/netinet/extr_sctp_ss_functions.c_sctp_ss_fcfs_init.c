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
typedef  int uint32_t ;
typedef  size_t uint16_t ;
struct TYPE_7__ {size_t streamoutcnt; TYPE_4__* strmout; } ;
struct sctp_tcb {TYPE_3__ asoc; } ;
struct sctp_stream_queue_pending {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  list; } ;
struct TYPE_6__ {TYPE_1__ out; } ;
struct sctp_association {TYPE_2__ ss_data; } ;
struct TYPE_8__ {int /*<<< orphan*/  outqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_TCB_SEND_LOCK (struct sctp_tcb*) ; 
 int /*<<< orphan*/  SCTP_TCB_SEND_UNLOCK (struct sctp_tcb*) ; 
 struct sctp_stream_queue_pending* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 struct sctp_stream_queue_pending* TAILQ_NEXT (struct sctp_stream_queue_pending*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  sctp_ss_fcfs_add (struct sctp_tcb*,TYPE_3__*,TYPE_4__*,struct sctp_stream_queue_pending*,int) ; 

__attribute__((used)) static void
sctp_ss_fcfs_init(struct sctp_tcb *stcb, struct sctp_association *asoc,
    int holds_lock)
{
	uint32_t x, n = 0, add_more = 1;
	struct sctp_stream_queue_pending *sp;
	uint16_t i;

	if (holds_lock == 0) {
		SCTP_TCB_SEND_LOCK(stcb);
	}
	TAILQ_INIT(&asoc->ss_data.out.list);
	/*
	 * If there is data in the stream queues already, the scheduler of
	 * an existing association has been changed. We can only cycle
	 * through the stream queues and add everything to the FCFS queue.
	 */
	while (add_more) {
		add_more = 0;
		for (i = 0; i < stcb->asoc.streamoutcnt; i++) {
			sp = TAILQ_FIRST(&stcb->asoc.strmout[i].outqueue);
			x = 0;
			/* Find n. message in current stream queue */
			while (sp != NULL && x < n) {
				sp = TAILQ_NEXT(sp, next);
				x++;
			}
			if (sp != NULL) {
				sctp_ss_fcfs_add(stcb, &stcb->asoc, &stcb->asoc.strmout[i], sp, 1);
				add_more = 1;
			}
		}
		n++;
	}
	if (holds_lock == 0) {
		SCTP_TCB_SEND_UNLOCK(stcb);
	}
	return;
}