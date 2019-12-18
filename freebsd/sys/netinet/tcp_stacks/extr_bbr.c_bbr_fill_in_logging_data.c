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
typedef  union tcp_log_stackspecific {int dummy; } tcp_log_stackspecific ;
typedef  int /*<<< orphan*/  uint32_t ;
struct tcp_log_bbr {int /*<<< orphan*/  pkt_epoch; int /*<<< orphan*/  pkts_out; int /*<<< orphan*/  use_lt_bw; int /*<<< orphan*/  ininput; int /*<<< orphan*/  inhpts; int /*<<< orphan*/  cwnd_gain; int /*<<< orphan*/  pacing_gain; int /*<<< orphan*/  lt_epoch; int /*<<< orphan*/  epoch; int /*<<< orphan*/  bbr_substate; int /*<<< orphan*/  bbr_state; int /*<<< orphan*/  lost; int /*<<< orphan*/  timeStamp; int /*<<< orphan*/  delivered; int /*<<< orphan*/  applimited; int /*<<< orphan*/  inflight; int /*<<< orphan*/  bw_inuse; int /*<<< orphan*/  rttProp; int /*<<< orphan*/  delRate; int /*<<< orphan*/  cur_del_rate; } ;
struct TYPE_4__ {int /*<<< orphan*/  rc_pkt_epoch; int /*<<< orphan*/  rc_flight_at_input; int /*<<< orphan*/  rc_bbr_cwnd_gain; int /*<<< orphan*/  rc_bbr_hptsi_gain; int /*<<< orphan*/  rc_lt_epoch; int /*<<< orphan*/  rc_rtt_epoch; int /*<<< orphan*/  rc_lost; int /*<<< orphan*/  rc_delivered; int /*<<< orphan*/  r_app_limited_until; scalar_t__ rc_lost_bytes; scalar_t__ rc_sacked; int /*<<< orphan*/  rc_rttprop; int /*<<< orphan*/  rc_delrate; int /*<<< orphan*/  rc_bbr_cur_del_rate; } ;
struct tcp_bbr {TYPE_2__ r_ctl; int /*<<< orphan*/  rc_lt_use_bw; TYPE_1__* rc_inp; int /*<<< orphan*/  rc_bbr_state; int /*<<< orphan*/  rc_tp; } ;
struct TYPE_3__ {int /*<<< orphan*/  inp_in_input; int /*<<< orphan*/  inp_in_hpts; } ;

/* Variables and functions */
 int /*<<< orphan*/  bbr_get_bw (struct tcp_bbr*) ; 
 int /*<<< orphan*/  bbr_state_val (struct tcp_bbr*) ; 
 int /*<<< orphan*/  ctf_flight_size (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  get_filter_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_filter_value_small (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct tcp_log_bbr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __inline void
bbr_fill_in_logging_data(struct tcp_bbr *bbr, struct tcp_log_bbr *l, uint32_t cts)
{
	memset(l, 0, sizeof(union tcp_log_stackspecific));
	l->cur_del_rate = bbr->r_ctl.rc_bbr_cur_del_rate;
	l->delRate = get_filter_value(&bbr->r_ctl.rc_delrate);
	l->rttProp = get_filter_value_small(&bbr->r_ctl.rc_rttprop);
	l->bw_inuse = bbr_get_bw(bbr);
	l->inflight = ctf_flight_size(bbr->rc_tp,
			  (bbr->r_ctl.rc_sacked + bbr->r_ctl.rc_lost_bytes));
	l->applimited = bbr->r_ctl.r_app_limited_until;
	l->delivered = bbr->r_ctl.rc_delivered;
	l->timeStamp = cts;
	l->lost = bbr->r_ctl.rc_lost;
	l->bbr_state = bbr->rc_bbr_state;
	l->bbr_substate = bbr_state_val(bbr);
	l->epoch = bbr->r_ctl.rc_rtt_epoch;
	l->lt_epoch = bbr->r_ctl.rc_lt_epoch;
	l->pacing_gain = bbr->r_ctl.rc_bbr_hptsi_gain;
	l->cwnd_gain = bbr->r_ctl.rc_bbr_cwnd_gain;
	l->inhpts = bbr->rc_inp->inp_in_hpts;
	l->ininput = bbr->rc_inp->inp_in_input;
	l->use_lt_bw = bbr->rc_lt_use_bw;
	l->pkts_out = bbr->r_ctl.rc_flight_at_input;
	l->pkt_epoch = bbr->r_ctl.rc_pkt_epoch;
}