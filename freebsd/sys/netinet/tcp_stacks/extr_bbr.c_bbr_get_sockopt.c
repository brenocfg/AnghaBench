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
struct tcpcb {int t_delayed_ack; } ;
struct TYPE_3__ {int cur_time_limit; } ;
struct TYPE_4__ {int bbr_hptsi_per_second; int bbr_hptsi_segments_delay_tar; int bbr_hptsi_segments_max; int bbr_hptsi_bytes_min; int bbr_cross_over; int rc_startup_pg; int rc_drain_pg; int rc_probertt_int; int bbr_rttprobe_gain_val; int rc_min_rto_ms; int rc_pace_max_segs; int rc_min_to; int rc_reorder_shift; int rc_reorder_fade; int bbr_hptsi_segments_floor; int bbr_utter_max; int rc_pkt_delay; int rc_incr_tmrs; int /*<<< orphan*/  rc_inc_enet_oh; int /*<<< orphan*/  rc_inc_ip_oh; int /*<<< orphan*/  rc_inc_tcp_oh; TYPE_1__ rc_rttprop; } ;
struct tcp_bbr {int no_pacing_until; int rc_use_google; int rc_use_ts_limit; int rc_init_win; int rc_loss_exit; int rc_max_rto_sec; int bbr_use_rack_cheat; int bbr_init_win_cheat; int rc_use_idle_restart; int rc_tlp_threshold; int rc_resends_use_tso; int rc_allow_data_af_clo; int bbr_hdw_pace_ena; int r_use_policer; int ts_can_raise; TYPE_2__ r_ctl; } ;
struct sockopt {int sopt_name; } ;
struct socket {int dummy; } ;
struct inpcb {int dummy; } ;
typedef  int int32_t ;

/* Variables and functions */
 int BBR_INCL_ENET_OH ; 
 int BBR_INCL_IP_OH ; 
 int BBR_INCL_TCP_OH ; 
 int EINVAL ; 
 int /*<<< orphan*/  INP_WUNLOCK (struct inpcb*) ; 
#define  TCP_BBR_ALGORITHM 164 
#define  TCP_BBR_DRAIN_PG 163 
#define  TCP_BBR_EXTRA_STATE 162 
#define  TCP_BBR_FLOOR_MIN_TSO 161 
#define  TCP_BBR_HDWR_PACE 160 
#define  TCP_BBR_IWINTSO 159 
#define  TCP_BBR_MAX_RTO 158 
#define  TCP_BBR_MIN_RTO 157 
#define  TCP_BBR_MIN_TOPACEOUT 156 
#define  TCP_BBR_PACE_CROSS 155 
#define  TCP_BBR_PACE_DEL_TAR 154 
#define  TCP_BBR_PACE_OH 153 
#define  TCP_BBR_PACE_PER_SEC 152 
#define  TCP_BBR_PACE_SEG_MAX 151 
#define  TCP_BBR_PACE_SEG_MIN 150 
#define  TCP_BBR_POLICER_DETECT 149 
#define  TCP_BBR_PROBE_RTT_GAIN 148 
#define  TCP_BBR_PROBE_RTT_INT 147 
#define  TCP_BBR_PROBE_RTT_LEN 146 
#define  TCP_BBR_RETRAN_WTSO 145 
#define  TCP_BBR_SEND_IWND_IN_TSO 144 
#define  TCP_BBR_STARTUP_LOSS_EXIT 143 
#define  TCP_BBR_STARTUP_PG 142 
#define  TCP_BBR_TMR_PACE_OH 141 
#define  TCP_BBR_TSLIMITS 140 
#define  TCP_BBR_TSTMP_RAISES 139 
#define  TCP_BBR_USEDEL_RATE 138 
#define  TCP_BBR_USE_RACK_CHEAT 137 
#define  TCP_BBR_UTTER_MAX_TSO 136 
#define  TCP_DATA_AFTER_CLOSE 135 
#define  TCP_DELACK 134 
#define  TCP_RACK_MIN_TO 133 
#define  TCP_RACK_PACE_MAX_SEG 132 
#define  TCP_RACK_PKT_DELAY 131 
#define  TCP_RACK_REORD_FADE 130 
#define  TCP_RACK_REORD_THRESH 129 
#define  TCP_RACK_TLP_THRESH 128 
 int USECS_IN_SECOND ; 
 int sooptcopyout (struct sockopt*,int*,int) ; 
 int tcp_default_ctloutput (struct socket*,struct sockopt*,struct inpcb*,struct tcpcb*) ; 

__attribute__((used)) static int
bbr_get_sockopt(struct socket *so, struct sockopt *sopt,
    struct inpcb *inp, struct tcpcb *tp, struct tcp_bbr *bbr)
{
	int32_t error, optval;

