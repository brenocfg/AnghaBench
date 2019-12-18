#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {struct sctp_stream_out* last_out_stream; struct sctp_stream_out* locked_on_sending; } ;
struct TYPE_9__ {TYPE_5__ ss_data; } ;
struct sctp_tcb {TYPE_4__ asoc; } ;
struct TYPE_6__ {int /*<<< orphan*/ * tqe_prev; int /*<<< orphan*/ * tqe_next; } ;
struct TYPE_7__ {TYPE_1__ next_spoke; } ;
struct TYPE_8__ {TYPE_2__ fb; } ;
struct sctp_stream_out {TYPE_3__ ss_params; } ;

/* Variables and functions */

__attribute__((used)) static void
sctp_ss_fcfs_init_stream(struct sctp_tcb *stcb, struct sctp_stream_out *strq, struct sctp_stream_out *with_strq)
{
	if (with_strq != NULL) {
		if (stcb->asoc.ss_data.locked_on_sending == with_strq) {
			stcb->asoc.ss_data.locked_on_sending = strq;
		}
		if (stcb->asoc.ss_data.last_out_stream == with_strq) {
			stcb->asoc.ss_data.last_out_stream = strq;
		}
	}
	strq->ss_params.fb.next_spoke.tqe_next = NULL;
	strq->ss_params.fb.next_spoke.tqe_prev = NULL;
	return;
}