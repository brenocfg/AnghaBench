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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct tcpcb {int t_srtt; int snd_cwnd; } ;
struct TYPE_2__ {int rc_rack_min_rtt; int rc_rack_largest_cwnd; scalar_t__ rc_gp_hist_filled; scalar_t__* rc_gp_history; } ;
struct tcp_rack {scalar_t__ rack_per_of_gp; scalar_t__ rc_always_pace; int rc_pace_reduce; int r_enforce_min_pace; TYPE_1__ r_ctl; } ;
typedef  int int32_t ;

/* Variables and functions */
 int MSEC_IN_SECOND ; 
 int RACK_GP_HIST ; 
 int TCP_RTT_SHIFT ; 
 int TICKS_2_MSEC (int) ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int ctf_fixed_maxseg (struct tcpcb*) ; 
 int /*<<< orphan*/  rack_calc_nonzero ; 
 int /*<<< orphan*/  rack_calc_zero ; 

__attribute__((used)) static int32_t
rack_get_pacing_delay(struct tcp_rack *rack, struct tcpcb *tp, uint32_t len)
{
	int32_t slot = 0;

	if ((rack->rack_per_of_gp == 0) ||
	    (rack->rc_always_pace == 0)) {
		/*
		 * We use the most optimistic possible cwnd/srtt for
		 * sending calculations. This will make our
		 * calculation anticipate getting more through
		 * quicker then possible. But thats ok we don't want
		 * the peer to have a gap in data sending.
		 */
		uint32_t srtt, cwnd, tr_perms = 0;
		
old_method:
		if (rack->r_ctl.rc_rack_min_rtt)
			srtt = rack->r_ctl.rc_rack_min_rtt;
		else
			srtt = TICKS_2_MSEC((tp->t_srtt >> TCP_RTT_SHIFT));
		if (rack->r_ctl.rc_rack_largest_cwnd)
			cwnd = rack->r_ctl.rc_rack_largest_cwnd;
		else
			cwnd = tp->snd_cwnd;
		tr_perms = cwnd / srtt;
		if (tr_perms == 0) {
			tr_perms = ctf_fixed_maxseg(tp);
		}
		/*
		 * Calculate how long this will take to drain, if
		 * the calculation comes out to zero, thats ok we
		 * will use send_a_lot to possibly spin around for
		 * more increasing tot_len_this_send to the point
		 * that its going to require a pace, or we hit the
		 * cwnd. Which in that case we are just waiting for
		 * a ACK.
		 */
		slot = len / tr_perms;
		/* Now do we reduce the time so we don't run dry? */
		if (slot && rack->rc_pace_reduce) {
			int32_t reduce;
			
			reduce = (slot / rack->rc_pace_reduce);
			if (reduce < slot) {
				slot -= reduce;
			} else
				slot = 0;
		}
	} else {
		int cnt;
		uint64_t bw_est, bw_raise, res, lentim;

		bw_est = 0;
		for (cnt=0; cnt<RACK_GP_HIST; cnt++) {
			if ((rack->r_ctl.rc_gp_hist_filled == 0) &&
			    (rack->r_ctl.rc_gp_history[cnt] == 0))
				break;
			bw_est += rack->r_ctl.rc_gp_history[cnt];
		}
		if (bw_est == 0) {
			/* 
			 * No way yet to make a b/w estimate 
			 * (no goodput est yet).
			 */
			goto old_method;
		}
		/* Covert to bytes per second */
		bw_est *= MSEC_IN_SECOND;
		/* 
		 * Now ratchet it up by our percentage. Note
		 * that the minimum you can do is 1 which would
		 * get you 101% of the average last N goodput estimates.
		 * The max you can do is 256 which would yeild you 
		 * 356% of the last N goodput estimates.
		 */
		bw_raise = bw_est * (uint64_t)rack->rack_per_of_gp;
		bw_est += bw_raise;
		/* average by the number we added */
		bw_est /= cnt;
		/* Now calculate a rate based on this b/w */
		lentim = (uint64_t) len * (uint64_t)MSEC_IN_SECOND;
		res = lentim / bw_est;
		slot = (uint32_t)res;
	}
	if (rack->r_enforce_min_pace &&
	    (slot == 0)) {
		/* We are enforcing a minimum pace time of 1ms */
		slot = rack->r_enforce_min_pace;
	}
	if (slot) 
		counter_u64_add(rack_calc_nonzero, 1);
	else
		counter_u64_add(rack_calc_zero, 1);
	return (slot);
}