#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  flex8; scalar_t__ flex7; void* flex6; int /*<<< orphan*/  pkts_out; int /*<<< orphan*/  flex5; int /*<<< orphan*/  flex4; int /*<<< orphan*/  flex3; int /*<<< orphan*/  flex2; void* flex1; } ;
union tcp_log_stackspecific {TYPE_4__ u_bbr; } ;
typedef  void* uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  rc_target_at_state; int /*<<< orphan*/  rc_ack_hdwr_delay; int /*<<< orphan*/  rc_bbr_state_time; int /*<<< orphan*/  rc_rcvtime; } ;
struct tcp_bbr {int /*<<< orphan*/  rc_tv; TYPE_3__* rc_inp; TYPE_5__* rc_tp; int /*<<< orphan*/  rc_ack_was_delayed; TYPE_1__ r_ctl; } ;
struct TYPE_10__ {scalar_t__ t_logstate; int /*<<< orphan*/  ts_offset; } ;
struct TYPE_8__ {TYPE_2__* inp_socket; } ;
struct TYPE_7__ {int /*<<< orphan*/  so_snd; int /*<<< orphan*/  so_rcv; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_LOG_EVENTP (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union tcp_log_stackspecific*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TCP_LOG_RTT ; 
 scalar_t__ TCP_LOG_STATE_OFF ; 
 int /*<<< orphan*/  bbr_fill_in_logging_data (struct tcp_bbr*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_tv_to_mssectick (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bbr_log_rtt_sample(struct tcp_bbr *bbr, uint32_t rtt, uint32_t tsin)
{
	/*
	 * Log the rtt sample we are applying to the srtt algorithm in
	 * useconds.
	 */
	if (bbr->rc_tp->t_logstate != TCP_LOG_STATE_OFF) {
		union tcp_log_stackspecific log;

		bbr_fill_in_logging_data(bbr, &log.u_bbr, bbr->r_ctl.rc_rcvtime);
		log.u_bbr.flex1 = rtt;
		log.u_bbr.flex2 = bbr->r_ctl.rc_bbr_state_time;
		log.u_bbr.flex3 = bbr->r_ctl.rc_ack_hdwr_delay;
		log.u_bbr.flex4 = bbr->rc_tp->ts_offset;
		log.u_bbr.flex5 = bbr->r_ctl.rc_target_at_state;
		log.u_bbr.pkts_out = tcp_tv_to_mssectick(&bbr->rc_tv);
		log.u_bbr.flex6 = tsin;
		log.u_bbr.flex7 = 0;
		log.u_bbr.flex8 = bbr->rc_ack_was_delayed;     
		TCP_LOG_EVENTP(bbr->rc_tp, NULL,
		    &bbr->rc_inp->inp_socket->so_rcv,
		    &bbr->rc_inp->inp_socket->so_snd,
		    TCP_LOG_RTT, 0,
		    0, &log, false, &bbr->rc_tv);
	}
}