	/*
	 * Because all our options are either boolean or an int, we can just
	 * pull everything into optval and then unlock and copy. If we ever
	 * add a option that is not a int, then this will have quite an
	 * impact to this routine.
	 */
	switch (sopt->sopt_name) {
	case TCP_BBR_PACE_PER_SEC:
		optval = bbr->r_ctl.bbr_hptsi_per_second;
		break;
	case TCP_BBR_PACE_DEL_TAR:
		optval = bbr->r_ctl.bbr_hptsi_segments_delay_tar;
		break;
	case TCP_BBR_PACE_SEG_MAX:
		optval = bbr->r_ctl.bbr_hptsi_segments_max;
		break;
	case TCP_BBR_MIN_TOPACEOUT:
		optval = bbr->no_pacing_until;
		break;
	case TCP_BBR_PACE_SEG_MIN:
		optval = bbr->r_ctl.bbr_hptsi_bytes_min;
		break;
	case TCP_BBR_PACE_CROSS:
		optval = bbr->r_ctl.bbr_cross_over;
		break;
	case TCP_BBR_ALGORITHM:
		optval = bbr->rc_use_google;
		break;
	case TCP_BBR_TSLIMITS:
		optval = bbr->rc_use_ts_limit;
		break;
	case TCP_BBR_IWINTSO:
		optval = bbr->rc_init_win;
		break;
	case TCP_BBR_STARTUP_PG:
		optval = bbr->r_ctl.rc_startup_pg;
		break;
	case TCP_BBR_DRAIN_PG:
		optval = bbr->r_ctl.rc_drain_pg;
		break;
	case TCP_BBR_PROBE_RTT_INT:
		optval = bbr->r_ctl.rc_probertt_int;
		break;
	case TCP_BBR_PROBE_RTT_LEN:
		optval = (bbr->r_ctl.rc_rttprop.cur_time_limit / USECS_IN_SECOND);
		break;
	case TCP_BBR_PROBE_RTT_GAIN:
		optval = bbr->r_ctl.bbr_rttprobe_gain_val;
		break;
	case TCP_BBR_STARTUP_LOSS_EXIT:
		optval = bbr->rc_loss_exit;
		break;
	case TCP_BBR_USEDEL_RATE:
		error = EINVAL;
		break;
	case TCP_BBR_MIN_RTO:
		optval = bbr->r_ctl.rc_min_rto_ms;
		break;
	case TCP_BBR_MAX_RTO:
		optval = bbr->rc_max_rto_sec;
		break;
	case TCP_RACK_PACE_MAX_SEG:
		/* Max segments in a pace */
		optval = bbr->r_ctl.rc_pace_max_segs;
		break;
	case TCP_RACK_MIN_TO:
		/* Minimum time between rack t-o's in ms */
		optval = bbr->r_ctl.rc_min_to;
		break;
	case TCP_RACK_REORD_THRESH:
		/* RACK reorder threshold (shift amount) */
		optval = bbr->r_ctl.rc_reorder_shift;
		break;
	case TCP_RACK_REORD_FADE:
		/* Does reordering fade after ms time */
		optval = bbr->r_ctl.rc_reorder_fade;
		break;
	case TCP_BBR_USE_RACK_CHEAT:
		/* Do we use the rack cheat for rxt */
		optval = bbr->bbr_use_rack_cheat;
		break;
	case TCP_BBR_FLOOR_MIN_TSO:
		optval = bbr->r_ctl.bbr_hptsi_segments_floor;
		break;
	case TCP_BBR_UTTER_MAX_TSO:
		optval = bbr->r_ctl.bbr_utter_max;
		break;
	case TCP_BBR_SEND_IWND_IN_TSO:
		/* Do we send TSO size segments initially */
		optval = bbr->bbr_init_win_cheat;
		break;
	case TCP_BBR_EXTRA_STATE:
		optval = bbr->rc_use_idle_restart;
		break;
	case TCP_RACK_TLP_THRESH:
		/* RACK TLP theshold i.e. srtt+(srtt/N) */
		optval = bbr->rc_tlp_threshold;
		break;
	case TCP_RACK_PKT_DELAY:
		/* RACK added ms i.e. rack-rtt + reord + N */
		optval = bbr->r_ctl.rc_pkt_delay;
		break;
	case TCP_BBR_RETRAN_WTSO:
		optval = bbr->rc_resends_use_tso;
		break;
	case TCP_DATA_AFTER_CLOSE:
		optval = bbr->rc_allow_data_af_clo;
		break;
	case TCP_DELACK:
		optval = tp->t_delayed_ack;
		break;
	case TCP_BBR_HDWR_PACE:
		optval = bbr->bbr_hdw_pace_ena;
		break;
	case TCP_BBR_POLICER_DETECT:
		optval = bbr->r_use_policer;
		break;
	case TCP_BBR_TSTMP_RAISES:
		optval = bbr->ts_can_raise;
		break;
	case TCP_BBR_TMR_PACE_OH:
		optval = bbr->r_ctl.rc_incr_tmrs;
		break;
	case TCP_BBR_PACE_OH:
		optval = 0;
		if (bbr->r_ctl.rc_inc_tcp_oh)
			optval |= BBR_INCL_TCP_OH;
		if (bbr->r_ctl.rc_inc_ip_oh)
			optval |= BBR_INCL_IP_OH;
		if (bbr->r_ctl.rc_inc_enet_oh)
			optval |= BBR_INCL_ENET_OH;
		break;
	default:
		return (tcp_default_ctloutput(so, sopt, inp, tp));
		break;
	}
	INP_WUNLOCK(inp);
	error = sooptcopyout(sopt, &optval, sizeof optval);
	return (error);
}