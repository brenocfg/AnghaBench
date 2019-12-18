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
struct TYPE_2__ {int rc_lt_bw; int /*<<< orphan*/  rc_pkt_epoch; int /*<<< orphan*/  rc_lt_epoch_use; int /*<<< orphan*/  rc_bbr_hptsi_gain; } ;
struct tcp_bbr {int rc_lt_use_bw; TYPE_1__ r_ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBR_UNIT ; 
 int /*<<< orphan*/  bbr_log_type_ltbw (struct tcp_bbr*,scalar_t__,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int bbr_lt_bw_diff ; 
 int bbr_lt_bw_ratio ; 
 int /*<<< orphan*/  bbr_reset_lt_bw_interval (struct tcp_bbr*,scalar_t__) ; 

__attribute__((used)) static inline void
bbr_lt_bw_samp_done(struct tcp_bbr *bbr, uint64_t bw, uint32_t cts, uint32_t timin)
{
	uint64_t diff;

	/* Do we have a previous sample? */
	if (bbr->r_ctl.rc_lt_bw) {
		/* Get the diff in bytes per second */
		if (bbr->r_ctl.rc_lt_bw > bw)
			diff = bbr->r_ctl.rc_lt_bw - bw;
		else
			diff = bw - bbr->r_ctl.rc_lt_bw;
		if ((diff <= bbr_lt_bw_diff) ||
		    (diff <= (bbr->r_ctl.rc_lt_bw / bbr_lt_bw_ratio))) {
			/* Consider us policed */
			uint32_t saved_bw;

			saved_bw = (uint32_t)bbr->r_ctl.rc_lt_bw;
			bbr->r_ctl.rc_lt_bw = (bw + bbr->r_ctl.rc_lt_bw) / 2;	/* average of two */
			bbr->rc_lt_use_bw = 1;
			bbr->r_ctl.rc_bbr_hptsi_gain = BBR_UNIT;
			/*
			 * Use pkt based epoch for measuring length of
			 * policer up
			 */
			bbr->r_ctl.rc_lt_epoch_use = bbr->r_ctl.rc_pkt_epoch;
			/*
			 * reason 4 is we need to start consider being
			 * policed
			 */
			bbr_log_type_ltbw(bbr, cts, 4, (uint32_t)bw, saved_bw, (uint32_t)diff, timin);
			return;
		}
	}
	bbr->r_ctl.rc_lt_bw = bw;
	bbr_reset_lt_bw_interval(bbr, cts);
	bbr_log_type_ltbw(bbr, cts, 5, 0, (uint32_t)bw, 0, timin);
}