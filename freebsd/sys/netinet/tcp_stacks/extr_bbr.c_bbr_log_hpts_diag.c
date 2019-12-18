#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int cur_del_rate; int /*<<< orphan*/  delRate; int /*<<< orphan*/  rttProp; int /*<<< orphan*/  bw_inuse; int /*<<< orphan*/  inflight; int /*<<< orphan*/  delivered; int /*<<< orphan*/  applimited; int /*<<< orphan*/  pkts_out; int /*<<< orphan*/  lt_epoch; int /*<<< orphan*/  epoch; int /*<<< orphan*/  flex8; int /*<<< orphan*/  flex7; int /*<<< orphan*/  flex6; int /*<<< orphan*/  flex5; int /*<<< orphan*/  flex4; int /*<<< orphan*/  flex3; int /*<<< orphan*/  flex2; int /*<<< orphan*/  flex1; } ;
union tcp_log_stackspecific {TYPE_3__ u_bbr; } ;
typedef  int /*<<< orphan*/  uint32_t ;
struct tcp_bbr {int /*<<< orphan*/  rc_tv; TYPE_2__* rc_inp; TYPE_4__* rc_tp; } ;
struct hpts_diag {int p_curtick; int p_lasttick; int /*<<< orphan*/  maxticks; int /*<<< orphan*/  wheel_cts; int /*<<< orphan*/  wheel_tick; int /*<<< orphan*/  p_runningtick; int /*<<< orphan*/  p_prev_slot; int /*<<< orphan*/  hpts_sleep_time; int /*<<< orphan*/  co_ret; int /*<<< orphan*/  yet_to_sleep; int /*<<< orphan*/  have_slept; int /*<<< orphan*/  p_on_min_sleep; int /*<<< orphan*/  p_hpts_active; int /*<<< orphan*/  need_new_to; int /*<<< orphan*/  slot_remaining; int /*<<< orphan*/  inp_hptsslot; int /*<<< orphan*/  slot_req; int /*<<< orphan*/  p_cur_slot; int /*<<< orphan*/  p_nxt_slot; } ;
struct TYPE_8__ {scalar_t__ t_logstate; } ;
struct TYPE_6__ {TYPE_1__* inp_socket; } ;
struct TYPE_5__ {int /*<<< orphan*/  so_snd; int /*<<< orphan*/  so_rcv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBR_LOG_HPTSDIAG ; 
 int /*<<< orphan*/  TCP_LOG_EVENTP (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union tcp_log_stackspecific*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ TCP_LOG_STATE_OFF ; 
 int /*<<< orphan*/  bbr_fill_in_logging_data (struct tcp_bbr*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ bbr_verbose_logging ; 

__attribute__((used)) static void
bbr_log_hpts_diag(struct tcp_bbr *bbr, uint32_t cts, struct hpts_diag *diag)
{
	if (bbr_verbose_logging && (bbr->rc_tp->t_logstate != TCP_LOG_STATE_OFF)) {
		union tcp_log_stackspecific log;

		bbr_fill_in_logging_data(bbr, &log.u_bbr, cts);
		log.u_bbr.flex1 = diag->p_nxt_slot;
		log.u_bbr.flex2 = diag->p_cur_slot;
		log.u_bbr.flex3 = diag->slot_req;
		log.u_bbr.flex4 = diag->inp_hptsslot;
		log.u_bbr.flex5 = diag->slot_remaining;
		log.u_bbr.flex6 = diag->need_new_to;
		log.u_bbr.flex7 = diag->p_hpts_active;
		log.u_bbr.flex8 = diag->p_on_min_sleep;
		/* Hijack other fields as needed  */
		log.u_bbr.epoch = diag->have_slept;
		log.u_bbr.lt_epoch = diag->yet_to_sleep;
		log.u_bbr.pkts_out = diag->co_ret;
		log.u_bbr.applimited = diag->hpts_sleep_time;
		log.u_bbr.delivered = diag->p_prev_slot;
		log.u_bbr.inflight = diag->p_runningtick;
		log.u_bbr.bw_inuse = diag->wheel_tick;
		log.u_bbr.rttProp = diag->wheel_cts;
		log.u_bbr.delRate = diag->maxticks;
		log.u_bbr.cur_del_rate = diag->p_curtick;
		log.u_bbr.cur_del_rate <<= 32;
		log.u_bbr.cur_del_rate |= diag->p_lasttick;
		TCP_LOG_EVENTP(bbr->rc_tp, NULL,
		    &bbr->rc_inp->inp_socket->so_rcv,
		    &bbr->rc_inp->inp_socket->so_snd,
		    BBR_LOG_HPTSDIAG, 0,
		    0, &log, false, &bbr->rc_tv);
	}
}