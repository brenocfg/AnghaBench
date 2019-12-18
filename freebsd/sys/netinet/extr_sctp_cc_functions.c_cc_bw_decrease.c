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
typedef  scalar_t__ uint8_t ;
typedef  int uint64_t ;
struct sctp_tcb {int /*<<< orphan*/  asoc; } ;
struct TYPE_3__ {int lbw_rtt; scalar_t__ cwnd_at_bw_set; int lbw; int vol_reduce; int step_cnt; int last_step_state; scalar_t__ steady_step; scalar_t__ ret_from_eq; } ;
struct TYPE_4__ {TYPE_1__ rtcc; } ;
struct sctp_nets {scalar_t__ cwnd; int rtt; int flight_size; scalar_t__ ssthresh; scalar_t__ mtu; TYPE_2__ cc_mod; scalar_t__ partial_bytes_acked; } ;

/* Variables and functions */
 scalar_t__ SCTP_INST_GAINING ; 
 scalar_t__ SCTP_INST_LOOSING ; 
 int /*<<< orphan*/  SDT_PROBE5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sctp_nets*,int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int /*<<< orphan*/  cwnd ; 
 int /*<<< orphan*/  rttstep ; 
 int /*<<< orphan*/  rttvar ; 
 int /*<<< orphan*/  sctp ; 
 int /*<<< orphan*/  sctp_enforce_cwnd_limit (int /*<<< orphan*/ *,struct sctp_nets*) ; 

