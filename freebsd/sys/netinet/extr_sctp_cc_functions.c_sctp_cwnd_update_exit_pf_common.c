#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  my_vtag; } ;
struct sctp_tcb {int rport; TYPE_2__* sctp_ep; TYPE_1__ asoc; } ;
struct sctp_nets {int cwnd; int mtu; } ;
struct TYPE_4__ {int sctp_lport; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTPDBG (int /*<<< orphan*/ ,char*,void*,int) ; 
 int /*<<< orphan*/  SCTP_DEBUG_INDATA1 ; 
 int /*<<< orphan*/  SDT_PROBE5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sctp_nets*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct sctp_nets*,int,int) ; 
 int /*<<< orphan*/  ack ; 
 int /*<<< orphan*/  cwnd ; 
 int /*<<< orphan*/  sctp ; 

__attribute__((used)) static void
sctp_cwnd_update_exit_pf_common(struct sctp_tcb *stcb, struct sctp_nets *net)
{
	int old_cwnd;

	old_cwnd = net->cwnd;
	net->cwnd = net->mtu;
	SDT_PROBE5(sctp, cwnd, net, ack,
	    stcb->asoc.my_vtag, ((stcb->sctp_ep->sctp_lport << 16) | (stcb->rport)), net,
	    old_cwnd, net->cwnd);
	SCTPDBG(SCTP_DEBUG_INDATA1, "Destination %p moved from PF to reachable with cwnd %d.\n",
	    (void *)net, net->cwnd);
}