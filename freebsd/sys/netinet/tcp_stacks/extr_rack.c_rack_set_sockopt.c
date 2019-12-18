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
struct tcpcb {int t_delayed_ack; int t_flags; scalar_t__ t_fb_ptr; } ;
struct TYPE_2__ {int rc_prop_rate; int rc_prop_reduce; int rc_tlp_cwnd_reduce; int rc_early_recovery; int rc_prr_sendalot; int rc_min_to; int rc_early_recovery_segs; int rc_reorder_shift; int rc_reorder_fade; int rc_tlp_threshold; int rc_pkt_delay; int rc_rate_sample_method; } ;
struct tcp_rack {int do_detection; int rack_tlp_threshold_use; int rc_always_pace; int rc_pace_reduce; int rc_pace_max_segs; int use_rack_cheat; int r_enforce_min_pace; int rack_per_of_gp; int rc_allow_data_af_clo; TYPE_1__ r_ctl; } ;
struct sockopt {int sopt_name; } ;
struct socket {int dummy; } ;
struct inpcb {int inp_flags; } ;
typedef  int /*<<< orphan*/  optval ;
typedef  int int32_t ;

/* Variables and functions */
 int ECONNRESET ; 
 int EINVAL ; 
 int INP_DROPPED ; 
 int INP_TIMEWAIT ; 
 int /*<<< orphan*/  INP_WLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  INP_WUNLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  RACK_OPTS_INC (int /*<<< orphan*/ ) ; 
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
 int TF_ACKNOW ; 
 int TF_DELACK ; 
 int TLP_USE_ID ; 
 int TLP_USE_TWO_TWO ; 
 int USE_RTT_AVG ; 
 int USE_RTT_HIGH ; 
 int USE_RTT_LOW ; 
 struct tcpcb* intotcpcb (struct inpcb*) ; 
 int /*<<< orphan*/  rack_output (struct tcpcb*) ; 
 int /*<<< orphan*/  rack_set_pace_segments (struct tcpcb*,struct tcp_rack*) ; 
 int sooptcopyin (struct sockopt*,int*,int,int) ; 
 int tcp_default_ctloutput (struct socket*,struct sockopt*,struct inpcb*,struct tcpcb*) ; 
 int /*<<< orphan*/  tcp_log_socket_option (struct tcpcb*,int,int,int) ; 
 int /*<<< orphan*/  tcp_rack_cheat ; 
 int /*<<< orphan*/  tcp_rack_early_recov ; 
 int /*<<< orphan*/  tcp_rack_early_seg ; 
 int /*<<< orphan*/  tcp_rack_max_seg ; 
 int /*<<< orphan*/  tcp_rack_min_pace ; 
 int /*<<< orphan*/  tcp_rack_min_to ; 
 int /*<<< orphan*/  tcp_rack_no_sack ; 
 int /*<<< orphan*/  tcp_rack_pace_always ; 
 int /*<<< orphan*/  tcp_rack_pace_reduce ; 
 int /*<<< orphan*/  tcp_rack_pkt_delay ; 
 int /*<<< orphan*/  tcp_rack_prop ; 
 int /*<<< orphan*/  tcp_rack_prop_rate ; 
 int /*<<< orphan*/  tcp_rack_prr_sendalot ; 
 int /*<<< orphan*/  tcp_rack_reord_fade ; 
 int /*<<< orphan*/  tcp_rack_reord_thresh ; 
 int /*<<< orphan*/  tcp_rack_tlp_reduce ; 
 int /*<<< orphan*/  tcp_rack_tlp_thresh ; 
 int /*<<< orphan*/  tcp_tlp_use ; 

__attribute__((used)) static int
rack_set_sockopt(struct socket *so, struct sockopt *sopt,
    struct inpcb *inp, struct tcpcb *tp, struct tcp_rack *rack)
{
	int32_t error = 0, optval;

