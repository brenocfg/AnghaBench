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
typedef  int uint64_t ;
struct sctp_tcb {int dummy; } ;
struct TYPE_3__ {int lbw; int lbw_rtt; int vol_reduce; int step_cnt; int last_step_state; scalar_t__ cwnd_at_bw_set; scalar_t__ steady_step; } ;
struct TYPE_4__ {TYPE_1__ rtcc; } ;
struct sctp_nets {int rtt; int flight_size; scalar_t__ cwnd; TYPE_2__ cc_mod; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDT_PROBE5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sctp_nets*,int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int /*<<< orphan*/  cwnd ; 
 int /*<<< orphan*/  rttstep ; 
 int /*<<< orphan*/  rttvar ; 
 int /*<<< orphan*/  sctp ; 

__attribute__((used)) static int
cc_bw_increase(struct sctp_tcb *stcb, struct sctp_nets *net, uint64_t nbw, uint64_t vtag)
{
	uint64_t oth, probepoint;

	/*
	 * BW increased, so update and return 0, since all actions in our
	 * table say to do the normal CC update. Note that we pay no
	 * attention to the inst_ind since our overall sum is increasing.
	 */
	/* PROBE POINT 0 */
	probepoint = (((uint64_t)net->cwnd) << 32);
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
		net->cc_mod.rtcc.last_step_state = 0;
		net->cc_mod.rtcc.step_cnt = 0;
		net->cc_mod.rtcc.vol_reduce = 0;
	}
	net->cc_mod.rtcc.lbw = nbw;
	net->cc_mod.rtcc.lbw_rtt = net->rtt;
	net->cc_mod.rtcc.cwnd_at_bw_set = net->cwnd;
	return (0);
}