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
struct tcpcb {int t_delayed_ack; scalar_t__ snd_una; scalar_t__ snd_max; int /*<<< orphan*/ * t_fb_ptr; int /*<<< orphan*/  snd_wnd; TYPE_1__* t_inpcb; } ;
struct TYPE_4__ {int /*<<< orphan*/  rc_tmap; int /*<<< orphan*/  rc_mtree; int /*<<< orphan*/  rc_tlp_rxt_last_time; int /*<<< orphan*/  rc_last_ack; int /*<<< orphan*/  rc_last_time_decay; int /*<<< orphan*/  rc_min_to; int /*<<< orphan*/  rc_prr_sendalot; int /*<<< orphan*/  rc_rate_sample_method; int /*<<< orphan*/  rc_high_rwnd; int /*<<< orphan*/  rc_early_recovery; int /*<<< orphan*/  rc_tlp_cwnd_reduce; int /*<<< orphan*/  rc_prop_rate; int /*<<< orphan*/  rc_prop_reduce; int /*<<< orphan*/  rc_pkt_delay; int /*<<< orphan*/  rc_reorder_shift; int /*<<< orphan*/  rc_tlp_threshold; int /*<<< orphan*/  rc_reorder_fade; int /*<<< orphan*/  rc_free; } ;
struct tcp_rack {int use_rack_cheat; int do_detection; TYPE_2__ r_ctl; int /*<<< orphan*/  rack_per_of_gp; int /*<<< orphan*/  rack_tlp_threshold_use; int /*<<< orphan*/  rc_always_pace; int /*<<< orphan*/  r_enforce_min_pace; int /*<<< orphan*/  rc_pace_max_segs; int /*<<< orphan*/  rc_pace_reduce; int /*<<< orphan*/  rc_allow_data_af_clo; scalar_t__ r_cpu; TYPE_1__* rc_inp; struct tcpcb* rc_tp; } ;
struct rack_sendmap {int r_rtr_cnt; scalar_t__ r_start; scalar_t__ r_end; int r_in_tmap; scalar_t__ r_dupack; scalar_t__ r_rtr_bytes; int /*<<< orphan*/ * r_tim_lastsent; int /*<<< orphan*/  r_flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  inp_flags2; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INP_SUPPORTS_MBUFQ ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  RACK_OVERMAX ; 
 int /*<<< orphan*/  RB_INIT (int /*<<< orphan*/ *) ; 
 struct rack_sendmap* RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct rack_sendmap*) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct rack_sendmap*,int /*<<< orphan*/ ) ; 
 scalar_t__ V_tcp_delack_enabled ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  microuptime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,struct rack_sendmap*,struct tcp_rack*,struct rack_sendmap*) ; 
 int /*<<< orphan*/  r_tnext ; 
 struct rack_sendmap* rack_alloc (struct tcp_rack*) ; 
 int /*<<< orphan*/  rack_clear_rate_sample (struct tcp_rack*) ; 
 int /*<<< orphan*/  rack_early_recovery ; 
 int /*<<< orphan*/  rack_hptsi_segments ; 
 int /*<<< orphan*/  rack_ignore_data_after_close ; 
 int /*<<< orphan*/  rack_lower_cwnd_at_tlp ; 
 int /*<<< orphan*/  rack_min_pace_time ; 
 int /*<<< orphan*/  rack_min_to ; 
 int /*<<< orphan*/  rack_pace_every_seg ; 
 int /*<<< orphan*/  rack_pcb_zone ; 
 int /*<<< orphan*/  rack_per_of_gp ; 
 int /*<<< orphan*/  rack_pkt_delay ; 
 int /*<<< orphan*/  rack_proportional_rate ; 
 int /*<<< orphan*/  rack_rate_sample_method ; 
 int /*<<< orphan*/  rack_rb_tree_head ; 
 int /*<<< orphan*/  rack_reorder_fade ; 
 int /*<<< orphan*/  rack_reorder_thresh ; 
 int /*<<< orphan*/  rack_send_a_lot_in_prr ; 
 int /*<<< orphan*/  rack_set_pace_segments (struct tcpcb*,struct tcp_rack*) ; 
 int /*<<< orphan*/  rack_slot_reduction ; 
 int /*<<< orphan*/  rack_start_hpts_timer (struct tcp_rack*,struct tcpcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rack_stop_all_timers (struct tcpcb*) ; 
 int /*<<< orphan*/  rack_tlp_thresh ; 
 int /*<<< orphan*/  rack_tlp_threshold_use ; 
 int /*<<< orphan*/  rack_use_proportional_reduce ; 
 scalar_t__ tcp_force_detection ; 
 int /*<<< orphan*/  tcp_ts_getticks () ; 
 int /*<<< orphan*/ * uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ use_rack_cheat ; 

__attribute__((used)) static int
rack_init(struct tcpcb *tp)
{
	struct tcp_rack *rack = NULL;
	struct rack_sendmap *insret;

	tp->t_fb_ptr = uma_zalloc(rack_pcb_zone, M_NOWAIT);
	if (tp->t_fb_ptr == NULL) {
		/*
		 * We need to allocate memory but cant. The INP and INP_INFO
		 * locks and they are recusive (happens during setup. So a
		 * scheme to drop the locks fails :(
		 *
		 */
		return (ENOMEM);
	}
	memset(tp->t_fb_ptr, 0, sizeof(struct tcp_rack));

	rack = (struct tcp_rack *)tp->t_fb_ptr;
	RB_INIT(&rack->r_ctl.rc_mtree);
	TAILQ_INIT(&rack->r_ctl.rc_free);
	TAILQ_INIT(&rack->r_ctl.rc_tmap);
	rack->rc_tp = tp;
	if (tp->t_inpcb) {
		rack->rc_inp = tp->t_inpcb;
	}
	tp->t_inpcb->inp_flags2 |= INP_SUPPORTS_MBUFQ;
	/* Probably not needed but lets be sure */
	rack_clear_rate_sample(rack);
	rack->r_cpu = 0;
	rack->r_ctl.rc_reorder_fade = rack_reorder_fade;
	rack->rc_allow_data_af_clo = rack_ignore_data_after_close;
	rack->r_ctl.rc_tlp_threshold = rack_tlp_thresh;
	rack->rc_pace_reduce = rack_slot_reduction;
	if (use_rack_cheat)
		rack->use_rack_cheat = 1;
	if (V_tcp_delack_enabled)
		tp->t_delayed_ack = 1;
	else
		tp->t_delayed_ack = 0;
	rack->rc_pace_max_segs = rack_hptsi_segments;
	rack->r_ctl.rc_reorder_shift = rack_reorder_thresh;
	rack->r_ctl.rc_pkt_delay = rack_pkt_delay;
	rack->r_ctl.rc_prop_reduce = rack_use_proportional_reduce;
	rack->r_enforce_min_pace = rack_min_pace_time;
	rack->r_ctl.rc_prop_rate = rack_proportional_rate;
	rack->r_ctl.rc_tlp_cwnd_reduce = rack_lower_cwnd_at_tlp;
	rack->r_ctl.rc_early_recovery = rack_early_recovery;
	rack->rc_always_pace = rack_pace_every_seg;
	rack_set_pace_segments(tp, rack);
	rack->r_ctl.rc_high_rwnd = tp->snd_wnd;
	rack->r_ctl.rc_rate_sample_method = rack_rate_sample_method;
	rack->rack_tlp_threshold_use = rack_tlp_threshold_use;
	rack->r_ctl.rc_prr_sendalot = rack_send_a_lot_in_prr;
	rack->r_ctl.rc_min_to = rack_min_to;
	rack->rack_per_of_gp = rack_per_of_gp;
	microuptime(&rack->r_ctl.rc_last_ack);
	rack->r_ctl.rc_last_time_decay = rack->r_ctl.rc_last_ack;
	rack->r_ctl.rc_tlp_rxt_last_time = tcp_ts_getticks();
	/* Do we force on detection? */
	if (tcp_force_detection)
		rack->do_detection = 1;
	else
		rack->do_detection = 0;
	if (tp->snd_una != tp->snd_max) {
		/* Create a send map for the current outstanding data */
		struct rack_sendmap *rsm;

		rsm = rack_alloc(rack);
		if (rsm == NULL) {
			uma_zfree(rack_pcb_zone, tp->t_fb_ptr);
			tp->t_fb_ptr = NULL;
			return (ENOMEM);
		}
		rsm->r_flags = RACK_OVERMAX;
		rsm->r_tim_lastsent[0] = rack->r_ctl.rc_tlp_rxt_last_time;
		rsm->r_rtr_cnt = 1;
		rsm->r_rtr_bytes = 0;
		rsm->r_start = tp->snd_una;
		rsm->r_end = tp->snd_max;
		rsm->r_dupack = 0;
		insret = RB_INSERT(rack_rb_tree_head, &rack->r_ctl.rc_mtree, rsm);
#ifdef INVARIANTS
		if (insret != NULL) {
			panic("Insert in rb tree fails ret:%p rack:%p rsm:%p",
			      insret, rack, rsm);
		}
#endif
		TAILQ_INSERT_TAIL(&rack->r_ctl.rc_tmap, rsm, r_tnext);
		rsm->r_in_tmap = 1;
	}
	rack_stop_all_timers(tp);
	rack_start_hpts_timer(rack, tp, tcp_ts_getticks(), 0, 0, 0);
	return (0);
}