	switch (sopt->sopt_name) {
	case TCP_RACK_PROP_RATE:
	case TCP_RACK_PROP:
	case TCP_RACK_TLP_REDUCE:
	case TCP_RACK_EARLY_RECOV:
	case TCP_RACK_PACE_ALWAYS:
	case TCP_DELACK:
	case TCP_RACK_PACE_REDUCE:
	case TCP_RACK_PACE_MAX_SEG:
	case TCP_RACK_PRR_SENDALOT:
	case TCP_RACK_MIN_TO:
	case TCP_RACK_EARLY_SEG:
	case TCP_RACK_REORD_THRESH:
	case TCP_RACK_REORD_FADE:
	case TCP_RACK_TLP_THRESH:
	case TCP_RACK_PKT_DELAY:
	case TCP_RACK_TLP_USE:
	case TCP_RACK_TLP_INC_VAR:
	case TCP_RACK_IDLE_REDUCE_HIGH:
	case TCP_RACK_MIN_PACE:
	case TCP_RACK_GP_INCREASE:
	case TCP_BBR_RACK_RTT_USE:
	case TCP_BBR_USE_RACK_CHEAT:
	case TCP_RACK_DO_DETECTION:
	case TCP_DATA_AFTER_CLOSE:
		break;
	default:
		return (tcp_default_ctloutput(so, sopt, inp, tp));
		break;
	}
	INP_WUNLOCK(inp);
	error = sooptcopyin(sopt, &optval, sizeof(optval), sizeof(optval));
	if (error)
		return (error);
	INP_WLOCK(inp);
	if (inp->inp_flags & (INP_TIMEWAIT | INP_DROPPED)) {
		INP_WUNLOCK(inp);
		return (ECONNRESET);
	}
	tp = intotcpcb(inp);
	rack = (struct tcp_rack *)tp->t_fb_ptr;
	switch (sopt->sopt_name) {
	case TCP_RACK_DO_DETECTION:
		RACK_OPTS_INC(tcp_rack_no_sack);
		if (optval == 0)
			rack->do_detection = 0;
		else
			rack->do_detection = 1;
		break;
	case TCP_RACK_PROP_RATE:
		if ((optval <= 0) || (optval >= 100)) {
			error = EINVAL;
			break;
		}
		RACK_OPTS_INC(tcp_rack_prop_rate);
		rack->r_ctl.rc_prop_rate = optval;
		break;
	case TCP_RACK_TLP_USE:
		if ((optval < TLP_USE_ID) || (optval > TLP_USE_TWO_TWO)) {
			error = EINVAL;
			break;
		}
		RACK_OPTS_INC(tcp_tlp_use);
		rack->rack_tlp_threshold_use = optval;
		break;
	case TCP_RACK_PROP:
		/* RACK proportional rate reduction (bool) */
		RACK_OPTS_INC(tcp_rack_prop);
		rack->r_ctl.rc_prop_reduce = optval;
		break;
	case TCP_RACK_TLP_REDUCE:
		/* RACK TLP cwnd reduction (bool) */
		RACK_OPTS_INC(tcp_rack_tlp_reduce);
		rack->r_ctl.rc_tlp_cwnd_reduce = optval;
		break;
	case TCP_RACK_EARLY_RECOV:
		/* Should recovery happen early (bool) */
		RACK_OPTS_INC(tcp_rack_early_recov);
		rack->r_ctl.rc_early_recovery = optval;
		break;
	case TCP_RACK_PACE_ALWAYS:
		/* Use the always pace method (bool)  */
		RACK_OPTS_INC(tcp_rack_pace_always);
		if (optval > 0)
			rack->rc_always_pace = 1;
		else
			rack->rc_always_pace = 0;
		break;
	case TCP_RACK_PACE_REDUCE:
		/* RACK Hptsi reduction factor (divisor) */
		RACK_OPTS_INC(tcp_rack_pace_reduce);
		if (optval)
			/* Must be non-zero */
			rack->rc_pace_reduce = optval;
		else
			error = EINVAL;
		break;
	case TCP_RACK_PACE_MAX_SEG:
		/* Max segments in a pace */
		RACK_OPTS_INC(tcp_rack_max_seg);
		rack->rc_pace_max_segs = optval;
		rack_set_pace_segments(tp, rack);
		break;
	case TCP_RACK_PRR_SENDALOT:
		/* Allow PRR to send more than one seg */
		RACK_OPTS_INC(tcp_rack_prr_sendalot);
		rack->r_ctl.rc_prr_sendalot = optval;
		break;
	case TCP_RACK_MIN_TO:
		/* Minimum time between rack t-o's in ms */
		RACK_OPTS_INC(tcp_rack_min_to);
		rack->r_ctl.rc_min_to = optval;
		break;
	case TCP_RACK_EARLY_SEG:
		/* If early recovery max segments */
		RACK_OPTS_INC(tcp_rack_early_seg);
		rack->r_ctl.rc_early_recovery_segs = optval;
		break;
	case TCP_RACK_REORD_THRESH:
		/* RACK reorder threshold (shift amount) */
		RACK_OPTS_INC(tcp_rack_reord_thresh);
		if ((optval > 0) && (optval < 31))
			rack->r_ctl.rc_reorder_shift = optval;
		else
			error = EINVAL;
		break;
	case TCP_RACK_REORD_FADE:
		/* Does reordering fade after ms time */
		RACK_OPTS_INC(tcp_rack_reord_fade);
		rack->r_ctl.rc_reorder_fade = optval;
		break;
	case TCP_RACK_TLP_THRESH:
		/* RACK TLP theshold i.e. srtt+(srtt/N) */
		RACK_OPTS_INC(tcp_rack_tlp_thresh);
		if (optval)
			rack->r_ctl.rc_tlp_threshold = optval;
		else
			error = EINVAL;
		break;
	case TCP_BBR_USE_RACK_CHEAT:
		RACK_OPTS_INC(tcp_rack_cheat);
		if (optval)
			rack->use_rack_cheat = 1;
		else
			rack->use_rack_cheat = 0;
		break;
	case TCP_RACK_PKT_DELAY:
		/* RACK added ms i.e. rack-rtt + reord + N */
		RACK_OPTS_INC(tcp_rack_pkt_delay);
		rack->r_ctl.rc_pkt_delay = optval;
		break;
	case TCP_RACK_TLP_INC_VAR:
		/* Does TLP include rtt variance in t-o */
		error = EINVAL;
		break;
	case TCP_RACK_IDLE_REDUCE_HIGH:
		error = EINVAL;
		break;
	case TCP_DELACK:
		if (optval == 0)
			tp->t_delayed_ack = 0;
		else
			tp->t_delayed_ack = 1;
		if (tp->t_flags & TF_DELACK) {
			tp->t_flags &= ~TF_DELACK;
			tp->t_flags |= TF_ACKNOW;
			rack_output(tp);
		}
		break;
	case TCP_RACK_MIN_PACE:
		RACK_OPTS_INC(tcp_rack_min_pace);
		if (optval > 3)
			rack->r_enforce_min_pace = 3;
		else
			rack->r_enforce_min_pace = optval;
		break;
	case TCP_RACK_GP_INCREASE:
		if ((optval >= 0) &&
		    (optval <= 256)) 
			rack->rack_per_of_gp = optval;
		else
			error = EINVAL;

		break;
	case TCP_BBR_RACK_RTT_USE:
		if ((optval != USE_RTT_HIGH) &&
		    (optval != USE_RTT_LOW) &&
		    (optval != USE_RTT_AVG))
			error = EINVAL;
		else
			rack->r_ctl.rc_rate_sample_method = optval;
		break;
	case TCP_DATA_AFTER_CLOSE:
		if (optval)
			rack->rc_allow_data_af_clo = 1;
		else
			rack->rc_allow_data_af_clo = 0;
		break;
	default:
		return (tcp_default_ctloutput(so, sopt, inp, tp));
		break;
	}
#ifdef NETFLIX_STATS
	tcp_log_socket_option(tp, sopt->sopt_name, optval, error);
#endif
	INP_WUNLOCK(inp);
	return (error);
}