__attribute__((used)) static int
cc_bw_decrease(struct sctp_tcb *stcb, struct sctp_nets *net, uint64_t nbw, uint64_t rtt_offset,
    uint64_t vtag, uint8_t inst_ind)
{
	uint64_t oth, probepoint;

	/* Bandwidth decreased. */
	probepoint = (((uint64_t)net->cwnd) << 32);
	if (net->rtt > net->cc_mod.rtcc.lbw_rtt + rtt_offset) {
		/* rtt increased */
		/* Did we add more */
		if ((net->cwnd > net->cc_mod.rtcc.cwnd_at_bw_set) &&
		    (inst_ind != SCTP_INST_LOOSING)) {
			/* We caused it maybe.. back off? */
			/* PROBE POINT 1 */
			probepoint |= ((1 << 16) | 1);
			SDT_PROBE5(sctp, cwnd, net, rttvar,
			    vtag,
			    ((net->cc_mod.rtcc.lbw << 32) | nbw),
			    ((net->cc_mod.rtcc.lbw_rtt << 32) | net->rtt),
			    net->flight_size,
			    probepoint);
			if (net->cc_mod.rtcc.ret_from_eq) {
				/*
				 * Switch over to CA if we are less
				 * aggressive
				 */
				net->ssthresh = net->cwnd - 1;
				net->partial_bytes_acked = 0;
			}
			return (1);
		}
		/* Probe point 2 */
		probepoint |= ((2 << 16) | 0);
		SDT_PROBE5(sctp, cwnd, net, rttvar,
		    vtag,
		    ((net->cc_mod.rtcc.lbw << 32) | nbw),
		    ((net->cc_mod.rtcc.lbw_rtt << 32) | net->rtt),
		    net->flight_size,
		    probepoint);
		/* Someone else - fight for more? */
		if (net->cc_mod.rtcc.steady_step) {
			oth = net->cc_mod.rtcc.vol_reduce;
			oth <<= 16;
			oth |= net->cc_mod.rtcc.step_cnt;
			oth <<= 16;
			oth |= net->cc_mod.rtcc.last_step_state;
			SDT_PROBE5(sctp, cwnd, net, rttstep,
			    vtag,
			    ((net->cc_mod.rtcc.lbw << 32) | nbw),
			    ((net->cc_mod.rtcc.lbw_rtt << 32) | net->rtt),
			    oth,
			    probepoint);
			/*
			 * Did we voluntarily give up some? if so take one
			 * back please
			 */
			if ((net->cc_mod.rtcc.vol_reduce) &&
			    (inst_ind != SCTP_INST_GAINING)) {
				net->cwnd += net->mtu;
				sctp_enforce_cwnd_limit(&stcb->asoc, net);
				net->cc_mod.rtcc.vol_reduce--;
			}
			net->cc_mod.rtcc.last_step_state = 2;
			net->cc_mod.rtcc.step_cnt = 0;
		}
		goto out_decision;
	} else if (net->rtt < net->cc_mod.rtcc.lbw_rtt - rtt_offset) {
		/* bw & rtt decreased */
		/* Probe point 3 */
		probepoint |= ((3 << 16) | 0);
		SDT_PROBE5(sctp, cwnd, net, rttvar,
		    vtag,
		    ((net->cc_mod.rtcc.lbw << 32) | nbw),
		    ((net->cc_mod.rtcc.lbw_rtt << 32) | net->rtt),
		    net->flight_size,
		    probepoint);
		if (net->cc_mod.rtcc.steady_step) {
			oth = net->cc_mod.rtcc.vol_reduce;
			oth <<= 16;
			oth |= net->cc_mod.rtcc.step_cnt;
			oth <<= 16;
			oth |= net->cc_mod.rtcc.last_step_state;
			SDT_PROBE5(sctp, cwnd, net, rttstep,
			    vtag,
			    ((net->cc_mod.rtcc.lbw << 32) | nbw),
			    ((net->cc_mod.rtcc.lbw_rtt << 32) | net->rtt),
			    oth,
			    probepoint);
			if ((net->cc_mod.rtcc.vol_reduce) &&
			    (inst_ind != SCTP_INST_GAINING)) {
				net->cwnd += net->mtu;
				sctp_enforce_cwnd_limit(&stcb->asoc, net);
				net->cc_mod.rtcc.vol_reduce--;
			}
			net->cc_mod.rtcc.last_step_state = 3;
			net->cc_mod.rtcc.step_cnt = 0;
		}
		goto out_decision;
	}
	/* The bw decreased but rtt stayed the same */
	/* Probe point 4 */
	probepoint |= ((4 << 16) | 0);
	SDT_PROBE5(sctp, cwnd, net, rttvar,
	    vtag,
	    ((net->cc_mod.rtcc.lbw << 32) | nbw),
	    ((net->cc_mod.rtcc.lbw_rtt << 32) | net->rtt),
	    net->flight_size,
	    probepoint);
	if (net->cc_mod.rtcc.steady_step) {
		oth = net->cc_mod.rtcc.vol_reduce;
		oth <<= 16;
		oth |= net->cc_mod.rtcc.step_cnt;
		oth <<= 16;
		oth |= net->cc_mod.rtcc.last_step_state;
		SDT_PROBE5(sctp, cwnd, net, rttstep,
		    vtag,
		    ((net->cc_mod.rtcc.lbw << 32) | nbw),
		    ((net->cc_mod.rtcc.lbw_rtt << 32) | net->rtt),
		    oth,
		    probepoint);
		if ((net->cc_mod.rtcc.vol_reduce) &&
		    (inst_ind != SCTP_INST_GAINING)) {
			net->cwnd += net->mtu;
			sctp_enforce_cwnd_limit(&stcb->asoc, net);
			net->cc_mod.rtcc.vol_reduce--;
		}
		net->cc_mod.rtcc.last_step_state = 4;
		net->cc_mod.rtcc.step_cnt = 0;
	}
out_decision:
	net->cc_mod.rtcc.lbw = nbw;
	net->cc_mod.rtcc.lbw_rtt = net->rtt;
	net->cc_mod.rtcc.cwnd_at_bw_set = net->cwnd;
	if (inst_ind == SCTP_INST_GAINING) {
		return (1);
	} else {
		return (0);
	}
}