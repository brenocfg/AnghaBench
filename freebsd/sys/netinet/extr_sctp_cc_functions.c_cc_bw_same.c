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
struct sctp_tcb {int dummy; } ;
struct TYPE_3__ {int lbw_rtt; int lbw; int steady_step; int last_step_state; int step_cnt; int vol_reduce; int cwnd_at_bw_set; int ret_from_eq; } ;
struct TYPE_4__ {TYPE_1__ rtcc; } ;
struct sctp_nets {int cwnd; int rtt; int flight_size; int mtu; TYPE_2__ cc_mod; } ;

/* Variables and functions */
 scalar_t__ SCTP_INST_GAINING ; 
 scalar_t__ SCTP_INST_LOOSING ; 
 scalar_t__ SCTP_INST_NEUTRAL ; 
 int /*<<< orphan*/  SDT_PROBE5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sctp_nets*,int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int /*<<< orphan*/  cwnd ; 
 int /*<<< orphan*/  rttstep ; 
 int /*<<< orphan*/  rttvar ; 
 int /*<<< orphan*/  sctp ; 

__attribute__((used)) static int
cc_bw_same(struct sctp_tcb *stcb, struct sctp_nets *net, uint64_t nbw,
    uint64_t rtt_offset, uint64_t vtag, uint8_t inst_ind)
{
	uint64_t oth, probepoint;

	probepoint = (((uint64_t)net->cwnd) << 32);
	if (net->rtt > net->cc_mod.rtcc.lbw_rtt + rtt_offset) {
		/*
		 * rtt increased we don't update bw.. so we don't update the
		 * rtt either.
		 */
		/* Probe point 5 */
		probepoint |= ((5 << 16) | 1);
		SDT_PROBE5(sctp, cwnd, net, rttvar,
		    vtag,
		    ((net->cc_mod.rtcc.lbw << 32) | nbw),
		    ((net->cc_mod.rtcc.lbw_rtt << 32) | net->rtt),
		    net->flight_size,
		    probepoint);
		if ((net->cc_mod.rtcc.steady_step) && (inst_ind != SCTP_INST_LOOSING)) {
			if (net->cc_mod.rtcc.last_step_state == 5)
				net->cc_mod.rtcc.step_cnt++;
			else
				net->cc_mod.rtcc.step_cnt = 1;
			net->cc_mod.rtcc.last_step_state = 5;
			if ((net->cc_mod.rtcc.step_cnt == net->cc_mod.rtcc.steady_step) ||
			    ((net->cc_mod.rtcc.step_cnt > net->cc_mod.rtcc.steady_step) &&
			    ((net->cc_mod.rtcc.step_cnt % net->cc_mod.rtcc.steady_step) == 0))) {
				/* Try a step down */
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
				if (net->cwnd > (4 * net->mtu)) {
					net->cwnd -= net->mtu;
					net->cc_mod.rtcc.vol_reduce++;
				} else {
					net->cc_mod.rtcc.step_cnt = 0;
				}
			}
		}
		return (1);
	}
	if (net->rtt < net->cc_mod.rtcc.lbw_rtt - rtt_offset) {
		/*
		 * rtt decreased, there could be more room. we update both
		 * the bw and the rtt here to lock this in as a good step
		 * down.
		 */
		/* Probe point 6 */
		probepoint |= ((6 << 16) | 0);
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
			if ((net->cc_mod.rtcc.last_step_state == 5) &&
			    (net->cc_mod.rtcc.step_cnt > net->cc_mod.rtcc.steady_step)) {
				/* Step down worked */
				net->cc_mod.rtcc.step_cnt = 0;
				return (1);
			} else {
				net->cc_mod.rtcc.last_step_state = 6;
				net->cc_mod.rtcc.step_cnt = 0;
			}
		}
		net->cc_mod.rtcc.lbw = nbw;
		net->cc_mod.rtcc.lbw_rtt = net->rtt;
		net->cc_mod.rtcc.cwnd_at_bw_set = net->cwnd;
		if (inst_ind == SCTP_INST_GAINING)
			return (1);
		else if (inst_ind == SCTP_INST_NEUTRAL)
			return (1);
		else
			return (0);
	}
	/*
	 * Ok bw and rtt remained the same .. no update to any
	 */
	/* Probe point 7 */
	probepoint |= ((7 << 16) | net->cc_mod.rtcc.ret_from_eq);
	SDT_PROBE5(sctp, cwnd, net, rttvar,
	    vtag,
	    ((net->cc_mod.rtcc.lbw << 32) | nbw),
	    ((net->cc_mod.rtcc.lbw_rtt << 32) | net->rtt),
	    net->flight_size,
	    probepoint);
	if ((net->cc_mod.rtcc.steady_step) && (inst_ind != SCTP_INST_LOOSING)) {
		if (net->cc_mod.rtcc.last_step_state == 5)
			net->cc_mod.rtcc.step_cnt++;
		else
			net->cc_mod.rtcc.step_cnt = 1;
		net->cc_mod.rtcc.last_step_state = 5;
		if ((net->cc_mod.rtcc.step_cnt == net->cc_mod.rtcc.steady_step) ||
		    ((net->cc_mod.rtcc.step_cnt > net->cc_mod.rtcc.steady_step) &&
		    ((net->cc_mod.rtcc.step_cnt % net->cc_mod.rtcc.steady_step) == 0))) {
			/* Try a step down */
			if (net->cwnd > (4 * net->mtu)) {
				net->cwnd -= net->mtu;
				net->cc_mod.rtcc.vol_reduce++;
				return (1);
			} else {
				net->cc_mod.rtcc.step_cnt = 0;
			}
		}
	}
	if (inst_ind == SCTP_INST_GAINING)
		return (1);
	else if (inst_ind == SCTP_INST_NEUTRAL)
		return (1);
	else
		return ((int)net->cc_mod.rtcc.ret_from_eq);
}