#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
struct tcpcb {int t_maxseg; scalar_t__ t_srtt; int /*<<< orphan*/  t_rxtcur; } ;
struct tcp_bbr {int rc_tlp_threshold; int rc_last_options; scalar_t__ rc_max_rto_sec; } ;
struct bbr_sendmap {int r_end; int r_start; int r_rtr_cnt; int* r_tim_lastsent; } ;

/* Variables and functions */
 int BBR_INITIAL_RTO ; 
 int /*<<< orphan*/  BBR_TO_FRM_TLP ; 
 struct bbr_sendmap* TAILQ_PREV (struct bbr_sendmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TICKS_2_USEC (int /*<<< orphan*/ ) ; 
 scalar_t__ TSTMP_GEQ (int,int) ; 
 int USECS_IN_SECOND ; 
 int bbr_delayed_ack_time ; 
 int /*<<< orphan*/  bbr_head ; 
 int /*<<< orphan*/  bbr_log_thresh_choice (struct tcp_bbr*,int,int,int,int,struct bbr_sendmap*,int /*<<< orphan*/ ) ; 
 int bbr_tlp_min ; 
 int /*<<< orphan*/  r_tnext ; 

__attribute__((used)) static uint32_t
bbr_calc_thresh_tlp(struct tcpcb *tp, struct tcp_bbr *bbr,
    struct bbr_sendmap *rsm, uint32_t srtt,
    uint32_t cts)
{
	uint32_t thresh, len, maxseg, t_rxtcur;
	struct bbr_sendmap *prsm;

	if (srtt == 0)
		srtt = 1;
	if (bbr->rc_tlp_threshold)
		thresh = srtt + (srtt / bbr->rc_tlp_threshold);
	else
		thresh = (srtt * 2);
	maxseg = tp->t_maxseg - bbr->rc_last_options;
	/* Get the previous sent packet, if any  */
	len = rsm->r_end - rsm->r_start;

	/* 2.1 behavior */
	prsm = TAILQ_PREV(rsm, bbr_head, r_tnext);
	if (prsm && (len <= maxseg)) {
		/*
		 * Two packets outstanding, thresh should be (2*srtt) +
		 * possible inter-packet delay (if any).
		 */
		uint32_t inter_gap = 0;
		int idx, nidx;

		idx = rsm->r_rtr_cnt - 1;
		nidx = prsm->r_rtr_cnt - 1;
		if (TSTMP_GEQ(rsm->r_tim_lastsent[nidx], prsm->r_tim_lastsent[idx])) {
			/* Yes it was sent later (or at the same time) */
			inter_gap = rsm->r_tim_lastsent[idx] - prsm->r_tim_lastsent[nidx];
		}
		thresh += inter_gap;
	} else if (len <= maxseg) {
		/*
		 * Possibly compensate for delayed-ack.
		 */
		uint32_t alt_thresh;

		alt_thresh = srtt + (srtt / 2) + bbr_delayed_ack_time;
		if (alt_thresh > thresh)
			thresh = alt_thresh;
	}
	/* Not above the current  RTO */
	if (tp->t_srtt == 0)
		t_rxtcur = BBR_INITIAL_RTO;
	else
		t_rxtcur = TICKS_2_USEC(tp->t_rxtcur);

	bbr_log_thresh_choice(bbr, cts, thresh, t_rxtcur, srtt, rsm, BBR_TO_FRM_TLP);
	/* Not above an RTO */
	if (thresh > t_rxtcur) {
		thresh = t_rxtcur;
	}
	/* Not above a RTO max */
	if (thresh > (((uint32_t)bbr->rc_max_rto_sec) * USECS_IN_SECOND)) {
		thresh = (((uint32_t)bbr->rc_max_rto_sec) * USECS_IN_SECOND);
	}
	/* And now apply the user TLP min */
	if (thresh < bbr_tlp_min) {
		thresh = bbr_tlp_min;
	}
	return (thresh);
}