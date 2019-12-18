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
struct TYPE_6__ {int /*<<< orphan*/  total_flight_count; int /*<<< orphan*/  chunks_on_out_queue; int /*<<< orphan*/  total_output_queue_size; int /*<<< orphan*/  total_flight; } ;
struct sctp_tcb {TYPE_2__ asoc; } ;
struct TYPE_7__ {int /*<<< orphan*/  log4; int /*<<< orphan*/  log3; int /*<<< orphan*/  log2; int /*<<< orphan*/  log1; } ;
struct TYPE_5__ {int /*<<< orphan*/  count_in_flight; int /*<<< orphan*/  count_in_queue; int /*<<< orphan*/  total_in_queue; int /*<<< orphan*/  total_flight; void* stcb; } ;
struct TYPE_8__ {TYPE_3__ misc; TYPE_1__ nagle; } ;
struct sctp_cwnd_log {TYPE_4__ x; } ;

/* Variables and functions */
 int /*<<< orphan*/  KTR_SCTP ; 
 int /*<<< orphan*/  SCTP_CTR6 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_LOG_EVENT_NAGLE ; 

void
sctp_log_nagle_event(struct sctp_tcb *stcb, int action)
{
#if defined(SCTP_LOCAL_TRACE_BUF)
	struct sctp_cwnd_log sctp_clog;

	sctp_clog.x.nagle.stcb = (void *)stcb;
	sctp_clog.x.nagle.total_flight = stcb->asoc.total_flight;
	sctp_clog.x.nagle.total_in_queue = stcb->asoc.total_output_queue_size;
	sctp_clog.x.nagle.count_in_queue = stcb->asoc.chunks_on_out_queue;
	sctp_clog.x.nagle.count_in_flight = stcb->asoc.total_flight_count;
	SCTP_CTR6(KTR_SCTP, "SCTP:%d[%d]:%x-%x-%x-%x",
	    SCTP_LOG_EVENT_NAGLE,
	    action,
	    sctp_clog.x.misc.log1,
	    sctp_clog.x.misc.log2,
	    sctp_clog.x.misc.log3,
	    sctp_clog.x.misc.log4);
#endif
}