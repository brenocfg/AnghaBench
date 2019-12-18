#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  asconf_seq_out; int /*<<< orphan*/  asconf_seq_out_acked; } ;
struct sctp_tcb {TYPE_1__ asoc; int /*<<< orphan*/  sctp_ep; } ;
struct sctp_nets {int dummy; } ;

/* Variables and functions */
 scalar_t__ SCTP_FROM_SCTP_ASCONF ; 
 scalar_t__ SCTP_LOC_2 ; 
 int /*<<< orphan*/  SCTP_TIMER_TYPE_ASCONF ; 
 int /*<<< orphan*/  sctp_timer_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sctp_tcb*,struct sctp_nets*,scalar_t__) ; 
 int /*<<< orphan*/  sctp_toss_old_asconf (struct sctp_tcb*) ; 

void
sctp_asconf_cleanup(struct sctp_tcb *stcb, struct sctp_nets *net)
{
	/*
	 * clear out any existing asconfs going out
	 */
	sctp_timer_stop(SCTP_TIMER_TYPE_ASCONF, stcb->sctp_ep, stcb, net,
	    SCTP_FROM_SCTP_ASCONF + SCTP_LOC_2);
	stcb->asoc.asconf_seq_out_acked = stcb->asoc.asconf_seq_out;
	/* remove the old ASCONF on our outbound queue */
	sctp_toss_old_asconf(stcb);
}