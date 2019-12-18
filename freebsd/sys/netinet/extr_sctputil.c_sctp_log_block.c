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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  void* uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  log4; int /*<<< orphan*/  log3; int /*<<< orphan*/  log2; int /*<<< orphan*/  log1; } ;
struct TYPE_4__ {scalar_t__ sndlen; void* flight_size; void* chunks_on_oque; void* stream_qcnt; int /*<<< orphan*/  peer_rwnd; void* send_sent_qcnt; int /*<<< orphan*/  onsb; } ;
struct TYPE_6__ {TYPE_2__ misc; TYPE_1__ blk; } ;
struct sctp_cwnd_log {TYPE_3__ x; } ;
struct sctp_association {int total_flight; scalar_t__ chunks_on_out_queue; scalar_t__ stream_queue_cnt; int /*<<< orphan*/  peers_rwnd; scalar_t__ sent_queue_cnt; scalar_t__ send_queue_cnt; int /*<<< orphan*/  total_output_queue_size; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  KTR_SCTP ; 
 int /*<<< orphan*/  SCTP_CTR6 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_LOG_EVENT_BLOCK ; 

void
sctp_log_block(uint8_t from, struct sctp_association *asoc, ssize_t sendlen)
{
#if defined(SCTP_LOCAL_TRACE_BUF)
	struct sctp_cwnd_log sctp_clog;

	sctp_clog.x.blk.onsb = asoc->total_output_queue_size;
	sctp_clog.x.blk.send_sent_qcnt = (uint16_t)(asoc->send_queue_cnt + asoc->sent_queue_cnt);
	sctp_clog.x.blk.peer_rwnd = asoc->peers_rwnd;
	sctp_clog.x.blk.stream_qcnt = (uint16_t)asoc->stream_queue_cnt;
	sctp_clog.x.blk.chunks_on_oque = (uint16_t)asoc->chunks_on_out_queue;
	sctp_clog.x.blk.flight_size = (uint16_t)(asoc->total_flight / 1024);
	sctp_clog.x.blk.sndlen = (uint32_t)sendlen;
	SCTP_CTR6(KTR_SCTP, "SCTP:%d[%d]:%x-%x-%x-%x",
	    SCTP_LOG_EVENT_BLOCK,
	    from,
	    sctp_clog.x.misc.log1,
	    sctp_clog.x.misc.log2,
	    sctp_clog.x.misc.log3,
	    sctp_clog.x.misc.log4);
#endif
}