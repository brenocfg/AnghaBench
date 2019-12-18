#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_9__ {int sb_flags; } ;
struct socket {TYPE_3__ so_snd; } ;
struct TYPE_7__ {int stream_queue_cnt; int chunks_on_out_queue; int /*<<< orphan*/  sent_queue_cnt; int /*<<< orphan*/  send_queue_cnt; int /*<<< orphan*/  total_flight_count; } ;
struct sctp_tcb {struct socket* sctp_socket; TYPE_2__* sctp_ep; TYPE_1__ asoc; } ;
struct TYPE_11__ {int /*<<< orphan*/  log4; int /*<<< orphan*/  log3; int /*<<< orphan*/  log2; int /*<<< orphan*/  log1; } ;
struct TYPE_10__ {int stream_qcnt; int chunks_on_oque; int sctpflags; int sbflags; int /*<<< orphan*/  sent_q; int /*<<< orphan*/  send_q; int /*<<< orphan*/  flight; int /*<<< orphan*/  wake_cnt; void* stcb; } ;
struct TYPE_12__ {TYPE_5__ misc; TYPE_4__ wake; } ;
struct sctp_cwnd_log {TYPE_6__ x; } ;
struct TYPE_8__ {int sctp_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KTR_SCTP ; 
 int /*<<< orphan*/  SCTP_CTR6 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_LOG_EVENT_WAKE ; 
 int SCTP_PCB_FLAGS_DONT_WAKE ; 
 int SCTP_PCB_FLAGS_WAKEINPUT ; 
 int SCTP_PCB_FLAGS_WAKEOUTPUT ; 

void
sctp_wakeup_log(struct sctp_tcb *stcb, uint32_t wake_cnt, int from)
{
#if defined(SCTP_LOCAL_TRACE_BUF)
	struct sctp_cwnd_log sctp_clog;

	sctp_clog.x.wake.stcb = (void *)stcb;
	sctp_clog.x.wake.wake_cnt = wake_cnt;
	sctp_clog.x.wake.flight = stcb->asoc.total_flight_count;
	sctp_clog.x.wake.send_q = stcb->asoc.send_queue_cnt;
	sctp_clog.x.wake.sent_q = stcb->asoc.sent_queue_cnt;

	if (stcb->asoc.stream_queue_cnt < 0xff)
		sctp_clog.x.wake.stream_qcnt = (uint8_t)stcb->asoc.stream_queue_cnt;
	else
		sctp_clog.x.wake.stream_qcnt = 0xff;

	if (stcb->asoc.chunks_on_out_queue < 0xff)
		sctp_clog.x.wake.chunks_on_oque = (uint8_t)stcb->asoc.chunks_on_out_queue;
	else
		sctp_clog.x.wake.chunks_on_oque = 0xff;

	sctp_clog.x.wake.sctpflags = 0;
	/* set in the defered mode stuff */
	if (stcb->sctp_ep->sctp_flags & SCTP_PCB_FLAGS_DONT_WAKE)
		sctp_clog.x.wake.sctpflags |= 1;
	if (stcb->sctp_ep->sctp_flags & SCTP_PCB_FLAGS_WAKEOUTPUT)
		sctp_clog.x.wake.sctpflags |= 2;
	if (stcb->sctp_ep->sctp_flags & SCTP_PCB_FLAGS_WAKEINPUT)
		sctp_clog.x.wake.sctpflags |= 4;
	/* what about the sb */
	if (stcb->sctp_socket) {
		struct socket *so = stcb->sctp_socket;

		sctp_clog.x.wake.sbflags = (uint8_t)((so->so_snd.sb_flags & 0x00ff));
	} else {
		sctp_clog.x.wake.sbflags = 0xff;
	}
	SCTP_CTR6(KTR_SCTP, "SCTP:%d[%d]:%x-%x-%x-%x",
	    SCTP_LOG_EVENT_WAKE,
	    from,
	    sctp_clog.x.misc.log1,
	    sctp_clog.x.misc.log2,
	    sctp_clog.x.misc.log3,
	    sctp_clog.x.misc.log4);
#endif
}