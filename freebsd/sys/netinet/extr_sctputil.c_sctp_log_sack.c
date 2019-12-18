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
typedef  void* uint32_t ;
typedef  void* uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  log4; int /*<<< orphan*/  log3; int /*<<< orphan*/  log2; int /*<<< orphan*/  log1; } ;
struct TYPE_6__ {void* numDups; void* numGaps; void* tsn; void* oldcumack; void* cumack; } ;
struct TYPE_5__ {TYPE_1__ misc; TYPE_3__ sack; } ;
struct sctp_cwnd_log {TYPE_2__ x; } ;

/* Variables and functions */
 int /*<<< orphan*/  KTR_SCTP ; 
 int /*<<< orphan*/  SCTP_CTR6 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_LOG_EVENT_SACK ; 

void
sctp_log_sack(uint32_t old_cumack, uint32_t cumack, uint32_t tsn, uint16_t gaps, uint16_t dups, int from)
{
#if defined(SCTP_LOCAL_TRACE_BUF)
	struct sctp_cwnd_log sctp_clog;

	sctp_clog.x.sack.cumack = cumack;
	sctp_clog.x.sack.oldcumack = old_cumack;
	sctp_clog.x.sack.tsn = tsn;
	sctp_clog.x.sack.numGaps = gaps;
	sctp_clog.x.sack.numDups = dups;
	SCTP_CTR6(KTR_SCTP, "SCTP:%d[%d]:%x-%x-%x-%x",
	    SCTP_LOG_EVENT_SACK,
	    from,
	    sctp_clog.x.misc.log1,
	    sctp_clog.x.misc.log2,
	    sctp_clog.x.misc.log3,
	    sctp_clog.x.misc.log4);
#endif
}