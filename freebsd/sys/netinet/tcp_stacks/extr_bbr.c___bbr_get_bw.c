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
struct TYPE_3__ {int rc_initial_hptsi_bw; scalar_t__ rc_delivered; int r_measurement_count; int rc_lt_bw; int red_bw; int /*<<< orphan*/  rc_delrate; int /*<<< orphan*/  rc_rttprop; } ;
struct tcp_bbr {scalar_t__ rc_bbr_state; int rc_past_init_win; scalar_t__ rc_use_google; TYPE_2__* rc_tp; TYPE_1__ r_ctl; scalar_t__ r_recovery_bw; scalar_t__ rc_lt_use_bw; } ;
struct TYPE_4__ {scalar_t__ t_srtt; scalar_t__ t_peakrate_thr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBR_SRTT ; 
 scalar_t__ BBR_STATE_STARTUP ; 
 int bbr_get_rtt (struct tcp_bbr*,int /*<<< orphan*/ ) ; 
 scalar_t__ bbr_initial_cwnd (struct tcp_bbr*,TYPE_2__*) ; 
 int bbr_min_measurements_req ; 
 int get_filter_value (int /*<<< orphan*/ *) ; 
 scalar_t__ get_filter_value_small (int /*<<< orphan*/ *) ; 
 int uqmin (int,int) ; 

__attribute__((used)) static inline uint64_t
__bbr_get_bw(struct tcp_bbr *bbr)
{
	uint64_t bw, min_bw;
	uint64_t rtt;
	int gm_measure_cnt = 1;
	
	/* 
	 * For startup we make, like google, a
	 * minimum b/w. This is generated from the
	 * IW and the rttProp. We do fall back to srtt
	 * if for some reason (initial handshake) we don't
	 * have a rttProp. We, in the worst case, fall back
	 * to the configured min_bw (rc_initial_hptsi_bw).
	 */
	if (bbr->rc_bbr_state == BBR_STATE_STARTUP) {
		/* Attempt first to use rttProp */
		rtt = (uint64_t)get_filter_value_small(&bbr->r_ctl.rc_rttprop);		
		if (rtt && (rtt < 0xffffffff)) {
measure:
			min_bw = (uint64_t)(bbr_initial_cwnd(bbr, bbr->rc_tp)) *
				((uint64_t)1000000);
			min_bw /= rtt;
			if (min_bw < bbr->r_ctl.rc_initial_hptsi_bw) {
				min_bw = bbr->r_ctl.rc_initial_hptsi_bw;
			}

		} else if (bbr->rc_tp->t_srtt != 0) {
			/* No rttProp, use srtt? */
			rtt = bbr_get_rtt(bbr, BBR_SRTT);
			goto measure;
		} else {
			min_bw = bbr->r_ctl.rc_initial_hptsi_bw;
		}
	} else
		min_bw = 0;

	if ((bbr->rc_past_init_win == 0) &&
	    (bbr->r_ctl.rc_delivered > bbr_initial_cwnd(bbr, bbr->rc_tp)))
		bbr->rc_past_init_win = 1;
	if ((bbr->rc_use_google)  && (bbr->r_ctl.r_measurement_count >= 1))
		gm_measure_cnt = 0;
	if (gm_measure_cnt &&
	    ((bbr->r_ctl.r_measurement_count < bbr_min_measurements_req) ||
	     (bbr->rc_past_init_win == 0))) {
		/* For google we use our guess rate until we get 1 measurement */

use_initial_window:
		rtt = (uint64_t)get_filter_value_small(&bbr->r_ctl.rc_rttprop);
		if (rtt && (rtt < 0xffffffff)) {
			/*
			 * We have an RTT measurment. Use that in
			 * combination with our initial window to calculate
			 * a b/w.
			 */
			bw = (uint64_t)(bbr_initial_cwnd(bbr, bbr->rc_tp)) *
				((uint64_t)1000000);
			bw /= rtt;
			if (bw < bbr->r_ctl.rc_initial_hptsi_bw) {
				bw = bbr->r_ctl.rc_initial_hptsi_bw;
			}
		} else {
			/* Drop back to the 40 and punt to a default */
			bw = bbr->r_ctl.rc_initial_hptsi_bw;
		}
		if (bw < 1)
			/* Probably should panic */
			bw = 1;
		if (bw > min_bw)
			return (bw);
		else
			return (min_bw);
	}
	if (bbr->rc_lt_use_bw)
		bw = bbr->r_ctl.rc_lt_bw;
	else if (bbr->r_recovery_bw && (bbr->rc_use_google == 0))
		bw = bbr->r_ctl.red_bw;
	else
		bw = get_filter_value(&bbr->r_ctl.rc_delrate);
	if (bbr->rc_tp->t_peakrate_thr && (bbr->rc_use_google == 0)) {
		/*
		 * Enforce user set rate limit, keep in mind that
		 * t_peakrate_thr is in B/s already
		 */
		bw = uqmin((uint64_t)bbr->rc_tp->t_peakrate_thr, bw);
	}
	if (bw == 0) {
		/* We should not be at 0, go to the initial window then  */
		goto use_initial_window;
	}
	if (bw < 1)
		/* Probably should panic */
		bw = 1;
	if (bw < min_bw)
		bw = min_bw;
	return (bw);
}