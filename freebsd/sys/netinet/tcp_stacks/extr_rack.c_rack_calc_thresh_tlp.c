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
typedef  int uint32_t ;
struct tcpcb {int snd_max; int snd_una; int /*<<< orphan*/  t_rxtcur; } ;
struct TYPE_2__ {int rc_tlp_threshold; int rc_sacked; int rc_holes_rxt; } ;
struct tcp_rack {scalar_t__ rack_tlp_threshold_use; TYPE_1__ r_ctl; } ;
struct rack_sendmap {int r_end; int r_start; int r_rtr_cnt; int* r_tim_lastsent; } ;

/* Variables and functions */
 struct rack_sendmap* TAILQ_PREV (struct rack_sendmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TICKS_2_MSEC (int /*<<< orphan*/ ) ; 
 scalar_t__ TLP_USE_ID ; 
 scalar_t__ TLP_USE_TWO_ONE ; 
 scalar_t__ TLP_USE_TWO_TWO ; 
 scalar_t__ TSTMP_GEQ (int,int) ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int ctf_fixed_maxseg (struct tcpcb*) ; 
 int /*<<< orphan*/  r_tnext ; 
 int rack_delayed_ack_time ; 
 int /*<<< orphan*/  rack_enter_tlp_calc ; 
 int /*<<< orphan*/  rack_head ; 
 int rack_rto_max ; 
 int rack_tlp_min ; 
 int /*<<< orphan*/  rack_used_tlpmethod ; 
 int /*<<< orphan*/  rack_used_tlpmethod2 ; 

__attribute__((used)) static uint32_t
rack_calc_thresh_tlp(struct tcpcb *tp, struct tcp_rack *rack,
		     struct rack_sendmap *rsm, uint32_t srtt)
{
	struct rack_sendmap *prsm;
	uint32_t thresh, len;
	int maxseg;
	
	if (srtt == 0)
		srtt = 1;
	if (rack->r_ctl.rc_tlp_threshold)
		thresh = srtt + (srtt / rack->r_ctl.rc_tlp_threshold);
	else
		thresh = (srtt * 2);
	
	/* Get the previous sent packet, if any  */
	maxseg = ctf_fixed_maxseg(tp);
	counter_u64_add(rack_enter_tlp_calc, 1);
	len = rsm->r_end - rsm->r_start;
	if (rack->rack_tlp_threshold_use == TLP_USE_ID) {
		/* Exactly like the ID */
		if (((tp->snd_max - tp->snd_una) - rack->r_ctl.rc_sacked + rack->r_ctl.rc_holes_rxt) <= maxseg) {
			uint32_t alt_thresh;
			/*
			 * Compensate for delayed-ack with the d-ack time.
			 */
			counter_u64_add(rack_used_tlpmethod, 1);
			alt_thresh = srtt + (srtt / 2) + rack_delayed_ack_time;
			if (alt_thresh > thresh)
				thresh = alt_thresh;
		}
	} else if (rack->rack_tlp_threshold_use == TLP_USE_TWO_ONE) {
		/* 2.1 behavior */
		prsm = TAILQ_PREV(rsm, rack_head, r_tnext);
		if (prsm && (len <= maxseg)) {
			/*
			 * Two packets outstanding, thresh should be (2*srtt) +
			 * possible inter-packet delay (if any).
			 */
			uint32_t inter_gap = 0;
			int idx, nidx;
			
			counter_u64_add(rack_used_tlpmethod, 1);
			idx = rsm->r_rtr_cnt - 1;
			nidx = prsm->r_rtr_cnt - 1;
			if (TSTMP_GEQ(rsm->r_tim_lastsent[nidx], prsm->r_tim_lastsent[idx])) {
				/* Yes it was sent later (or at the same time) */
				inter_gap = rsm->r_tim_lastsent[idx] - prsm->r_tim_lastsent[nidx];
			}
			thresh += inter_gap;
		} else 	if (len <= maxseg) {
			/*
			 * Possibly compensate for delayed-ack.
			 */
			uint32_t alt_thresh;
			
			counter_u64_add(rack_used_tlpmethod2, 1);
			alt_thresh = srtt + (srtt / 2) + rack_delayed_ack_time;
			if (alt_thresh > thresh)
				thresh = alt_thresh;
		}
	} else if (rack->rack_tlp_threshold_use == TLP_USE_TWO_TWO) {
		/* 2.2 behavior */
		if (len <= maxseg) {
			uint32_t alt_thresh;
			/*
			 * Compensate for delayed-ack with the d-ack time.
			 */
			counter_u64_add(rack_used_tlpmethod, 1);
			alt_thresh = srtt + (srtt / 2) + rack_delayed_ack_time;
			if (alt_thresh > thresh)
				thresh = alt_thresh;
		}
	}
 	/* Not above an RTO */
	if (thresh > TICKS_2_MSEC(tp->t_rxtcur)) {
		thresh = TICKS_2_MSEC(tp->t_rxtcur);
	}
	/* Not above a RTO max */
	if (thresh > rack_rto_max) {
		thresh = rack_rto_max;
	}
	/* Apply user supplied min TLP */
	if (thresh < rack_tlp_min) {
		thresh = rack_tlp_min;
	}
	return (thresh);
}