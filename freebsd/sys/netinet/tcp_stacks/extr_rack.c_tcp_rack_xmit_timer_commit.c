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
typedef  int uint32_t ;
struct tcpcb {int t_srtt; int t_rttvar; int t_rttbest; scalar_t__ t_softerror; int /*<<< orphan*/  t_rxtcur; scalar_t__ t_rxtshift; int /*<<< orphan*/  t_stats; int /*<<< orphan*/  t_rttupdated; scalar_t__ t_fb_ptr; } ;
struct TYPE_3__ {int rs_flags; int rs_rtt_lowest; int rs_rtt_highest; int rs_rtt_tot; scalar_t__ rs_rtt_cnt; } ;
struct TYPE_4__ {scalar_t__ rc_rate_sample_method; TYPE_1__ rack_rs; } ;
struct tcp_rack {TYPE_2__ r_ctl; } ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSEC_2_TICKS (int /*<<< orphan*/ ) ; 
 int RACK_RTT_EMPTY ; 
 int /*<<< orphan*/  TCPSTAT_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCPT_RANGESET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TCP_DELTA_SHIFT ; 
 int /*<<< orphan*/  TCP_REXMTVAL (struct tcpcb*) ; 
 int TCP_RTTVAR_SHIFT ; 
 int TCP_RTT_SHIFT ; 
 scalar_t__ USE_RTT_AVG ; 
 scalar_t__ USE_RTT_HIGH ; 
 scalar_t__ USE_RTT_LOW ; 
 int /*<<< orphan*/  VOI_TCP_RTT ; 
 int /*<<< orphan*/  imax (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*,scalar_t__) ; 
 int /*<<< orphan*/  rack_log_rtt_sample (struct tcp_rack*,int) ; 
 int /*<<< orphan*/  rack_log_rtt_upd (struct tcpcb*,struct tcp_rack*,int,int,int) ; 
 int /*<<< orphan*/  rack_rto_max ; 
 int /*<<< orphan*/  rack_rto_min ; 
 int /*<<< orphan*/  stats_voi_update_abs_u32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcps_rttupdated ; 

__attribute__((used)) static void
tcp_rack_xmit_timer_commit(struct tcp_rack *rack, struct tcpcb *tp)
{
	int32_t delta;
	uint32_t o_srtt, o_var;
	int32_t rtt;

	if (rack->r_ctl.rack_rs.rs_flags & RACK_RTT_EMPTY)
		/* No valid sample */
		return;
	if (rack->r_ctl.rc_rate_sample_method == USE_RTT_LOW) {
		/* We are to use the lowest RTT seen in a single ack */
		rtt = rack->r_ctl.rack_rs.rs_rtt_lowest;
	} else if (rack->r_ctl.rc_rate_sample_method == USE_RTT_HIGH) {
		/* We are to use the highest RTT seen in a single ack */
		rtt = rack->r_ctl.rack_rs.rs_rtt_highest;
	} else if (rack->r_ctl.rc_rate_sample_method == USE_RTT_AVG) {
		/* We are to use the average RTT seen in a single ack */
		rtt = (int32_t)(rack->r_ctl.rack_rs.rs_rtt_tot /
				(uint64_t)rack->r_ctl.rack_rs.rs_rtt_cnt);
	} else {
#ifdef INVARIANTS
		panic("Unknown rtt variant %d", rack->r_ctl.rc_rate_sample_method);
#endif		
		return;
	}
	if (rtt == 0)
		rtt = 1;
	rack_log_rtt_sample(rack, rtt);
	o_srtt = tp->t_srtt;
	o_var = tp->t_rttvar;
	rack = (struct tcp_rack *)tp->t_fb_ptr;
	if (tp->t_srtt != 0) {
		/*
		 * srtt is stored as fixed point with 5 bits after the
		 * binary point (i.e., scaled by 8).  The following magic is
		 * equivalent to the smoothing algorithm in rfc793 with an
		 * alpha of .875 (srtt = rtt/8 + srtt*7/8 in fixed point).
		 * Adjust rtt to origin 0.
		 */
		delta = ((rtt - 1) << TCP_DELTA_SHIFT)
		    - (tp->t_srtt >> (TCP_RTT_SHIFT - TCP_DELTA_SHIFT));

		tp->t_srtt += delta;
		if (tp->t_srtt <= 0)
			tp->t_srtt = 1;

		/*
		 * We accumulate a smoothed rtt variance (actually, a
		 * smoothed mean difference), then set the retransmit timer
		 * to smoothed rtt + 4 times the smoothed variance. rttvar
		 * is stored as fixed point with 4 bits after the binary
		 * point (scaled by 16).  The following is equivalent to
		 * rfc793 smoothing with an alpha of .75 (rttvar =
		 * rttvar*3/4 + |delta| / 4).  This replaces rfc793's
		 * wired-in beta.
		 */
		if (delta < 0)
			delta = -delta;
		delta -= tp->t_rttvar >> (TCP_RTTVAR_SHIFT - TCP_DELTA_SHIFT);
		tp->t_rttvar += delta;
		if (tp->t_rttvar <= 0)
			tp->t_rttvar = 1;
		if (tp->t_rttbest > tp->t_srtt + tp->t_rttvar)
			tp->t_rttbest = tp->t_srtt + tp->t_rttvar;
	} else {
		/*
		 * No rtt measurement yet - use the unsmoothed rtt. Set the
		 * variance to half the rtt (so our first retransmit happens
		 * at 3*rtt).
		 */
		tp->t_srtt = rtt << TCP_RTT_SHIFT;
		tp->t_rttvar = rtt << (TCP_RTTVAR_SHIFT - 1);
		tp->t_rttbest = tp->t_srtt + tp->t_rttvar;
	}
	TCPSTAT_INC(tcps_rttupdated);
	rack_log_rtt_upd(tp, rack, rtt, o_srtt, o_var);
	tp->t_rttupdated++;
#ifdef NETFLIX_STATS
	stats_voi_update_abs_u32(tp->t_stats, VOI_TCP_RTT, imax(0, rtt));
#endif
	tp->t_rxtshift = 0;

	/*
	 * the retransmit should happen at rtt + 4 * rttvar. Because of the
	 * way we do the smoothing, srtt and rttvar will each average +1/2
	 * tick of bias.  When we compute the retransmit timer, we want 1/2
	 * tick of rounding and 1 extra tick because of +-1/2 tick
	 * uncertainty in the firing of the timer.  The bias will give us
	 * exactly the 1.5 tick we need.  But, because the bias is
	 * statistical, we have to test that we don't drop below the minimum
	 * feasible timer (which is 2 ticks).
	 */
	TCPT_RANGESET(tp->t_rxtcur, TCP_REXMTVAL(tp),
	   max(MSEC_2_TICKS(rack_rto_min), rtt + 2), MSEC_2_TICKS(rack_rto_max));
	tp->t_softerror = 0;
}