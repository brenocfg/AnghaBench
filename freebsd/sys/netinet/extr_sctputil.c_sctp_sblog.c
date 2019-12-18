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
struct sockbuf {int /*<<< orphan*/  sb_cc; } ;
struct TYPE_5__ {scalar_t__ sb_cc; } ;
struct sctp_tcb {TYPE_1__ asoc; } ;
struct TYPE_7__ {int /*<<< orphan*/  log4; int /*<<< orphan*/  log3; int /*<<< orphan*/  log2; int /*<<< orphan*/  log1; } ;
struct TYPE_6__ {int incr; scalar_t__ stcb_sbcc; int /*<<< orphan*/  so_sbcc; struct sctp_tcb* stcb; } ;
struct TYPE_8__ {TYPE_3__ misc; TYPE_2__ sb; } ;
struct sctp_cwnd_log {TYPE_4__ x; } ;

/* Variables and functions */
 int /*<<< orphan*/  KTR_SCTP ; 
 int /*<<< orphan*/  SCTP_CTR6 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_LOG_EVENT_SB ; 

void
sctp_sblog(struct sockbuf *sb, struct sctp_tcb *stcb, int from, int incr)
{
#if defined(SCTP_LOCAL_TRACE_BUF)
	struct sctp_cwnd_log sctp_clog;

	sctp_clog.x.sb.stcb = stcb;
	sctp_clog.x.sb.so_sbcc = sb->sb_cc;
	if (stcb)
		sctp_clog.x.sb.stcb_sbcc = stcb->asoc.sb_cc;
	else
		sctp_clog.x.sb.stcb_sbcc = 0;
	sctp_clog.x.sb.incr = incr;
	SCTP_CTR6(KTR_SCTP, "SCTP:%d[%d]:%x-%x-%x-%x",
	    SCTP_LOG_EVENT_SB,
	    from,
	    sctp_clog.x.misc.log1,
	    sctp_clog.x.misc.log2,
	    sctp_clog.x.misc.log3,
	    sctp_clog.x.misc.log4);
#endif
}