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
typedef  int /*<<< orphan*/  uint32_t ;
struct tcpcb {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rc_lost; int /*<<< orphan*/  rc_lt_lost; int /*<<< orphan*/  rc_lost_bytes; int /*<<< orphan*/  rc_reorder_ts; } ;
struct tcp_bbr {TYPE_1__ r_ctl; scalar_t__ rc_tlp_rtx_out; } ;
struct bbr_sendmap {int r_flags; scalar_t__ r_start; scalar_t__ r_end; } ;

/* Variables and functions */
 int BBR_CUM_ACKED ; 
 int BBR_HAS_FIN ; 
 int BBR_MARKED_LOST ; 
 int /*<<< orphan*/  BBR_STAT_ADD (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  BBR_STAT_INC (int /*<<< orphan*/ ) ; 
 int BBR_TLP ; 
 int BBR_WAS_SACKPASS ; 
 scalar_t__ SEQ_GT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bbr_badfr ; 
 int /*<<< orphan*/  bbr_badfr_bytes ; 
 int /*<<< orphan*/  bbr_reorder_seen ; 

__attribute__((used)) static void
bbr_earlier_retran(struct tcpcb *tp, struct tcp_bbr *bbr, struct bbr_sendmap *rsm,
		   uint32_t t, uint32_t cts, int ack_type)
{
	/*
	 * For this RSM, we acknowledged the data from a previous
	 * transmission, not the last one we made. This means we did a false
	 * retransmit.
	 */
	if (rsm->r_flags & BBR_HAS_FIN) {
		/*
		 * The sending of the FIN often is multiple sent when we
		 * have everything outstanding ack'd. We ignore this case
		 * since its over now.
		 */
		return;
	}
	if (rsm->r_flags & BBR_TLP) {
		/*
		 * We expect TLP's to have this occur often
		 */
		bbr->rc_tlp_rtx_out = 0;
		return;
	}
	if (ack_type != BBR_CUM_ACKED) {
		/*
		 * If it was not a cum-ack we
		 * don't really know for sure since
		 * the timestamp could be from some
		 * other transmission.
		 */
		return;
	}
		
	if (rsm->r_flags & BBR_WAS_SACKPASS) {
		/*
		 * We retransmitted based on a sack and the earlier
		 * retransmission ack'd it - re-ordering is occuring.
		 */
		BBR_STAT_INC(bbr_reorder_seen);
		bbr->r_ctl.rc_reorder_ts = cts;
	}
	/* Back down the loss count */
	if (rsm->r_flags & BBR_MARKED_LOST) {
		bbr->r_ctl.rc_lost -= rsm->r_end - rsm->r_start;
		bbr->r_ctl.rc_lost_bytes -= rsm->r_end - rsm->r_start;
		rsm->r_flags &= ~BBR_MARKED_LOST;		
		if (SEQ_GT(bbr->r_ctl.rc_lt_lost, bbr->r_ctl.rc_lost))
			/* LT sampling also needs adjustment */
			bbr->r_ctl.rc_lt_lost = bbr->r_ctl.rc_lost;
	}
	/***** RRS HERE ************************/
	/* Do we need to do this???            */
	/* bbr_reset_lt_bw_sampling(bbr, cts); */
	/***** RRS HERE ************************/
	BBR_STAT_INC(bbr_badfr);
	BBR_STAT_ADD(bbr_badfr_bytes, (rsm->r_end - rsm->r_start));
}