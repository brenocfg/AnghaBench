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
typedef  scalar_t__ uint8_t ;
struct TYPE_5__ {int send_queue_cnt; int stream_queue_cnt; int /*<<< orphan*/  peers_rwnd; } ;
struct sctp_tcb {TYPE_1__ asoc; } ;
struct sctp_nets {int /*<<< orphan*/  find_pseudo_cumack; int /*<<< orphan*/  new_pseudo_cumack; int /*<<< orphan*/  pseudo_cumack; int /*<<< orphan*/  flight_size; int /*<<< orphan*/  cwnd; } ;
struct TYPE_7__ {int /*<<< orphan*/  log4; int /*<<< orphan*/  log3; int /*<<< orphan*/  log2; int /*<<< orphan*/  log1; } ;
struct TYPE_6__ {int cnt_in_send; int cnt_in_str; int cwnd_augment; int /*<<< orphan*/  meets_pseudo_cumack; int /*<<< orphan*/  need_new_pseudo_cumack; int /*<<< orphan*/  pseudo_cumack; int /*<<< orphan*/  inflight; int /*<<< orphan*/  cwnd_new_value; struct sctp_nets* net; } ;
struct TYPE_8__ {TYPE_3__ misc; TYPE_2__ cwnd; } ;
struct sctp_cwnd_log {TYPE_4__ x; } ;

/* Variables and functions */
 int /*<<< orphan*/  KTR_SCTP ; 
 int /*<<< orphan*/  SCTP_CTR6 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SCTP_CWNDLOG_PRESEND ; 
 int /*<<< orphan*/  SCTP_LOG_EVENT_CWND ; 

void
sctp_log_cwnd(struct sctp_tcb *stcb, struct sctp_nets *net, int augment, uint8_t from)
{
#if defined(SCTP_LOCAL_TRACE_BUF)
	struct sctp_cwnd_log sctp_clog;

	sctp_clog.x.cwnd.net = net;
	if (stcb->asoc.send_queue_cnt > 255)
		sctp_clog.x.cwnd.cnt_in_send = 255;
	else
		sctp_clog.x.cwnd.cnt_in_send = stcb->asoc.send_queue_cnt;
	if (stcb->asoc.stream_queue_cnt > 255)
		sctp_clog.x.cwnd.cnt_in_str = 255;
	else
		sctp_clog.x.cwnd.cnt_in_str = stcb->asoc.stream_queue_cnt;

	if (net) {
		sctp_clog.x.cwnd.cwnd_new_value = net->cwnd;
		sctp_clog.x.cwnd.inflight = net->flight_size;
		sctp_clog.x.cwnd.pseudo_cumack = net->pseudo_cumack;
		sctp_clog.x.cwnd.meets_pseudo_cumack = net->new_pseudo_cumack;
		sctp_clog.x.cwnd.need_new_pseudo_cumack = net->find_pseudo_cumack;
	}
	if (SCTP_CWNDLOG_PRESEND == from) {
		sctp_clog.x.cwnd.meets_pseudo_cumack = stcb->asoc.peers_rwnd;
	}
	sctp_clog.x.cwnd.cwnd_augment = augment;
	SCTP_CTR6(KTR_SCTP, "SCTP:%d[%d]:%x-%x-%x-%x",
	    SCTP_LOG_EVENT_CWND,
	    from,
	    sctp_clog.x.misc.log1,
	    sctp_clog.x.misc.log2,
	    sctp_clog.x.misc.log3,
	    sctp_clog.x.misc.log4);
#endif
}