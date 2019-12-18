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
struct TYPE_4__ {int /*<<< orphan*/  log4; int /*<<< orphan*/  log3; int /*<<< orphan*/  log2; int /*<<< orphan*/  log1; } ;
struct TYPE_5__ {void* tsn; void* largest_new_tsn; void* largest_tsn; } ;
struct TYPE_6__ {TYPE_1__ misc; TYPE_2__ fr; } ;
struct sctp_cwnd_log {TYPE_3__ x; } ;
typedef  int /*<<< orphan*/  sctp_clog ;

/* Variables and functions */
 int /*<<< orphan*/  KTR_SCTP ; 
 int /*<<< orphan*/  SCTP_CTR6 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_LOG_EVENT_FR ; 
 int /*<<< orphan*/  memset (struct sctp_cwnd_log*,int /*<<< orphan*/ ,int) ; 

void
sctp_log_fr(uint32_t biggest_tsn, uint32_t biggest_new_tsn, uint32_t tsn, int from)
{
#if defined(SCTP_LOCAL_TRACE_BUF)
	struct sctp_cwnd_log sctp_clog;

	memset(&sctp_clog, 0, sizeof(sctp_clog));
	sctp_clog.x.fr.largest_tsn = biggest_tsn;
	sctp_clog.x.fr.largest_new_tsn = biggest_new_tsn;
	sctp_clog.x.fr.tsn = tsn;
	SCTP_CTR6(KTR_SCTP, "SCTP:%d[%d]:%x-%x-%x-%x",
	    SCTP_LOG_EVENT_FR,
	    from,
	    sctp_clog.x.misc.log1,
	    sctp_clog.x.misc.log2,
	    sctp_clog.x.misc.log3,
	    sctp_clog.x.misc.log4);
#endif
}