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
typedef  int uint32_t ;
struct TYPE_3__ {int rc_reorder_ts; int rc_reorder_fade; int rc_pkt_delay; int rc_reorder_shift; } ;
struct tcp_bbr {scalar_t__ rc_max_rto_sec; TYPE_2__* rc_tp; TYPE_1__ r_ctl; } ;
struct bbr_sendmap {int dummy; } ;
typedef  int int32_t ;
struct TYPE_4__ {scalar_t__ t_srtt; int /*<<< orphan*/  t_rxtcur; } ;

/* Variables and functions */
 int BBR_INITIAL_RTO ; 
 int /*<<< orphan*/  BBR_TO_FRM_RACK ; 
 scalar_t__ SEQ_GEQ (int,int) ; 
 int TICKS_2_USEC (int /*<<< orphan*/ ) ; 
 int USECS_IN_SECOND ; 
 int /*<<< orphan*/  bbr_log_thresh_choice (struct tcp_bbr*,int,int,int,int,struct bbr_sendmap*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
bbr_calc_thresh_rack(struct tcp_bbr *bbr, uint32_t srtt, uint32_t cts, struct bbr_sendmap *rsm)
{
	/*
	 * lro is the flag we use to determine if we have seen reordering.
	 * If it gets set we have seen reordering. The reorder logic either
	 * works in one of two ways:
	 *
	 * If reorder-fade is configured, then we track the last time we saw
	 * re-ordering occur. If we reach the point where enough time as
	 * passed we no longer consider reordering has occuring.
	 *
	 * Or if reorder-face is 0, then once we see reordering we consider
	 * the connection to alway be subject to reordering and just set lro
	 * to 1.
	 *
	 * In the end if lro is non-zero we add the extra time for
	 * reordering in.
	 */
	int32_t lro;
	uint32_t thresh, t_rxtcur;

	if (srtt == 0)
		srtt = 1;
	if (bbr->r_ctl.rc_reorder_ts) {
		if (bbr->r_ctl.rc_reorder_fade) {
			if (SEQ_GEQ(cts, bbr->r_ctl.rc_reorder_ts)) {
				lro = cts - bbr->r_ctl.rc_reorder_ts;
				if (lro == 0) {
					/*
					 * No time as passed since the last
					 * reorder, mark it as reordering.
					 */
					lro = 1;
				}
			} else {
				/* Negative time? */
				lro = 0;
			}
			if (lro > bbr->r_ctl.rc_reorder_fade) {
				/* Turn off reordering seen too */
				bbr->r_ctl.rc_reorder_ts = 0;
				lro = 0;
			}
		} else {
			/* Reodering does not fade */
			lro = 1;
		}
	} else {
		lro = 0;
	}
	thresh = srtt + bbr->r_ctl.rc_pkt_delay;
	if (lro) {
		/* It must be set, if not you get 1/4 rtt */
		if (bbr->r_ctl.rc_reorder_shift)
			thresh += (srtt >> bbr->r_ctl.rc_reorder_shift);
		else
			thresh += (srtt >> 2);
	} else {
		thresh += 1000;
	}
	/* We don't let the rack timeout be above a RTO */
	if ((bbr->rc_tp)->t_srtt == 0)
		t_rxtcur = BBR_INITIAL_RTO;
	else
		t_rxtcur = TICKS_2_USEC(bbr->rc_tp->t_rxtcur);
	if (thresh > t_rxtcur) {
		thresh = t_rxtcur;
	}
	/* And we don't want it above the RTO max either */
	if (thresh > (((uint32_t)bbr->rc_max_rto_sec) * USECS_IN_SECOND)) {
		thresh = (((uint32_t)bbr->rc_max_rto_sec) * USECS_IN_SECOND);
	}
	bbr_log_thresh_choice(bbr, cts, thresh, lro, srtt, rsm, BBR_TO_FRM_RACK);
	return (thresh);
}