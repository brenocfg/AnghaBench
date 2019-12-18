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
struct tcpcb {scalar_t__ t_state; int /*<<< orphan*/  t_flags; TYPE_1__* t_timers; } ;
struct TYPE_4__ {scalar_t__ rc_prr_sndcnt; int /*<<< orphan*/  rc_hpts_flags; int /*<<< orphan*/  rc_tmap; int /*<<< orphan*/  rc_resend; int /*<<< orphan*/  rc_timer_exp; } ;
struct tcp_rack {scalar_t__ r_state; int rc_rack_rtt; TYPE_2__ r_ctl; scalar_t__ use_rack_cheat; } ;
struct rack_sendmap {scalar_t__ r_end; scalar_t__ r_start; } ;
typedef  scalar_t__ int32_t ;
struct TYPE_3__ {int tt_flags; } ;

/* Variables and functions */
 scalar_t__ IN_RECOVERY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  PACE_TMR_RACK ; 
 int /*<<< orphan*/  RACK_TO_FRM_RACK ; 
 int /*<<< orphan*/  TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 scalar_t__ TSTMP_LT (int,int /*<<< orphan*/ ) ; 
 int TT_STOPPED ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ctf_fixed_maxseg (struct tcpcb*) ; 
 struct rack_sendmap* rack_check_recovery_mode (struct tcpcb*,int) ; 
 int /*<<< orphan*/  rack_log_to_event (struct tcp_rack*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  rack_log_to_prr (struct tcp_rack*,int) ; 
 int /*<<< orphan*/  rack_set_state (struct tcpcb*,struct tcp_rack*) ; 
 int /*<<< orphan*/  rack_tlp_does_nada ; 
 int /*<<< orphan*/  rack_to_tot ; 
 int /*<<< orphan*/  tcp_log_dump_tp_logbuf (struct tcpcb*,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
rack_timeout_rack(struct tcpcb *tp, struct tcp_rack *rack, uint32_t cts)
{
	/*
	 * This timer simply provides an internal trigger to send out data.
	 * The check_recovery_mode call will see if there are needed
	 * retransmissions, if so we will enter fast-recovery. The output
	 * call may or may not do the same thing depending on sysctl
	 * settings.
	 */
	struct rack_sendmap *rsm;
	int32_t recovery, ll;

	if (tp->t_timers->tt_flags & TT_STOPPED) {
		return (1);
	}
	if (TSTMP_LT(cts, rack->r_ctl.rc_timer_exp)) {
		/* Its not time yet */
		return (0);
	}
	recovery = IN_RECOVERY(tp->t_flags);
	counter_u64_add(rack_to_tot, 1);
	if (rack->r_state && (rack->r_state != tp->t_state))
		rack_set_state(tp, rack);
	rsm = rack_check_recovery_mode(tp, cts);
	if (rsm)
		ll = rsm->r_end - rsm->r_start;
	else
		ll = 0;
	rack_log_to_event(rack, RACK_TO_FRM_RACK, ll);
	if (rsm) {
		uint32_t rtt;

		rtt = rack->rc_rack_rtt;
		if (rtt == 0)
			rtt = 1;
		if ((recovery == 0) &&
		    (rack->r_ctl.rc_prr_sndcnt < ctf_fixed_maxseg(tp))) {
			/*
			 * The rack-timeout that enter's us into recovery
			 * will force out one MSS and set us up so that we
			 * can do one more send in 2*rtt (transitioning the
			 * rack timeout into a rack-tlp).
			 */
			rack->r_ctl.rc_prr_sndcnt = ctf_fixed_maxseg(tp);
			rack_log_to_prr(rack, 3);
		} else if ((rack->r_ctl.rc_prr_sndcnt < (rsm->r_end - rsm->r_start)) &&
			   rack->use_rack_cheat) {
			/*
			 * When a rack timer goes, if the rack cheat is
			 * on, arrange it so we can send a full segment.
			 */
			rack->r_ctl.rc_prr_sndcnt = ctf_fixed_maxseg(tp);
			rack_log_to_prr(rack, 4);
		}
	} else {
		/* This is a case that should happen rarely if ever */
		counter_u64_add(rack_tlp_does_nada, 1);
#ifdef TCP_BLACKBOX
		tcp_log_dump_tp_logbuf(tp, "nada counter trips", M_NOWAIT, true);
#endif
		rack->r_ctl.rc_resend = TAILQ_FIRST(&rack->r_ctl.rc_tmap);
	}
	rack->r_ctl.rc_hpts_flags &= ~PACE_TMR_RACK;
	return (0);
}