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
typedef  void* uint16_t ;
struct sctp_queued_to_read {scalar_t__ mid; scalar_t__ sinfo_tsn; int /*<<< orphan*/  sinfo_stream; int /*<<< orphan*/  stcb; } ;
struct TYPE_5__ {int /*<<< orphan*/  log4; int /*<<< orphan*/  log3; int /*<<< orphan*/  log2; int /*<<< orphan*/  log1; } ;
struct TYPE_4__ {void* e_sseq; scalar_t__ e_tsn; int /*<<< orphan*/  strm; void* n_sseq; scalar_t__ n_tsn; int /*<<< orphan*/  stcb; } ;
struct TYPE_6__ {TYPE_2__ misc; TYPE_1__ strlog; } ;
struct sctp_cwnd_log {TYPE_3__ x; } ;

/* Variables and functions */
 int /*<<< orphan*/  KTR_SCTP ; 
 int /*<<< orphan*/  SCTP_CTR6 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_LOG_EVENT_STRM ; 
 int /*<<< orphan*/  SCTP_PRINTF (char*) ; 

void
sctp_log_strm_del(struct sctp_queued_to_read *control, struct sctp_queued_to_read *poschk, int from)
{
#if defined(SCTP_LOCAL_TRACE_BUF)
	struct sctp_cwnd_log sctp_clog;

	if (control == NULL) {
		SCTP_PRINTF("Gak log of NULL?\n");
		return;
	}
	sctp_clog.x.strlog.stcb = control->stcb;
	sctp_clog.x.strlog.n_tsn = control->sinfo_tsn;
	sctp_clog.x.strlog.n_sseq = (uint16_t)control->mid;
	sctp_clog.x.strlog.strm = control->sinfo_stream;
	if (poschk != NULL) {
		sctp_clog.x.strlog.e_tsn = poschk->sinfo_tsn;
		sctp_clog.x.strlog.e_sseq = (uint16_t)poschk->mid;
	} else {
		sctp_clog.x.strlog.e_tsn = 0;
		sctp_clog.x.strlog.e_sseq = 0;
	}
	SCTP_CTR6(KTR_SCTP, "SCTP:%d[%d]:%x-%x-%x-%x",
	    SCTP_LOG_EVENT_STRM,
	    from,
	    sctp_clog.x.misc.log1,
	    sctp_clog.x.misc.log2,
	    sctp_clog.x.misc.log3,
	    sctp_clog.x.misc.log4);
#endif
}