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
struct TYPE_9__ {int /*<<< orphan*/  pkts_out; int /*<<< orphan*/  flex8; int /*<<< orphan*/  flex6; int /*<<< orphan*/  flex5; int /*<<< orphan*/  flex4; int /*<<< orphan*/  flex3; int /*<<< orphan*/  flex2; int /*<<< orphan*/  flex1; } ;
union tcp_log_stackspecific {TYPE_4__ u_bbr; } ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  rc_target_at_state; int /*<<< orphan*/  rc_hpts_flags; } ;
struct tcp_bbr {int /*<<< orphan*/  rc_tv; TYPE_3__* rc_inp; TYPE_5__* rc_tp; int /*<<< orphan*/  rc_pacer_started; TYPE_1__ r_ctl; int /*<<< orphan*/  rc_in_persist; int /*<<< orphan*/  bbr_timer_src; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_10__ {scalar_t__ t_logstate; int /*<<< orphan*/  t_rxtcur; } ;
struct TYPE_8__ {TYPE_2__* inp_socket; } ;
struct TYPE_7__ {int /*<<< orphan*/  so_snd; int /*<<< orphan*/  so_rcv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBR_LOG_TIMERCANC ; 
 int /*<<< orphan*/  TCP_LOG_EVENTP (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union tcp_log_stackspecific*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ TCP_LOG_STATE_OFF ; 
 int /*<<< orphan*/  TICKS_2_USEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bbr_fill_in_logging_data (struct tcp_bbr*,TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bbr_log_to_cancel(struct tcp_bbr *bbr, int32_t line, uint32_t cts, uint8_t hpts_removed)
{
	if (bbr->rc_tp->t_logstate != TCP_LOG_STATE_OFF) {
		union tcp_log_stackspecific log;

		bbr_fill_in_logging_data(bbr, &log.u_bbr, cts);
		log.u_bbr.flex1 = line;
		log.u_bbr.flex2 = bbr->bbr_timer_src;
		log.u_bbr.flex3 = bbr->r_ctl.rc_hpts_flags;
		log.u_bbr.flex4 = bbr->rc_in_persist;
		log.u_bbr.flex5 = bbr->r_ctl.rc_target_at_state;
		log.u_bbr.flex6 = TICKS_2_USEC(bbr->rc_tp->t_rxtcur);
		log.u_bbr.flex8 = hpts_removed;
		log.u_bbr.pkts_out = bbr->rc_pacer_started;
		TCP_LOG_EVENTP(bbr->rc_tp, NULL,
		    &bbr->rc_inp->inp_socket->so_rcv,
		    &bbr->rc_inp->inp_socket->so_snd,
		    BBR_LOG_TIMERCANC, 0,
		    0, &log, false, &bbr->rc_tv);
	}
}