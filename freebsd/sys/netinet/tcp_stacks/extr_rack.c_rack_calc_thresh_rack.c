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
struct tcp_rack {TYPE_2__* rc_tp; TYPE_1__ r_ctl; } ;
typedef  int int32_t ;
struct TYPE_4__ {int /*<<< orphan*/  t_rxtcur; } ;

/* Variables and functions */
 scalar_t__ SEQ_GEQ (int,int) ; 
 int TICKS_2_MSEC (int /*<<< orphan*/ ) ; 
 int rack_rto_max ; 

__attribute__((used)) static uint32_t
rack_calc_thresh_rack(struct tcp_rack *rack, uint32_t srtt, uint32_t cts)
{
	int32_t lro;
	uint32_t thresh;

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
	if (srtt == 0)
		srtt = 1;
	if (rack->r_ctl.rc_reorder_ts) {
		if (rack->r_ctl.rc_reorder_fade) {
			if (SEQ_GEQ(cts, rack->r_ctl.rc_reorder_ts)) {
				lro = cts - rack->r_ctl.rc_reorder_ts;
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
			if (lro > rack->r_ctl.rc_reorder_fade) {
				/* Turn off reordering seen too */
				rack->r_ctl.rc_reorder_ts = 0;
				lro = 0;
			}
		} else {
			/* Reodering does not fade */
			lro = 1;
		}
	} else {
		lro = 0;
	}
	thresh = srtt + rack->r_ctl.rc_pkt_delay;
	if (lro) {
		/* It must be set, if not you get 1/4 rtt */
		if (rack->r_ctl.rc_reorder_shift)
			thresh += (srtt >> rack->r_ctl.rc_reorder_shift);
		else
			thresh += (srtt >> 2);
	} else {
		thresh += 1;
	}
	/* We don't let the rack timeout be above a RTO */
	if (thresh > TICKS_2_MSEC(rack->rc_tp->t_rxtcur)) {
		thresh = TICKS_2_MSEC(rack->rc_tp->t_rxtcur);
	}
	/* And we don't want it above the RTO max either */
	if (thresh > rack_rto_max) {
		thresh = rack_rto_max;
	}
	return (thresh);
}