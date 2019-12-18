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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct sctphdr {int dummy; } ;
struct TYPE_8__ {scalar_t__ max_burst; } ;
struct sctp_tcb {int rport; TYPE_4__ asoc; TYPE_1__* sctp_ep; } ;
struct TYPE_6__ {int lbw; int lbw_rtt; scalar_t__ ret_from_eq; scalar_t__ last_step_state; scalar_t__ step_cnt; scalar_t__ vol_reduce; scalar_t__ steady_step; scalar_t__ tls_needs_set; scalar_t__ bw_bytes; scalar_t__ bw_tot_time; scalar_t__ bw_bytes_at_last_rttc; scalar_t__ cwnd_at_bw_set; } ;
struct TYPE_7__ {TYPE_2__ rtcc; } ;
struct sctp_nets {int rtt; int cwnd; int mtu; TYPE_3__ cc_mod; int /*<<< orphan*/  flight_size; } ;
struct TYPE_5__ {scalar_t__ sctp_lport; } ;

/* Variables and functions */
 int SCTP_BASE_SYSCTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_INITIAL_CWND ; 
 int /*<<< orphan*/  SDT_PROBE5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sctp_nets*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cwnd ; 
 int /*<<< orphan*/  max (int,int /*<<< orphan*/ ) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rttvar ; 
 int /*<<< orphan*/  sctp ; 
 int /*<<< orphan*/  sctp_initial_cwnd ; 

__attribute__((used)) static void
sctp_cwnd_new_rtcc_transmission_begins(struct sctp_tcb *stcb,
    struct sctp_nets *net)
{
	uint64_t vtag, probepoint;

	if (net->cc_mod.rtcc.lbw) {
		/* Clear the old bw.. we went to 0 in-flight */
		vtag = (net->rtt << 32) | (((uint32_t)(stcb->sctp_ep->sctp_lport)) << 16) |
		    (stcb->rport);
		probepoint = (((uint64_t)net->cwnd) << 32);
		/* Probe point 8 */
		probepoint |= ((8 << 16) | 0);
		SDT_PROBE5(sctp, cwnd, net, rttvar,
		    vtag,
		    ((net->cc_mod.rtcc.lbw << 32) | 0),
		    ((net->cc_mod.rtcc.lbw_rtt << 32) | net->rtt),
		    net->flight_size,
		    probepoint);
		net->cc_mod.rtcc.lbw_rtt = 0;
		net->cc_mod.rtcc.cwnd_at_bw_set = 0;
		net->cc_mod.rtcc.lbw = 0;
		net->cc_mod.rtcc.bw_bytes_at_last_rttc = 0;
		net->cc_mod.rtcc.vol_reduce = 0;
		net->cc_mod.rtcc.bw_tot_time = 0;
		net->cc_mod.rtcc.bw_bytes = 0;
		net->cc_mod.rtcc.tls_needs_set = 0;
		if (net->cc_mod.rtcc.steady_step) {
			net->cc_mod.rtcc.vol_reduce = 0;
			net->cc_mod.rtcc.step_cnt = 0;
			net->cc_mod.rtcc.last_step_state = 0;
		}
		if (net->cc_mod.rtcc.ret_from_eq) {
			/* less aggressive one - reset cwnd too */
			uint32_t cwnd_in_mtu, cwnd;

			cwnd_in_mtu = SCTP_BASE_SYSCTL(sctp_initial_cwnd);
			if (cwnd_in_mtu == 0) {
				/*
				 * Using 0 means that the value of RFC 4960
				 * is used.
				 */
				cwnd = min((net->mtu * 4), max((2 * net->mtu), SCTP_INITIAL_CWND));
			} else {
				/*
				 * We take the minimum of the burst limit
				 * and the initial congestion window.
				 */
				if ((stcb->asoc.max_burst > 0) && (cwnd_in_mtu > stcb->asoc.max_burst))
					cwnd_in_mtu = stcb->asoc.max_burst;
				cwnd = (net->mtu - sizeof(struct sctphdr)) * cwnd_in_mtu;
			}
			if (net->cwnd > cwnd) {
				/*
				 * Only set if we are not a timeout (i.e.
				 * down to 1 mtu)
				 */
				net->cwnd = cwnd;
			}
		}
	}
}