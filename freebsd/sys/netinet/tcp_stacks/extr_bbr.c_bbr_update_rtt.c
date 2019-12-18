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
struct tcpopt {scalar_t__ to_tsecr; int to_flags; } ;
struct tcpcb {int dummy; } ;
struct TYPE_2__ {int rc_last_rtt; int rc_lowest_rtt; } ;
struct tcp_bbr {int rc_use_google; scalar_t__ rc_tlp_rtx_out; TYPE_1__ r_ctl; int /*<<< orphan*/  rc_tv; } ;
struct bbr_sendmap {int r_flags; int r_rtr_cnt; int* r_tim_lastsent; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int BBR_ACKED ; 
 scalar_t__ BBR_CUM_ACKED ; 
 int BBR_OVERMAX ; 
 int /*<<< orphan*/  BBR_RTT_BY_EARLIER_RET ; 
 int /*<<< orphan*/  BBR_RTT_BY_EXACTMATCH ; 
 int /*<<< orphan*/  BBR_RTT_BY_SOME_RETRAN ; 
 int /*<<< orphan*/  BBR_RTT_BY_THIS_RETRAN ; 
 int /*<<< orphan*/  BBR_RTT_BY_TIMESTAMP ; 
 int /*<<< orphan*/  BBR_RTT_BY_TSMATCHING ; 
 int BBR_RXT_CLEARED ; 
 int BBR_TIMER_FUDGE ; 
 int BBR_TLP ; 
 int BBR_WAS_RENEGED ; 
 int MS_IN_USEC ; 
 scalar_t__ SEQ_GEQ (int,int) ; 
 scalar_t__ SEQ_LEQ (int,int) ; 
 int TOF_TS ; 
 scalar_t__ TSTMP_GT (int,int) ; 
 int bbr_can_use_ts_for_rtt ; 
 int /*<<< orphan*/  bbr_earlier_retran (struct tcpcb*,struct tcp_bbr*,struct bbr_sendmap*,int,int,scalar_t__) ; 
 int bbr_ts_convert (scalar_t__) ; 
 int /*<<< orphan*/  bbr_update_bbr_info (struct tcp_bbr*,struct bbr_sendmap*,int,int,scalar_t__,int,int /*<<< orphan*/ ,int,scalar_t__,struct tcpopt*) ; 
 int /*<<< orphan*/  panic (char*,struct bbr_sendmap*,struct tcp_bbr*,int) ; 
 int tcp_tv_to_mssectick (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bbr_update_rtt(struct tcpcb *tp, struct tcp_bbr *bbr,
    struct bbr_sendmap *rsm, struct tcpopt *to, uint32_t cts, int32_t ack_type, uint32_t th_ack)
{
	int32_t i;
	uint32_t t, uts = 0;

	if ((rsm->r_flags & BBR_ACKED) ||
	    (rsm->r_flags & BBR_WAS_RENEGED) ||
	    (rsm->r_flags & BBR_RXT_CLEARED)) {
		/* Already done */
		return (0);
	}
	if (rsm->r_rtr_cnt == 1) {
		/*
		 * Only one transmit. Hopefully the normal case.
		 */
		if (TSTMP_GT(cts, rsm->r_tim_lastsent[0]))
			t = cts - rsm->r_tim_lastsent[0];
		else
			t = 1;
		if ((int)t <= 0)
			t = 1;
		bbr->r_ctl.rc_last_rtt = t;
		bbr_update_bbr_info(bbr, rsm, t, cts, to->to_tsecr, 0,
				    BBR_RTT_BY_EXACTMATCH, rsm->r_tim_lastsent[0], ack_type, to);
		return (1);
	}
	/* Convert to usecs */
	if ((bbr_can_use_ts_for_rtt == 1) &&
	    (bbr->rc_use_google == 1) &&
	    (ack_type == BBR_CUM_ACKED) &&
	    (to->to_flags & TOF_TS) &&
	    (to->to_tsecr != 0)) {

		t = tcp_tv_to_mssectick(&bbr->rc_tv) - to->to_tsecr;
		if (t < 1)
			t = 1;
		t *= MS_IN_USEC;
		bbr_update_bbr_info(bbr, rsm, t, cts, to->to_tsecr, 0,
				    BBR_RTT_BY_TIMESTAMP,
				    rsm->r_tim_lastsent[(rsm->r_rtr_cnt-1)],
				    ack_type, to);
		return (1);
	}
	uts = bbr_ts_convert(to->to_tsecr);
	if ((to->to_flags & TOF_TS) &&
	    (to->to_tsecr != 0) &&
	    (ack_type == BBR_CUM_ACKED) &&
	    ((rsm->r_flags & BBR_OVERMAX) == 0)) {
		/*
		 * Now which timestamp does it match? In this block the ACK
		 * may be coming from a previous transmission.
		 */
		uint32_t fudge;

		fudge = BBR_TIMER_FUDGE;
		for (i = 0; i < rsm->r_rtr_cnt; i++) {
			if ((SEQ_GEQ(uts, (rsm->r_tim_lastsent[i] - fudge))) &&
			    (SEQ_LEQ(uts, (rsm->r_tim_lastsent[i] + fudge)))) {
				if (TSTMP_GT(cts, rsm->r_tim_lastsent[i]))
					t = cts - rsm->r_tim_lastsent[i];
				else
					t = 1;
				if ((int)t <= 0)
					t = 1;
				bbr->r_ctl.rc_last_rtt = t;
				bbr_update_bbr_info(bbr, rsm, t, cts, to->to_tsecr, uts, BBR_RTT_BY_TSMATCHING,
						    rsm->r_tim_lastsent[i], ack_type, to);
				if ((i + 1) < rsm->r_rtr_cnt) {
					/* Likely */
					bbr_earlier_retran(tp, bbr, rsm, t, cts, ack_type);
				} else if (rsm->r_flags & BBR_TLP) {
					bbr->rc_tlp_rtx_out = 0;
				}
				return (1);
			}
		}
		/* Fall through if we can't find a matching timestamp */
	}
	/*
	 * Ok its a SACK block that we retransmitted. or a windows
	 * machine without timestamps. We can tell nothing from the
	 * time-stamp since its not there or the time the peer last
	 * recieved a segment that moved forward its cum-ack point.
	 *
	 * Lets look at the last retransmit and see what we can tell
	 * (with BBR for space we only keep 2 note we have to keep
	 * at least 2 so the map can not be condensed more).
	 */
	i = rsm->r_rtr_cnt - 1;
	if (TSTMP_GT(cts, rsm->r_tim_lastsent[i]))
		t = cts - rsm->r_tim_lastsent[i];
	else
		goto not_sure;
	if (t < bbr->r_ctl.rc_lowest_rtt) {
		/*
		 * We retransmitted and the ack came back in less
		 * than the smallest rtt we have observed in the
		 * windowed rtt. We most likey did an improper
		 * retransmit as outlined in 4.2 Step 3 point 2 in
		 * the rack-draft.
		 *
		 * Use the prior transmission to update all the
		 * information as long as there is only one prior
		 * transmission.
		 */
		if ((rsm->r_flags & BBR_OVERMAX) == 0) {
#ifdef BBR_INVARIANTS
			if (rsm->r_rtr_cnt == 1)
				panic("rsm:%p bbr:%p rsm has overmax and only 1 retranmit flags:%x?", rsm, bbr, rsm->r_flags);
#endif
			i = rsm->r_rtr_cnt - 2;
			if (TSTMP_GT(cts, rsm->r_tim_lastsent[i]))
				t = cts - rsm->r_tim_lastsent[i];
			else
				t = 1;
			bbr_update_bbr_info(bbr, rsm, t, cts, to->to_tsecr, uts, BBR_RTT_BY_EARLIER_RET,
					    rsm->r_tim_lastsent[i], ack_type, to);
			bbr_earlier_retran(tp, bbr, rsm, t, cts, ack_type);
		} else {
			/*
			 * Too many prior transmissions, just
			 * updated BBR delivered
			 */
not_sure:
			bbr_update_bbr_info(bbr, rsm, 0, cts, to->to_tsecr, uts,
					    BBR_RTT_BY_SOME_RETRAN, 0, ack_type, to);
		}
	} else {
		/*
		 * We retransmitted it and the retransmit did the
		 * job.
		 */
		if (rsm->r_flags & BBR_TLP)
			bbr->rc_tlp_rtx_out = 0;
		if ((rsm->r_flags & BBR_OVERMAX) == 0)
			bbr_update_bbr_info(bbr, rsm, t, cts, to->to_tsecr, uts,
					    BBR_RTT_BY_THIS_RETRAN, 0, ack_type, to);
		else
			bbr_update_bbr_info(bbr, rsm, 0, cts, to->to_tsecr, uts,
					    BBR_RTT_BY_SOME_RETRAN, 0, ack_type, to);
		return (1);
	}
	return (0);
}