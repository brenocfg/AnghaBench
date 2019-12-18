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
struct TYPE_6__ {int flex4; int use_lt_bw; int inflight; int /*<<< orphan*/  cur_del_rate; int /*<<< orphan*/  lost; int /*<<< orphan*/  pkts_out; int /*<<< orphan*/  lt_epoch; int /*<<< orphan*/  epoch; int /*<<< orphan*/  timeStamp; int /*<<< orphan*/  delivered; int /*<<< orphan*/  applimited; int /*<<< orphan*/  flex6; int /*<<< orphan*/  flex5; int /*<<< orphan*/  flex3; int /*<<< orphan*/  flex2; int /*<<< orphan*/  flex1; } ;
union tcp_log_stackspecific {TYPE_3__ u_bbr; } ;
struct timeval {int dummy; } ;
struct tcpcb {TYPE_2__* t_inpcb; } ;
struct tcp_hpts_entry {int /*<<< orphan*/  p_runningtick; int /*<<< orphan*/  p_hpts_sleep_time; int /*<<< orphan*/  p_delayed_by; int /*<<< orphan*/  saved_prev_slot; int /*<<< orphan*/  saved_curslot; int /*<<< orphan*/  saved_curtick; int /*<<< orphan*/  overidden_sleep; int /*<<< orphan*/  p_on_queue_cnt; int /*<<< orphan*/  p_curtick; int /*<<< orphan*/  p_prev_slot; int /*<<< orphan*/  p_cur_slot; int /*<<< orphan*/  p_nxt_slot; } ;
struct TYPE_5__ {TYPE_1__* inp_socket; } ;
struct TYPE_4__ {int /*<<< orphan*/  so_snd; int /*<<< orphan*/  so_rcv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBR_LOG_HPTSDIAG ; 
 int /*<<< orphan*/  TCP_LOG_EVENTP (struct tcpcb*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union tcp_log_stackspecific*,int,struct timeval*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcp_tv_to_usectick (struct timeval*) ; 

__attribute__((used)) static void
tcp_hpts_log(struct tcp_hpts_entry *hpts, struct tcpcb *tp, struct timeval *tv,
	     int ticks_to_run, int idx)
{
	union tcp_log_stackspecific log;
	
	memset(&log.u_bbr, 0, sizeof(log.u_bbr));
	log.u_bbr.flex1 = hpts->p_nxt_slot;
	log.u_bbr.flex2 = hpts->p_cur_slot;
	log.u_bbr.flex3 = hpts->p_prev_slot;
	log.u_bbr.flex4 = idx;
	log.u_bbr.flex5 = hpts->p_curtick;
	log.u_bbr.flex6 = hpts->p_on_queue_cnt;
	log.u_bbr.use_lt_bw = 1;
	log.u_bbr.inflight = ticks_to_run;
	log.u_bbr.applimited = hpts->overidden_sleep;
	log.u_bbr.delivered = hpts->saved_curtick;
	log.u_bbr.timeStamp = tcp_tv_to_usectick(tv);
	log.u_bbr.epoch = hpts->saved_curslot;
	log.u_bbr.lt_epoch = hpts->saved_prev_slot;
	log.u_bbr.pkts_out = hpts->p_delayed_by;
	log.u_bbr.lost = hpts->p_hpts_sleep_time;
	log.u_bbr.cur_del_rate = hpts->p_runningtick;
	TCP_LOG_EVENTP(tp, NULL,
		       &tp->t_inpcb->inp_socket->so_rcv,
		       &tp->t_inpcb->inp_socket->so_snd,
		       BBR_LOG_HPTSDIAG, 0,
		       0, &log, false, tv);
}