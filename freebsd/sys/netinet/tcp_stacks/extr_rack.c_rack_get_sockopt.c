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
struct tcpcb {scalar_t__ t_delayed_ack; } ;
struct TYPE_2__ {scalar_t__ rc_prop_rate; scalar_t__ rc_prop_reduce; scalar_t__ rc_tlp_cwnd_reduce; scalar_t__ rc_early_recovery; scalar_t__ rc_prr_sendalot; scalar_t__ rc_min_to; scalar_t__ rc_early_recovery_segs; scalar_t__ rc_reorder_shift; scalar_t__ rc_reorder_fade; scalar_t__ rc_tlp_threshold; scalar_t__ rc_pkt_delay; scalar_t__ rc_rate_sample_method; } ;
struct tcp_rack {scalar_t__ do_detection; scalar_t__ rc_pace_reduce; scalar_t__ rc_pace_max_segs; scalar_t__ rc_always_pace; scalar_t__ use_rack_cheat; scalar_t__ rack_tlp_threshold_use; scalar_t__ r_enforce_min_pace; scalar_t__ rack_per_of_gp; scalar_t__ rc_allow_data_af_clo; TYPE_1__ r_ctl; } ;
struct sockopt {int sopt_name; } ;
struct socket {int dummy; } ;
struct inpcb {int dummy; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  INP_WUNLOCK (struct inpcb*) ; 
#define  TCP_BBR_RACK_RTT_USE 151 
#define  TCP_BBR_USE_RACK_CHEAT 150 
#define  TCP_DATA_AFTER_CLOSE 149 
#define  TCP_DELACK 148 
#define  TCP_RACK_DO_DETECTION 147 
#define  TCP_RACK_EARLY_RECOV 146 
#define  TCP_RACK_EARLY_SEG 145 
#define  TCP_RACK_GP_INCREASE 144 
#define  TCP_RACK_IDLE_REDUCE_HIGH 143 
#define  TCP_RACK_MIN_PACE 142 
#define  TCP_RACK_MIN_TO 141 
#define  TCP_RACK_PACE_ALWAYS 140 
#define  TCP_RACK_PACE_MAX_SEG 139 
#define  TCP_RACK_PACE_REDUCE 138 
#define  TCP_RACK_PKT_DELAY 137 
#define  TCP_RACK_PROP 136 
#define  TCP_RACK_PROP_RATE 135 
#define  TCP_RACK_PRR_SENDALOT 134 
#define  TCP_RACK_REORD_FADE 133 
#define  TCP_RACK_REORD_THRESH 132 
#define  TCP_RACK_TLP_INC_VAR 131 
#define  TCP_RACK_TLP_REDUCE 130 
#define  TCP_RACK_TLP_THRESH 129 
#define  TCP_RACK_TLP_USE 128 
 scalar_t__ sooptcopyout (struct sockopt*,scalar_t__*,int) ; 
 int tcp_default_ctloutput (struct socket*,struct sockopt*,struct inpcb*,struct tcpcb*) ; 

__attribute__((used)) static int
rack_get_sockopt(struct socket *so, struct sockopt *sopt,
    struct inpcb *inp, struct tcpcb *tp, struct tcp_rack *rack)
{
	int32_t error, optval;

	/*
	 * Because all our options are either boolean or an int, we can just
	 * pull everything into optval and then unlock and copy. If we ever
	 * add a option that is not a int, then this will have quite an
	 * impact to this routine.
	 */
	error = 0;
	switch (sopt->sopt_name) {
	case TCP_RACK_DO_DETECTION:
		optval = rack->do_detection;
		break;

	case TCP_RACK_PROP_RATE:
		optval = rack->r_ctl.rc_prop_rate;
		break;
	case TCP_RACK_PROP:
		/* RACK proportional rate reduction (bool) */
		optval = rack->r_ctl.rc_prop_reduce;
		break;
	case TCP_RACK_TLP_REDUCE:
		/* RACK TLP cwnd reduction (bool) */
		optval = rack->r_ctl.rc_tlp_cwnd_reduce;
		break;
	case TCP_RACK_EARLY_RECOV:
		/* Should recovery happen early (bool) */
		optval = rack->r_ctl.rc_early_recovery;
		break;
	case TCP_RACK_PACE_REDUCE:
		/* RACK Hptsi reduction factor (divisor) */
		optval = rack->rc_pace_reduce;
		break;
	case TCP_RACK_PACE_MAX_SEG:
		/* Max segments in a pace */
		optval = rack->rc_pace_max_segs;
		break;
	case TCP_RACK_PACE_ALWAYS:
		/* Use the always pace method */
		optval = rack->rc_always_pace;
		break;
	case TCP_RACK_PRR_SENDALOT:
		/* Allow PRR to send more than one seg */
		optval = rack->r_ctl.rc_prr_sendalot;
		break;
	case TCP_RACK_MIN_TO:
		/* Minimum time between rack t-o's in ms */
		optval = rack->r_ctl.rc_min_to;
		break;
	case TCP_RACK_EARLY_SEG:
		/* If early recovery max segments */
		optval = rack->r_ctl.rc_early_recovery_segs;
		break;
	case TCP_RACK_REORD_THRESH:
		/* RACK reorder threshold (shift amount) */
		optval = rack->r_ctl.rc_reorder_shift;
		break;
	case TCP_RACK_REORD_FADE:
		/* Does reordering fade after ms time */
		optval = rack->r_ctl.rc_reorder_fade;
		break;
	case TCP_BBR_USE_RACK_CHEAT:
		/* Do we use the rack cheat for rxt */
		optval = rack->use_rack_cheat;
		break;
	case TCP_RACK_TLP_THRESH:
		/* RACK TLP theshold i.e. srtt+(srtt/N) */
		optval = rack->r_ctl.rc_tlp_threshold;
		break;
	case TCP_RACK_PKT_DELAY:
		/* RACK added ms i.e. rack-rtt + reord + N */
		optval = rack->r_ctl.rc_pkt_delay;
		break;
	case TCP_RACK_TLP_USE:
		optval = rack->rack_tlp_threshold_use;
		break;
	case TCP_RACK_TLP_INC_VAR:
		/* Does TLP include rtt variance in t-o */
		error = EINVAL;
		break;
	case TCP_RACK_IDLE_REDUCE_HIGH:
		error = EINVAL;
		break;
	case TCP_RACK_MIN_PACE:
		optval = rack->r_enforce_min_pace;
		break;
	case TCP_RACK_GP_INCREASE:
		optval = rack->rack_per_of_gp;
		break;
	case TCP_BBR_RACK_RTT_USE:
		optval = rack->r_ctl.rc_rate_sample_method;
		break;
	case TCP_DELACK:
		optval = tp->t_delayed_ack;
		break;
	case TCP_DATA_AFTER_CLOSE:
		optval = rack->rc_allow_data_af_clo;
		break;
	default:
		return (tcp_default_ctloutput(so, sopt, inp, tp));
		break;
	}
	INP_WUNLOCK(inp);
	if (error == 0) {
		error = sooptcopyout(sopt, &optval, sizeof optval);
	}
	return (error);
}