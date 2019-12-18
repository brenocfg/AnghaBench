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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int send_queue_cnt; int stream_queue_cnt; } ;
struct sctp_tcb {TYPE_2__ asoc; } ;
struct sctp_nets {int /*<<< orphan*/  flight_size; } ;
struct TYPE_7__ {int /*<<< orphan*/  log4; int /*<<< orphan*/  log3; int /*<<< orphan*/  log2; int /*<<< orphan*/  log1; } ;
struct TYPE_5__ {int cwnd_new_value; int cwnd_augment; int cnt_in_send; int cnt_in_str; int /*<<< orphan*/  inflight; struct sctp_nets* net; } ;
struct TYPE_8__ {TYPE_3__ misc; TYPE_1__ cwnd; } ;
struct sctp_cwnd_log {TYPE_4__ x; } ;
typedef  int /*<<< orphan*/  sctp_clog ;

/* Variables and functions */
 int /*<<< orphan*/  KTR_SCTP ; 
 int /*<<< orphan*/  SCTP_CTR6 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_LOG_EVENT_MAXBURST ; 
 int /*<<< orphan*/  memset (struct sctp_cwnd_log*,int /*<<< orphan*/ ,int) ; 

void
sctp_log_maxburst(struct sctp_tcb *stcb, struct sctp_nets *net, int error, int burst, uint8_t from)
{
#if defined(SCTP_LOCAL_TRACE_BUF)
	struct sctp_cwnd_log sctp_clog;

	memset(&sctp_clog, 0, sizeof(sctp_clog));
	sctp_clog.x.cwnd.net = net;
	sctp_clog.x.cwnd.cwnd_new_value = error;
	sctp_clog.x.cwnd.inflight = net->flight_size;
	sctp_clog.x.cwnd.cwnd_augment = burst;
	if (stcb->asoc.send_queue_cnt > 255)
		sctp_clog.x.cwnd.cnt_in_send = 255;
	else
		sctp_clog.x.cwnd.cnt_in_send = stcb->asoc.send_queue_cnt;
	if (stcb->asoc.stream_queue_cnt > 255)
		sctp_clog.x.cwnd.cnt_in_str = 255;
	else
		sctp_clog.x.cwnd.cnt_in_str = stcb->asoc.stream_queue_cnt;
	SCTP_CTR6(KTR_SCTP, "SCTP:%d[%d]:%x-%x-%x-%x",
	    SCTP_LOG_EVENT_MAXBURST,
	    from,
	    sctp_clog.x.misc.log1,
	    sctp_clog.x.misc.log2,
	    sctp_clog.x.misc.log3,
	    sctp_clog.x.misc.log4);
#endif
}