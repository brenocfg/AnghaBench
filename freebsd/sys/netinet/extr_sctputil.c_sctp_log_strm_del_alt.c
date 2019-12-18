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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  void* uint16_t ;
struct sctp_tcb {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  log4; int /*<<< orphan*/  log3; int /*<<< orphan*/  log2; int /*<<< orphan*/  log1; } ;
struct TYPE_4__ {void* strm; scalar_t__ e_sseq; scalar_t__ e_tsn; void* n_sseq; int /*<<< orphan*/  n_tsn; struct sctp_tcb* stcb; } ;
struct TYPE_6__ {TYPE_2__ misc; TYPE_1__ strlog; } ;
struct sctp_cwnd_log {TYPE_3__ x; } ;

/* Variables and functions */
 int /*<<< orphan*/  KTR_SCTP ; 
 int /*<<< orphan*/  SCTP_CTR6 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_LOG_EVENT_STRM ; 

void
sctp_log_strm_del_alt(struct sctp_tcb *stcb, uint32_t tsn, uint16_t sseq, uint16_t stream, int from)
{
#if defined(SCTP_LOCAL_TRACE_BUF)
	struct sctp_cwnd_log sctp_clog;

	sctp_clog.x.strlog.stcb = stcb;
	sctp_clog.x.strlog.n_tsn = tsn;
	sctp_clog.x.strlog.n_sseq = sseq;
	sctp_clog.x.strlog.e_tsn = 0;
	sctp_clog.x.strlog.e_sseq = 0;
	sctp_clog.x.strlog.strm = stream;
	SCTP_CTR6(KTR_SCTP, "SCTP:%d[%d]:%x-%x-%x-%x",
	    SCTP_LOG_EVENT_STRM,
	    from,
	    sctp_clog.x.misc.log1,
	    sctp_clog.x.misc.log2,
	    sctp_clog.x.misc.log3,
	    sctp_clog.x.misc.log4);
#endif
}