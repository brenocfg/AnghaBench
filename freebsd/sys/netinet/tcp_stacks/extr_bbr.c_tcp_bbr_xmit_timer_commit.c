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
typedef  scalar_t__ uint32_t ;
struct tcpcb {int t_srtt; int t_rttvar; int t_rttbest; scalar_t__ t_softerror; int /*<<< orphan*/  t_rxtcur; int /*<<< orphan*/  t_stats; int /*<<< orphan*/  t_rttupdated; } ;
struct TYPE_4__ {scalar_t__ cur_rtt; scalar_t__ ts_in; scalar_t__ rc_lowest_rtt; scalar_t__ rc_min_rto_ms; scalar_t__ bbr_smallest_srtt_this_state; int /*<<< orphan*/  cur_rtt_send_time; int /*<<< orphan*/  bbr_ts_check_our_cts; int /*<<< orphan*/  last_inbound_ts; int /*<<< orphan*/  bbr_ts_check_tstmp; scalar_t__ rc_ack_hdwr_delay; int /*<<< orphan*/  rc_rttprop; } ;
struct tcp_bbr {scalar_t__ rtt_valid; scalar_t__ rc_ts_clock_set; int rc_ts_data_set; TYPE_2__ r_ctl; TYPE_1__* rc_tp; scalar_t__ rc_max_rto_sec; scalar_t__ rc_ack_is_cumack; scalar_t__ rc_ts_valid; scalar_t__ r_init_rtt; scalar_t__ rc_ack_was_delayed; scalar_t__ rc_prtt_set_ts; } ;
typedef  int int32_t ;
struct TYPE_3__ {int /*<<< orphan*/  t_srtt; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSEC_2_TICKS (scalar_t__) ; 
 int /*<<< orphan*/  TCPSTAT_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCPT_RANGESET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TCP_DELTA_SHIFT ; 
 int /*<<< orphan*/  TCP_REXMTVAL (struct tcpcb*) ; 
 int TCP_RTTVAR_SHIFT ; 
 int TCP_RTT_SHIFT ; 
 int TICKS_2_USEC (int /*<<< orphan*/ ) ; 
 int USECS_IN_MSEC ; 
 int USEC_2_TICKS (int) ; 
 int /*<<< orphan*/  VOI_TCP_RTT ; 
 int /*<<< orphan*/  apply_filter_min_small (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bbr_log_rtt_sample (struct tcp_bbr*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bbr_make_timestamp_determination (struct tcp_bbr*) ; 
 int /*<<< orphan*/  filter_increase_by_small (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ get_filter_value_small (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  imax (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stats_voi_update_abs_u32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcps_rttupdated ; 

__attribute__((used)) static void
tcp_bbr_xmit_timer_commit(struct tcp_bbr *bbr, struct tcpcb *tp, uint32_t cts)
{
	int32_t delta;
	uint32_t rtt, tsin;
	int32_t rtt_ticks;


	if (bbr->rtt_valid == 0)
		/* No valid sample */
		return;

	rtt = bbr->r_ctl.cur_rtt;
	tsin = bbr->r_ctl.ts_in;
	if (bbr->rc_prtt_set_ts) {
		/* 
		 * We are to force feed the rttProp filter due
		 * to an entry into PROBE_RTT. This assures
		 * that the times are sync'd between when we
		 * go into PROBE_RTT and the filter expiration.
		 *
		 * Google does not use a true filter, so they do
		 * this implicitly since they only keep one value
		 * and when they enter probe-rtt they update the
		 * value to the newest rtt.
		 */
		uint32_t rtt_prop;
		
		bbr->rc_prtt_set_ts = 0;
		rtt_prop = get_filter_value_small(&bbr->r_ctl.rc_rttprop);
		if (rtt > rtt_prop)
			filter_increase_by_small(&bbr->r_ctl.rc_rttprop, (rtt - rtt_prop), cts);
		else
			apply_filter_min_small(&bbr->r_ctl.rc_rttprop, rtt, cts);	
	}
	if (bbr->rc_ack_was_delayed)
		rtt += bbr->r_ctl.rc_ack_hdwr_delay;

	if (rtt < bbr->r_ctl.rc_lowest_rtt)
		bbr->r_ctl.rc_lowest_rtt = rtt;
	bbr_log_rtt_sample(bbr, rtt, tsin);
	if (bbr->r_init_rtt) {
		/*
		 * The initial rtt is not-trusted, nuke it and lets get
		 * our first valid measurement in.
		 */
		bbr->r_init_rtt = 0;
		tp->t_srtt = 0;
	}
	if ((bbr->rc_ts_clock_set == 0) && bbr->rc_ts_valid) {
		/*
		 * So we have not yet figured out
		 * what the peers TSTMP value is
		 * in (most likely ms). We need a
		 * series of cum-ack's to determine
		 * this reliably.
		 */
		if (bbr->rc_ack_is_cumack) {
			if (bbr->rc_ts_data_set) {
				/* Lets attempt to determine the timestamp granularity. */
				bbr_make_timestamp_determination(bbr);
			} else {
				bbr->rc_ts_data_set = 1;
				bbr->r_ctl.bbr_ts_check_tstmp = bbr->r_ctl.last_inbound_ts;
				bbr->r_ctl.bbr_ts_check_our_cts = bbr->r_ctl.cur_rtt_send_time;
			}
		} else {
			/* 
			 * We have to have consecutive acks 
			 * reset any "filled" state to none.
			 */
			bbr->rc_ts_data_set = 0;
		}
	}
	/* Round it up */
	rtt_ticks = USEC_2_TICKS((rtt + (USECS_IN_MSEC - 1)));
	if (rtt_ticks == 0)
		rtt_ticks = 1;
	if (tp->t_srtt != 0) {
		/*
		 * srtt is stored as fixed point with 5 bits after the
		 * binary point (i.e., scaled by 8).  The following magic is
		 * equivalent to the smoothing algorithm in rfc793 with an
		 * alpha of .875 (srtt = rtt/8 + srtt*7/8 in fixed point).
		 * Adjust rtt to origin 0.
		 */

		delta = ((rtt_ticks - 1) << TCP_DELTA_SHIFT)
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
		tp->t_srtt = rtt_ticks << TCP_RTT_SHIFT;
		tp->t_rttvar = rtt_ticks << (TCP_RTTVAR_SHIFT - 1);
		tp->t_rttbest = tp->t_srtt + tp->t_rttvar;
	}
	TCPSTAT_INC(tcps_rttupdated);
	tp->t_rttupdated++;
#ifdef NETFLIX_STATS
	stats_voi_update_abs_u32(tp->t_stats, VOI_TCP_RTT, imax(0, rtt_ticks));
#endif
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
	    max(MSEC_2_TICKS(bbr->r_ctl.rc_min_rto_ms), rtt_ticks + 2),
	    MSEC_2_TICKS(((uint32_t)bbr->rc_max_rto_sec) * 1000));

	/*
	 * We received an ack for a packet that wasn't retransmitted; it is
	 * probably safe to discard any error indications we've received
	 * recently.  This isn't quite right, but close enough for now (a
	 * route might have failed after we sent a segment, and the return
	 * path might not be symmetrical).
	 */
	tp->t_softerror = 0;
	rtt = (TICKS_2_USEC(bbr->rc_tp->t_srtt) >> TCP_RTT_SHIFT);
	if (bbr->r_ctl.bbr_smallest_srtt_this_state > rtt)
		bbr->r_ctl.bbr_smallest_srtt_this_state = rtt;
}