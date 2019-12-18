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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  rc_rttprop; } ;
struct tcp_bbr {int /*<<< orphan*/  rc_tp; TYPE_1__ r_ctl; } ;

/* Variables and functions */
 int BBR_UNIT ; 
 int /*<<< orphan*/  bbr_cwndtarget_rtt_touse ; 
 int bbr_get_bw_delay_prod (int,int) ; 
 scalar_t__ bbr_get_full_bw (struct tcp_bbr*) ; 
 int bbr_get_rtt (struct tcp_bbr*,int /*<<< orphan*/ ) ; 
 scalar_t__ bbr_initial_cwnd (struct tcp_bbr*,int /*<<< orphan*/ ) ; 
 int get_filter_value_small (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint32_t
bbr_get_raw_target_cwnd(struct tcp_bbr *bbr, uint32_t gain, uint64_t bw)
{
	uint64_t bdp, rtt;
	uint32_t cwnd;

	if ((get_filter_value_small(&bbr->r_ctl.rc_rttprop) == 0xffffffff) ||
	    (bbr_get_full_bw(bbr) == 0)) {
		/* No measurements yet */
		return (bbr_initial_cwnd(bbr, bbr->rc_tp));
	}
	/*
	 * Get bytes per RTT needed (rttProp is normally in
	 * bbr_cwndtarget_rtt_touse)
	 */
	rtt = bbr_get_rtt(bbr, bbr_cwndtarget_rtt_touse);
	/* Get the bdp from the two values */
	bdp = bbr_get_bw_delay_prod(rtt, bw);
	/* Now apply the gain */
	cwnd = (uint32_t)(((bdp * ((uint64_t)gain)) + (uint64_t)(BBR_UNIT - 1)) / ((uint64_t)BBR_UNIT));

	return (cwnd);
}