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
struct TYPE_4__ {int /*<<< orphan*/  rc_num_small_maps_alloced; int /*<<< orphan*/  rc_pace_max_segs; } ;
struct tcp_bbr {TYPE_2__ r_ctl; scalar_t__ rc_last_options; TYPE_1__* rc_tp; } ;
struct bbr_sendmap {int r_start; int r_end; int r_rtr_cnt; int r_is_smallmap; int /*<<< orphan*/ * r_tim_lastsent; int /*<<< orphan*/  r_bbr_state; int /*<<< orphan*/  r_flight_at_send; int /*<<< orphan*/  r_first_sent_time; int /*<<< orphan*/  r_app_limited; int /*<<< orphan*/  r_del_time; int /*<<< orphan*/  r_del_ack_ts; int /*<<< orphan*/  r_ts_valid; int /*<<< orphan*/  r_delivered; int /*<<< orphan*/  r_is_drain; int /*<<< orphan*/  r_is_gain; scalar_t__ r_rtr_bytes; int /*<<< orphan*/  r_dupack; int /*<<< orphan*/  r_flags; } ;
struct TYPE_3__ {scalar_t__ t_maxseg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBR_HAS_FIN ; 
 int /*<<< orphan*/  BBR_HAS_SYN ; 
 int min (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
bbr_clone_rsm(struct tcp_bbr *bbr, struct bbr_sendmap *nrsm, struct bbr_sendmap *rsm, uint32_t start)
{
	int idx;

	nrsm->r_start = start;
	nrsm->r_end = rsm->r_end;
	nrsm->r_rtr_cnt = rsm->r_rtr_cnt;
	nrsm->r_flags = rsm->r_flags;
	/* We don't transfer forward the SYN flag */
	nrsm->r_flags &= ~BBR_HAS_SYN;
	/* We move forward the FIN flag, not that this should happen */
	rsm->r_flags &= ~BBR_HAS_FIN;
	nrsm->r_dupack = rsm->r_dupack;
	nrsm->r_rtr_bytes = 0;
	nrsm->r_is_gain = rsm->r_is_gain;
	nrsm->r_is_drain = rsm->r_is_drain;
	nrsm->r_delivered = rsm->r_delivered;
	nrsm->r_ts_valid = rsm->r_ts_valid;
	nrsm->r_del_ack_ts = rsm->r_del_ack_ts;
	nrsm->r_del_time = rsm->r_del_time;
	nrsm->r_app_limited = rsm->r_app_limited;
	nrsm->r_first_sent_time = rsm->r_first_sent_time;
	nrsm->r_flight_at_send = rsm->r_flight_at_send;
	/* We split a piece the lower section looses any just_ret flag. */
	nrsm->r_bbr_state = rsm->r_bbr_state;
	for (idx = 0; idx < nrsm->r_rtr_cnt; idx++) {
		nrsm->r_tim_lastsent[idx] = rsm->r_tim_lastsent[idx];
	}
	rsm->r_end = nrsm->r_start;
	idx = min((bbr->rc_tp->t_maxseg - bbr->rc_last_options), bbr->r_ctl.rc_pace_max_segs);
	idx /= 8;
	/* Check if we got too small */
	if ((rsm->r_is_smallmap == 0) &&
	    ((rsm->r_end - rsm->r_start) <= idx)) {
		bbr->r_ctl.rc_num_small_maps_alloced++;
		rsm->r_is_smallmap = 1;
	}
	/* Check the new one as well */
	if ((nrsm->r_end - nrsm->r_start) <= idx) {
		bbr->r_ctl.rc_num_small_maps_alloced++;
		nrsm->r_is_smallmap = 1;
	}
}