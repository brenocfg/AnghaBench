#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct tcpcb {scalar_t__ t_state; int t_flags; int snd_una; int snd_max; scalar_t__ t_rxtcur; int t_srtt; TYPE_2__* t_inpcb; } ;
struct TYPE_6__ {scalar_t__ rc_tlp_rxt_last_time; scalar_t__ rc_min_to; scalar_t__ rc_prr_sndcnt; scalar_t__ rc_tlp_rtx_out; scalar_t__ rc_last_tlp_seq; scalar_t__ rc_tlp_seg_send_cnt; scalar_t__ rc_tlp_send_cnt; int /*<<< orphan*/  rc_hpts_flags; int /*<<< orphan*/  rc_tmap; } ;
struct tcp_rack {scalar_t__ use_rack_cheat; scalar_t__ rc_tlp_in_progress; TYPE_3__ r_ctl; scalar_t__ sack_attack_disable; scalar_t__ rc_in_persist; scalar_t__ t_timers_stopped; } ;
struct rack_sendmap {int r_rtr_cnt; scalar_t__* r_tim_lastsent; int r_flags; scalar_t__ r_start; } ;
typedef  size_t int32_t ;
struct TYPE_5__ {TYPE_1__* inp_socket; } ;
struct TYPE_4__ {int /*<<< orphan*/  so_snd; } ;

