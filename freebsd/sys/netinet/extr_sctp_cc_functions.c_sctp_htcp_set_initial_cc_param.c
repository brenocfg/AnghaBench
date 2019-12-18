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
struct TYPE_2__ {int /*<<< orphan*/  peers_rwnd; } ;
struct sctp_tcb {TYPE_1__ asoc; } ;
struct sctp_nets {int mtu; int /*<<< orphan*/  ssthresh; int /*<<< orphan*/  cwnd; } ;

/* Variables and functions */
 int SCTP_BASE_SYSCTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_CWND_INITIALIZATION ; 
 int SCTP_CWND_LOGGING_ENABLE ; 
 int SCTP_CWND_MONITOR_ENABLE ; 
 int /*<<< orphan*/  SCTP_INITIAL_CWND ; 
 int /*<<< orphan*/  htcp_init (struct sctp_nets*) ; 
 int /*<<< orphan*/  max (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_enforce_cwnd_limit (TYPE_1__*,struct sctp_nets*) ; 
 int /*<<< orphan*/  sctp_log_cwnd (struct sctp_tcb*,struct sctp_nets*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_logging_level ; 

__attribute__((used)) static void
sctp_htcp_set_initial_cc_param(struct sctp_tcb *stcb, struct sctp_nets *net)
{
	/*
	 * We take the max of the burst limit times a MTU or the
	 * INITIAL_CWND. We then limit this to 4 MTU's of sending.
	 */
	net->cwnd = min((net->mtu * 4), max((2 * net->mtu), SCTP_INITIAL_CWND));
	net->ssthresh = stcb->asoc.peers_rwnd;
	sctp_enforce_cwnd_limit(&stcb->asoc, net);
	htcp_init(net);

	if (SCTP_BASE_SYSCTL(sctp_logging_level) & (SCTP_CWND_MONITOR_ENABLE | SCTP_CWND_LOGGING_ENABLE)) {
		sctp_log_cwnd(stcb, net, 0, SCTP_CWND_INITIALIZATION);
	}
}