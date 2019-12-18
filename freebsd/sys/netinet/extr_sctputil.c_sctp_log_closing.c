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
typedef  scalar_t__ uint16_t ;
struct TYPE_5__ {scalar_t__ state; } ;
struct sctp_tcb {TYPE_1__ asoc; } ;
struct sctp_inpcb {int /*<<< orphan*/  sctp_flags; } ;
struct TYPE_7__ {int /*<<< orphan*/  log4; int /*<<< orphan*/  log3; int /*<<< orphan*/  log2; int /*<<< orphan*/  log1; } ;
struct TYPE_6__ {int /*<<< orphan*/  loc; scalar_t__ state; void* stcb; int /*<<< orphan*/  sctp_flags; void* inp; } ;
struct TYPE_8__ {TYPE_3__ misc; TYPE_2__ close; } ;
struct sctp_cwnd_log {TYPE_4__ x; } ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  KTR_SCTP ; 
 int /*<<< orphan*/  SCTP_CTR6 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_LOG_EVENT_CLOSE ; 

void
sctp_log_closing(struct sctp_inpcb *inp, struct sctp_tcb *stcb, int16_t loc)
{
#if defined(SCTP_LOCAL_TRACE_BUF)
	struct sctp_cwnd_log sctp_clog;

	sctp_clog.x.close.inp = (void *)inp;
	sctp_clog.x.close.sctp_flags = inp->sctp_flags;
	if (stcb) {
		sctp_clog.x.close.stcb = (void *)stcb;
		sctp_clog.x.close.state = (uint16_t)stcb->asoc.state;
	} else {
		sctp_clog.x.close.stcb = 0;
		sctp_clog.x.close.state = 0;
	}
	sctp_clog.x.close.loc = loc;
	SCTP_CTR6(KTR_SCTP, "SCTP:%d[%d]:%x-%x-%x-%x",
	    SCTP_LOG_EVENT_CLOSE,
	    0,
	    sctp_clog.x.misc.log1,
	    sctp_clog.x.misc.log2,
	    sctp_clog.x.misc.log3,
	    sctp_clog.x.misc.log4);
#endif
}