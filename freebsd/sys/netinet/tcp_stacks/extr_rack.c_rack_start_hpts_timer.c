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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct tcpcb {scalar_t__ t_state; int t_flags; int /*<<< orphan*/  snd_una; int /*<<< orphan*/  snd_max; struct inpcb* t_inpcb; } ;
struct TYPE_5__ {int rc_timer_exp; int rc_hpts_flags; int rc_last_output_to; } ;
struct tcp_rack {int rc_tmr_stopped; TYPE_3__* rc_inp; TYPE_2__ r_ctl; scalar_t__ sack_attack_disable; scalar_t__ tlp_timer_up; } ;
struct inpcb {int /*<<< orphan*/  inp_flags2; TYPE_1__* inp_socket; scalar_t__ inp_in_hpts; } ;
typedef  int int32_t ;
struct TYPE_6__ {scalar_t__ inp_in_hpts; int /*<<< orphan*/  inp_flags2; } ;
struct TYPE_4__ {int so_options; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPTS_MS_TO_SLOTS (int) ; 
 int /*<<< orphan*/  INP_DONT_SACK_QUEUE ; 
 int /*<<< orphan*/  INP_MBUF_QUEUE_READY ; 
 int PACE_PKT_OUTPUT ; 
 int PACE_TMR_DELACK ; 
 int PACE_TMR_KEEP ; 
 int PACE_TMR_MASK ; 
 int PACE_TMR_RACK ; 
 scalar_t__ SEQ_GT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SO_KEEPALIVE ; 
 scalar_t__ TCPS_CLOSED ; 
 scalar_t__ TCPS_CLOSING ; 
 scalar_t__ TCPS_HAVEESTABLISHED (scalar_t__) ; 
 scalar_t__ TCPS_LISTEN ; 
 int TF_DELACK ; 
 int TICKS_2_MSEC (int /*<<< orphan*/ ) ; 
 int TP_KEEPIDLE (struct tcpcb*) ; 
 int TP_KEEPINIT (struct tcpcb*) ; 
 scalar_t__ TSTMP_GT (int,int) ; 
 int USEC_TO_MSEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,struct tcpcb*,struct tcp_rack*,int,int,int,int) ; 
 int /*<<< orphan*/  rack_log_to_start (struct tcp_rack*,int,int,int,int) ; 
 int /*<<< orphan*/  rack_log_type_bbrsnd (struct tcp_rack*,int,int,int) ; 
 int rack_timer_start (struct tcpcb*,struct tcp_rack*,int,int) ; 
 scalar_t__ tcp_always_keepalive ; 
 int /*<<< orphan*/  tcp_delacktime ; 
 int /*<<< orphan*/  tcp_hpts_insert (struct inpcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_sad_pacing_interval ; 

__attribute__((used)) static void
rack_start_hpts_timer(struct tcp_rack *rack, struct tcpcb *tp, uint32_t cts, 
      int32_t slot, uint32_t tot_len_this_send, int sup_rack)
{
	struct inpcb *inp;
	uint32_t delayed_ack = 0;
	uint32_t hpts_timeout;
	uint8_t stopped;
	uint32_t left = 0;

	inp = tp->t_inpcb;
	if (inp->inp_in_hpts) {
		/* A previous call is already set up */
		return;
	}
	if ((tp->t_state == TCPS_CLOSED) ||
	    (tp->t_state == TCPS_LISTEN)) {
		return;
	}
	stopped = rack->rc_tmr_stopped;
	if (stopped && TSTMP_GT(rack->r_ctl.rc_timer_exp, cts)) {
		left = rack->r_ctl.rc_timer_exp - cts;
	}
	rack->tlp_timer_up = 0;
	rack->r_ctl.rc_timer_exp = 0;
	if (rack->rc_inp->inp_in_hpts == 0) {
		rack->r_ctl.rc_hpts_flags = 0;
	} 
	if (slot) {
		/* We are hptsi too */
		rack->r_ctl.rc_hpts_flags |= PACE_PKT_OUTPUT;
	} else if (rack->r_ctl.rc_hpts_flags & PACE_PKT_OUTPUT) {
		/* 
		 * We are still left on the hpts when the to goes
		 * it will be for output.
		 */
		if (TSTMP_GT(rack->r_ctl.rc_last_output_to, cts))
			slot = rack->r_ctl.rc_last_output_to - cts;
		else
			slot = 1;
	}
	hpts_timeout = rack_timer_start(tp, rack, cts, sup_rack);
	if (rack->sack_attack_disable &&
	    (slot < USEC_TO_MSEC(tcp_sad_pacing_interval))) {
		/*
		 * We have a potential attacker on
		 * the line. We have possibly some
		 * (or now) pacing time set. We want to 
		 * slow down the processing of sacks by some
		 * amount (if it is an attacker). Set the default 
		 * slot for attackers in place (unless the orginal
		 * interval is longer). Its stored in
		 * micro-seconds, so lets convert to msecs.
		 */
		slot = USEC_TO_MSEC(tcp_sad_pacing_interval);
	}
	if (tp->t_flags & TF_DELACK) {
		delayed_ack = TICKS_2_MSEC(tcp_delacktime);
		rack->r_ctl.rc_hpts_flags |= PACE_TMR_DELACK;
	}
	if (delayed_ack && ((hpts_timeout == 0) ||
			    (delayed_ack < hpts_timeout)))
		hpts_timeout = delayed_ack;
	else 
		rack->r_ctl.rc_hpts_flags &= ~PACE_TMR_DELACK;
	/*
	 * If no timers are going to run and we will fall off the hptsi
	 * wheel, we resort to a keep-alive timer if its configured.
	 */
	if ((hpts_timeout == 0) &&
	    (slot == 0)) {
		if ((tcp_always_keepalive || inp->inp_socket->so_options & SO_KEEPALIVE) &&
		    (tp->t_state <= TCPS_CLOSING)) {
			/*
			 * Ok we have no timer (persists, rack, tlp, rxt  or
			 * del-ack), we don't have segments being paced. So
			 * all that is left is the keepalive timer.
			 */
			if (TCPS_HAVEESTABLISHED(tp->t_state)) {
				/* Get the established keep-alive time */
				hpts_timeout = TP_KEEPIDLE(tp);
			} else {
				/* Get the initial setup keep-alive time */
				hpts_timeout = TP_KEEPINIT(tp);
			}
			rack->r_ctl.rc_hpts_flags |= PACE_TMR_KEEP;
		}
	}
	if (left && (stopped & (PACE_TMR_KEEP | PACE_TMR_DELACK)) ==
	    (rack->r_ctl.rc_hpts_flags & PACE_TMR_MASK)) {
		/*
		 * RACK, TLP, persists and RXT timers all are restartable
		 * based on actions input .. i.e we received a packet (ack
		 * or sack) and that changes things (rw, or snd_una etc).
		 * Thus we can restart them with a new value. For
		 * keep-alive, delayed_ack we keep track of what was left
		 * and restart the timer with a smaller value.
		 */
		if (left < hpts_timeout)
			hpts_timeout = left;
	}
	if (hpts_timeout) {
		/*
		 * Hack alert for now we can't time-out over 2,147,483
		 * seconds (a bit more than 596 hours), which is probably ok
		 * :).
		 */
		if (hpts_timeout > 0x7ffffffe)
			hpts_timeout = 0x7ffffffe;
		rack->r_ctl.rc_timer_exp = cts + hpts_timeout;
	}
	if (slot) {
		rack->rc_inp->inp_flags2 |= INP_MBUF_QUEUE_READY;
		if (rack->r_ctl.rc_hpts_flags & PACE_TMR_RACK) 
			inp->inp_flags2 |= INP_DONT_SACK_QUEUE;
		else 
			inp->inp_flags2 &= ~INP_DONT_SACK_QUEUE;
		rack->r_ctl.rc_last_output_to = cts + slot;
		if ((hpts_timeout == 0) || (hpts_timeout > slot)) {
			if (rack->rc_inp->inp_in_hpts == 0)
				tcp_hpts_insert(tp->t_inpcb, HPTS_MS_TO_SLOTS(slot));
			rack_log_to_start(rack, cts, hpts_timeout, slot, 1);
		} else {
			/*
			 * Arrange for the hpts to kick back in after the
			 * t-o if the t-o does not cause a send.
			 */
			if (rack->rc_inp->inp_in_hpts == 0)
				tcp_hpts_insert(tp->t_inpcb, HPTS_MS_TO_SLOTS(hpts_timeout));
			rack_log_to_start(rack, cts, hpts_timeout, slot, 0);
		}
	} else if (hpts_timeout) {
		if (rack->r_ctl.rc_hpts_flags & PACE_TMR_RACK)  {
			/* For a rack timer, don't wake us */
			rack->rc_inp->inp_flags2 |= INP_MBUF_QUEUE_READY;
			inp->inp_flags2 |= INP_DONT_SACK_QUEUE;
		} else {
			/* All other timers wake us up */
			rack->rc_inp->inp_flags2 &= ~INP_MBUF_QUEUE_READY;
			inp->inp_flags2 &= ~INP_DONT_SACK_QUEUE;
		}
		if (rack->rc_inp->inp_in_hpts == 0)
			tcp_hpts_insert(tp->t_inpcb, HPTS_MS_TO_SLOTS(hpts_timeout));
		rack_log_to_start(rack, cts, hpts_timeout, slot, 0);
	} else {
		/* No timer starting */
#ifdef INVARIANTS
		if (SEQ_GT(tp->snd_max, tp->snd_una)) {
			panic("tp:%p rack:%p tlts:%d cts:%u slot:%u pto:%u -- no timer started?",
			    tp, rack, tot_len_this_send, cts, slot, hpts_timeout);
		}
#endif
	}
	rack->rc_tmr_stopped = 0;
	if (slot)
		rack_log_type_bbrsnd(rack, tot_len_this_send, slot, cts);
}