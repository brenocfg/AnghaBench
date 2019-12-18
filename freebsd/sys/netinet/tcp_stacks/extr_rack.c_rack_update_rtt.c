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
struct tcpopt {int to_flags; int to_tsecr; } ;
struct tcpcb {int t_rttlow; scalar_t__ t_softerror; scalar_t__ t_rxtshift; int /*<<< orphan*/  snd_ssthresh; int /*<<< orphan*/  snd_cwnd; int /*<<< orphan*/  snd_max; int /*<<< orphan*/  t_flags; } ;
struct TYPE_2__ {int rc_rack_min_rtt; int rc_rack_tmit_time; int /*<<< orphan*/  rc_prr_sndcnt; int /*<<< orphan*/  rc_ssthresh_at; int /*<<< orphan*/  rc_cwnd_at; int /*<<< orphan*/  rc_rsm_start; scalar_t__ rc_tlp_cwnd_reduce; } ;
struct tcp_rack {int rc_rack_rtt; TYPE_1__ r_ctl; } ;
struct rack_sendmap {int r_flags; int r_rtr_cnt; int* r_tim_lastsent; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CC_NDUPACK ; 
 scalar_t__ CUM_ACKED ; 
 int /*<<< orphan*/  IN_RECOVERY (int /*<<< orphan*/ ) ; 
 int RACK_ACKED ; 
 int RACK_OVERMAX ; 
 int RACK_TLP ; 
 scalar_t__ SEQ_LT (int,int) ; 
 int TOF_TS ; 
 int /*<<< orphan*/  ctf_fixed_maxseg (struct tcpcb*) ; 
 int /*<<< orphan*/  rack_cong_signal (struct tcpcb*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rack_earlier_retran (struct tcpcb*,struct rack_sendmap*,int,int) ; 
 int /*<<< orphan*/  rack_log_to_prr (struct tcp_rack*,int) ; 
 int /*<<< orphan*/  tcp_rack_xmit_timer (struct tcp_rack*,int) ; 

__attribute__((used)) static int
rack_update_rtt(struct tcpcb *tp, struct tcp_rack *rack,
    struct rack_sendmap *rsm, struct tcpopt *to, uint32_t cts, int32_t ack_type)
{
	int32_t i;
	uint32_t t;

	if (rsm->r_flags & RACK_ACKED)
		/* Already done */
		return (0);


	if ((rsm->r_rtr_cnt == 1) ||
	    ((ack_type == CUM_ACKED) &&
	    (to->to_flags & TOF_TS) &&
	    (to->to_tsecr) &&
	    (rsm->r_tim_lastsent[rsm->r_rtr_cnt - 1] == to->to_tsecr))
	    ) {
		/*
		 * We will only find a matching timestamp if its cum-acked.
		 * But if its only one retransmission its for-sure matching
		 * :-)
		 */
		t = cts - rsm->r_tim_lastsent[(rsm->r_rtr_cnt - 1)];
		if ((int)t <= 0)
			t = 1;
		if (!tp->t_rttlow || tp->t_rttlow > t)
			tp->t_rttlow = t;
		if (!rack->r_ctl.rc_rack_min_rtt ||
		    SEQ_LT(t, rack->r_ctl.rc_rack_min_rtt)) {
			rack->r_ctl.rc_rack_min_rtt = t;
			if (rack->r_ctl.rc_rack_min_rtt == 0) {
				rack->r_ctl.rc_rack_min_rtt = 1;
			}
		}
		tcp_rack_xmit_timer(rack, t + 1);
		if ((rsm->r_flags & RACK_TLP) &&
		    (!IN_RECOVERY(tp->t_flags))) {
			/* Segment was a TLP and our retrans matched */
			if (rack->r_ctl.rc_tlp_cwnd_reduce) {
				rack->r_ctl.rc_rsm_start = tp->snd_max;
				rack->r_ctl.rc_cwnd_at = tp->snd_cwnd;
				rack->r_ctl.rc_ssthresh_at = tp->snd_ssthresh;
				rack_cong_signal(tp, NULL, CC_NDUPACK);
				/*
				 * When we enter recovery we need to assure
				 * we send one packet.
				 */
				rack->r_ctl.rc_prr_sndcnt = ctf_fixed_maxseg(tp);
				rack_log_to_prr(rack, 7);
			} 
		}
		if (SEQ_LT(rack->r_ctl.rc_rack_tmit_time, rsm->r_tim_lastsent[(rsm->r_rtr_cnt - 1)])) {
			/* New more recent rack_tmit_time */
			rack->r_ctl.rc_rack_tmit_time = rsm->r_tim_lastsent[(rsm->r_rtr_cnt - 1)];
			rack->rc_rack_rtt = t;
		}
		return (1);
	}
	/* 
	 * We clear the soft/rxtshift since we got an ack. 
	 * There is no assurance we will call the commit() function
	 * so we need to clear these to avoid incorrect handling.
	 */
	tp->t_rxtshift = 0;
	tp->t_softerror = 0;
	if ((to->to_flags & TOF_TS) &&
	    (ack_type == CUM_ACKED) &&
	    (to->to_tsecr) &&
	    ((rsm->r_flags & RACK_OVERMAX) == 0)) {
		/*
		 * Now which timestamp does it match? In this block the ACK
		 * must be coming from a previous transmission.
		 */
		for (i = 0; i < rsm->r_rtr_cnt; i++) {
			if (rsm->r_tim_lastsent[i] == to->to_tsecr) {
				t = cts - rsm->r_tim_lastsent[i];
				if ((int)t <= 0)
					t = 1;
				if ((i + 1) < rsm->r_rtr_cnt) {
					/* Likely */
					rack_earlier_retran(tp, rsm, t, cts);
				}
				if (!tp->t_rttlow || tp->t_rttlow > t)
					tp->t_rttlow = t;
				if (!rack->r_ctl.rc_rack_min_rtt || SEQ_LT(t, rack->r_ctl.rc_rack_min_rtt)) {
					rack->r_ctl.rc_rack_min_rtt = t;
					if (rack->r_ctl.rc_rack_min_rtt == 0) {
						rack->r_ctl.rc_rack_min_rtt = 1;
					}
				}
                                /*
				 * Note the following calls to
				 * tcp_rack_xmit_timer() are being commented
				 * out for now. They give us no more accuracy
				 * and often lead to a wrong choice. We have
				 * enough samples that have not been 
				 * retransmitted. I leave the commented out
				 * code in here in case in the future we
				 * decide to add it back (though I can't forsee
				 * doing that). That way we will easily see
				 * where they need to be placed.
				 */
				if (SEQ_LT(rack->r_ctl.rc_rack_tmit_time,
				    rsm->r_tim_lastsent[(rsm->r_rtr_cnt - 1)])) {
					/* New more recent rack_tmit_time */
					rack->r_ctl.rc_rack_tmit_time = rsm->r_tim_lastsent[(rsm->r_rtr_cnt - 1)];
					rack->rc_rack_rtt = t;
				}
				return (1);
			}
		}
		goto ts_not_found;
	} else {
		/*
		 * Ok its a SACK block that we retransmitted. or a windows
		 * machine without timestamps. We can tell nothing from the
		 * time-stamp since its not there or the time the peer last
		 * recieved a segment that moved forward its cum-ack point.
		 */
ts_not_found:
		i = rsm->r_rtr_cnt - 1;
		t = cts - rsm->r_tim_lastsent[i];
		if ((int)t <= 0)
			t = 1;
		if (rack->r_ctl.rc_rack_min_rtt && SEQ_LT(t, rack->r_ctl.rc_rack_min_rtt)) {
			/*
			 * We retransmitted and the ack came back in less
			 * than the smallest rtt we have observed. We most
			 * likey did an improper retransmit as outlined in
			 * 4.2 Step 3 point 2 in the rack-draft.
			 */
			i = rsm->r_rtr_cnt - 2;
			t = cts - rsm->r_tim_lastsent[i];
			rack_earlier_retran(tp, rsm, t, cts);
		} else if (rack->r_ctl.rc_rack_min_rtt) {
			/*
			 * We retransmitted it and the retransmit did the
			 * job.
			 */
			if (!rack->r_ctl.rc_rack_min_rtt ||
			    SEQ_LT(t, rack->r_ctl.rc_rack_min_rtt)) {
				rack->r_ctl.rc_rack_min_rtt = t;
				if (rack->r_ctl.rc_rack_min_rtt == 0) {
					rack->r_ctl.rc_rack_min_rtt = 1;
				}
			}
			if (SEQ_LT(rack->r_ctl.rc_rack_tmit_time, rsm->r_tim_lastsent[i])) {
				/* New more recent rack_tmit_time */
				rack->r_ctl.rc_rack_tmit_time = rsm->r_tim_lastsent[i];
				rack->rc_rack_rtt = t;
			}
			return (1);
		}
	}
	return (0);
}