/* Variables and functions */
 scalar_t__ IN_RECOVERY (int) ; 
 int /*<<< orphan*/  PACE_TMR_RACK ; 
 int /*<<< orphan*/  PACE_TMR_RXT ; 
 int /*<<< orphan*/  PACE_TMR_TLP ; 
 int RACK_ACKED ; 
 int RACK_HAS_FIN ; 
 scalar_t__ RACK_INITIAL_RTO ; 
 int RACK_SACK_PASSED ; 
 scalar_t__ SEQ_GEQ (scalar_t__,scalar_t__) ; 
 scalar_t__ SEQ_LT (int,int) ; 
 struct rack_sendmap* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct rack_sendmap* TAILQ_LAST_FAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TCPS_ESTABLISHED ; 
 scalar_t__ TCPTV_REXMTMAX ; 
 scalar_t__ TCP_RTT_SHIFT ; 
 int TF_SACK_PERMIT ; 
 int TF_SENTFIN ; 
 scalar_t__ TICKS_2_MSEC (scalar_t__) ; 
 scalar_t__ TSTMP_GEQ (scalar_t__,scalar_t__) ; 
 scalar_t__ TSTMP_GT (scalar_t__,scalar_t__) ; 
 scalar_t__ ctf_fixed_maxseg (struct tcpcb*) ; 
 int /*<<< orphan*/  r_tnext ; 
 scalar_t__ rack_calc_thresh_rack (struct tcp_rack*,scalar_t__,scalar_t__) ; 
 scalar_t__ rack_calc_thresh_tlp (struct tcpcb*,struct tcp_rack*,struct rack_sendmap*,scalar_t__) ; 
 struct rack_sendmap* rack_find_lowest_rsm (struct tcp_rack*) ; 
 scalar_t__ rack_get_persists_timer_val (struct tcpcb*,struct tcp_rack*) ; 
 scalar_t__ rack_grab_rtt (struct tcpcb*,struct tcp_rack*) ; 
 int /*<<< orphan*/  rack_sendmap ; 
 scalar_t__ rack_tlp_max_resend ; 
 scalar_t__ sbavail (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint32_t
rack_timer_start(struct tcpcb *tp, struct tcp_rack *rack, uint32_t cts, int sup_rack)
{
	/*
	 * Start the FR timer, we do this based on getting the first one in
	 * the rc_tmap. Note that if its NULL we must stop the timer. in all
	 * events we need to stop the running timer (if its running) before
	 * starting the new one.
	 */
	uint32_t thresh, exp, to, srtt, time_since_sent, tstmp_touse;
	uint32_t srtt_cur;
	int32_t idx;
	int32_t is_tlp_timer = 0;
	struct rack_sendmap *rsm;
	
	if (rack->t_timers_stopped) {
		/* All timers have been stopped none are to run */
		return (0);
	}
	if (rack->rc_in_persist) {
		/* We can't start any timer in persists */
		return (rack_get_persists_timer_val(tp, rack));
	}
	if ((tp->t_state < TCPS_ESTABLISHED) ||
	    ((tp->t_flags & TF_SACK_PERMIT) == 0))
		goto activate_rxt;
	rsm = TAILQ_FIRST(&rack->r_ctl.rc_tmap);
	if ((rsm == NULL) || sup_rack) {
		/* Nothing on the send map */
activate_rxt:
		time_since_sent = 0;
		rsm = TAILQ_FIRST(&rack->r_ctl.rc_tmap);
		if (rsm) {
			idx = rsm->r_rtr_cnt - 1;
			if (TSTMP_GEQ(rsm->r_tim_lastsent[idx], rack->r_ctl.rc_tlp_rxt_last_time)) 
				tstmp_touse = rsm->r_tim_lastsent[idx];
			else 
				tstmp_touse = rack->r_ctl.rc_tlp_rxt_last_time;
			if (TSTMP_GT(tstmp_touse, cts))
			    time_since_sent = cts - tstmp_touse;
		}
		if (SEQ_LT(tp->snd_una, tp->snd_max) || sbavail(&(tp->t_inpcb->inp_socket->so_snd))) {
			rack->r_ctl.rc_hpts_flags |= PACE_TMR_RXT;
			to = TICKS_2_MSEC(tp->t_rxtcur);
			if (to > time_since_sent)
				to -= time_since_sent;
			else
				to = rack->r_ctl.rc_min_to;
			if (to == 0)
				to = 1;
			return (to);
		}
		return (0);
	}
	if (rsm->r_flags & RACK_ACKED) {
		rsm = rack_find_lowest_rsm(rack);
		if (rsm == NULL) {
			/* No lowest? */
			goto activate_rxt;
		}
	}
	if (rack->sack_attack_disable) {
		/*
		 * We don't want to do
		 * any TLP's if you are an attacker.
		 * Though if you are doing what
		 * is expected you may still have
		 * SACK-PASSED marks.
		 */
		goto activate_rxt;
	}
	/* Convert from ms to usecs */
	if (rsm->r_flags & RACK_SACK_PASSED) {
		if ((tp->t_flags & TF_SENTFIN) &&
		    ((tp->snd_max - tp->snd_una) == 1) &&
		    (rsm->r_flags & RACK_HAS_FIN)) {
			/*
			 * We don't start a rack timer if all we have is a
			 * FIN outstanding.
			 */
			goto activate_rxt;
		}
		if ((rack->use_rack_cheat == 0) &&
		    (IN_RECOVERY(tp->t_flags)) &&
		     (rack->r_ctl.rc_prr_sndcnt  < ctf_fixed_maxseg(tp))) {
			/* 
			 * We are not cheating, in recovery  and
			 * not enough ack's to yet get our next
			 * retransmission out.
			 *
			 * Note that classified attackers do not
			 * get to use the rack-cheat.
			 */
			goto activate_tlp;
		}
		srtt = rack_grab_rtt(tp, rack);
		thresh = rack_calc_thresh_rack(rack, srtt, cts);
		idx = rsm->r_rtr_cnt - 1;
		exp = rsm->r_tim_lastsent[idx] + thresh;
		if (SEQ_GEQ(exp, cts)) {
			to = exp - cts;
			if (to < rack->r_ctl.rc_min_to) {
				to = rack->r_ctl.rc_min_to;
			}
		} else {
			to = rack->r_ctl.rc_min_to;
		}
	} else {
		/* Ok we need to do a TLP not RACK */
activate_tlp:
		if ((rack->rc_tlp_in_progress != 0) ||
		    (rack->r_ctl.rc_tlp_rtx_out != 0)) {
			/*
			 * The previous send was a TLP or a tlp_rtx is in
			 * process.
			 */
			goto activate_rxt;
		}
		rsm = TAILQ_LAST_FAST(&rack->r_ctl.rc_tmap, rack_sendmap, r_tnext);
		if (rsm == NULL) {
			/* We found no rsm to TLP with. */
			goto activate_rxt;
		}
		if (rsm->r_flags & RACK_HAS_FIN) {
			/* If its a FIN we dont do TLP */
			rsm = NULL;
			goto activate_rxt;
		}
		idx = rsm->r_rtr_cnt - 1;
		time_since_sent = 0;
		if (TSTMP_GEQ(rsm->r_tim_lastsent[idx], rack->r_ctl.rc_tlp_rxt_last_time)) 
			tstmp_touse = rsm->r_tim_lastsent[idx];
		else 
			tstmp_touse = rack->r_ctl.rc_tlp_rxt_last_time;
		if (TSTMP_GT(tstmp_touse, cts))
		    time_since_sent = cts - tstmp_touse;
		is_tlp_timer = 1;
		if (tp->t_srtt) {
			srtt_cur = (tp->t_srtt >> TCP_RTT_SHIFT);
			srtt = TICKS_2_MSEC(srtt_cur);
		} else
			srtt = RACK_INITIAL_RTO;
		thresh = rack_calc_thresh_tlp(tp, rack, rsm, srtt);
		if (thresh > time_since_sent)
			to = thresh - time_since_sent;
		else
			to = rack->r_ctl.rc_min_to;
		if (to > TCPTV_REXMTMAX) {
			/*
			 * If the TLP time works out to larger than the max
			 * RTO lets not do TLP.. just RTO.
			 */
			goto activate_rxt;
		}
		if (rsm->r_start != rack->r_ctl.rc_last_tlp_seq) {
			/*
			 * The tail is no longer the last one I did a probe
			 * on
			 */
			rack->r_ctl.rc_tlp_seg_send_cnt = 0;
			rack->r_ctl.rc_last_tlp_seq = rsm->r_start;
		}
	}
	if (is_tlp_timer == 0) {
		rack->r_ctl.rc_hpts_flags |= PACE_TMR_RACK;
	} else {
		if ((rack->r_ctl.rc_tlp_send_cnt > rack_tlp_max_resend) ||
		    (rack->r_ctl.rc_tlp_seg_send_cnt > rack_tlp_max_resend)) {
			/*
			 * We have exceeded how many times we can retran the
			 * current TLP timer, switch to the RTO timer.
			 */
			goto activate_rxt;
		} else {
			rack->r_ctl.rc_hpts_flags |= PACE_TMR_TLP;
		}
	}
	if (to == 0)
		to = 1;
	return (to);
}