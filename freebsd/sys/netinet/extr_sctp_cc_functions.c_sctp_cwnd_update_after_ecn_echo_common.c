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
struct TYPE_7__ {int /*<<< orphan*/  my_vtag; } ;
struct sctp_tcb {int rport; TYPE_4__* sctp_ep; TYPE_3__ asoc; } ;
struct TYPE_5__ {scalar_t__ use_dccc_ecn; } ;
struct TYPE_6__ {TYPE_1__ rtcc; } ;
struct sctp_nets {int cwnd; scalar_t__ lan_type; int ecn_prev_cwnd; int mtu; int ssthresh; int RTO; TYPE_2__ cc_mod; } ;
struct TYPE_8__ {int sctp_lport; } ;

/* Variables and functions */
 int SCTP_BASE_SYSCTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_CWND_LOG_FROM_SAT ; 
 int SCTP_CWND_MONITOR_ENABLE ; 
 scalar_t__ SCTP_LAN_LOCAL ; 
 int /*<<< orphan*/  SCTP_STAT_INCR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDT_PROBE5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sctp_nets*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct sctp_nets*,int,int) ; 
 int /*<<< orphan*/  cwnd ; 
 int /*<<< orphan*/  ecn ; 
 int /*<<< orphan*/  sctp ; 
 int /*<<< orphan*/  sctp_log_cwnd (struct sctp_tcb*,struct sctp_nets*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_logging_level ; 
 int /*<<< orphan*/  sctps_ecnereducedcwnd ; 

__attribute__((used)) static void
sctp_cwnd_update_after_ecn_echo_common(struct sctp_tcb *stcb, struct sctp_nets *net,
    int in_window, int num_pkt_lost, int use_rtcc)
{
	int old_cwnd = net->cwnd;

	if ((use_rtcc) && (net->lan_type == SCTP_LAN_LOCAL) && (net->cc_mod.rtcc.use_dccc_ecn)) {
		/* Data center Congestion Control */
		if (in_window == 0) {
			/*
			 * Go to CA with the cwnd at the point we sent the
			 * TSN that was marked with a CE.
			 */
			if (net->ecn_prev_cwnd < net->cwnd) {
				/* Restore to prev cwnd */
				net->cwnd = net->ecn_prev_cwnd - (net->mtu * num_pkt_lost);
			} else {
				/* Just cut in 1/2 */
				net->cwnd /= 2;
			}
			/* Drop to CA */
			net->ssthresh = net->cwnd - (num_pkt_lost * net->mtu);
			if (SCTP_BASE_SYSCTL(sctp_logging_level) & SCTP_CWND_MONITOR_ENABLE) {
				sctp_log_cwnd(stcb, net, (net->cwnd - old_cwnd), SCTP_CWND_LOG_FROM_SAT);
			}
		} else {
			/*
			 * Further tuning down required over the drastic
			 * original cut
			 */
			net->ssthresh -= (net->mtu * num_pkt_lost);
			net->cwnd -= (net->mtu * num_pkt_lost);
			if (SCTP_BASE_SYSCTL(sctp_logging_level) & SCTP_CWND_MONITOR_ENABLE) {
				sctp_log_cwnd(stcb, net, (net->cwnd - old_cwnd), SCTP_CWND_LOG_FROM_SAT);
			}

		}
		SCTP_STAT_INCR(sctps_ecnereducedcwnd);
	} else {
		if (in_window == 0) {
			SCTP_STAT_INCR(sctps_ecnereducedcwnd);
			net->ssthresh = net->cwnd / 2;
			if (net->ssthresh < net->mtu) {
				net->ssthresh = net->mtu;
				/*
				 * here back off the timer as well, to slow
				 * us down
				 */
				net->RTO <<= 1;
			}
			net->cwnd = net->ssthresh;
			SDT_PROBE5(sctp, cwnd, net, ecn,
			    stcb->asoc.my_vtag,
			    ((stcb->sctp_ep->sctp_lport << 16) | (stcb->rport)),
			    net,
			    old_cwnd, net->cwnd);
			if (SCTP_BASE_SYSCTL(sctp_logging_level) & SCTP_CWND_MONITOR_ENABLE) {
				sctp_log_cwnd(stcb, net, (net->cwnd - old_cwnd), SCTP_CWND_LOG_FROM_SAT);
			}
		}
	}

}