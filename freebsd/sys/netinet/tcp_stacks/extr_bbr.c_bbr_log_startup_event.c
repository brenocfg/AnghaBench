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
struct TYPE_9__ {int /*<<< orphan*/  cur_del_rate; int /*<<< orphan*/  flex8; int /*<<< orphan*/  flex6; int /*<<< orphan*/  flex5; scalar_t__ flex4; void* flex3; void* flex2; void* flex1; } ;
union tcp_log_stackspecific {TYPE_4__ u_bbr; } ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  void* uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  rc_bbr_lastbtlbw; int /*<<< orphan*/  rc_lost_at_startup; int /*<<< orphan*/  rc_target_at_state; } ;
struct tcp_bbr {int /*<<< orphan*/  rc_tv; TYPE_3__* rc_inp; TYPE_5__* rc_tp; TYPE_1__ r_ctl; } ;
struct TYPE_10__ {scalar_t__ t_logstate; } ;
struct TYPE_8__ {TYPE_2__* inp_socket; } ;
struct TYPE_7__ {int /*<<< orphan*/  so_snd; int /*<<< orphan*/  so_rcv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBR_LOG_REDUCE ; 
 int /*<<< orphan*/  TCP_LOG_EVENTP (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union tcp_log_stackspecific*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ TCP_LOG_STATE_OFF ; 
 int /*<<< orphan*/  bbr_fill_in_logging_data (struct tcp_bbr*,TYPE_4__*,void*) ; 

__attribute__((used)) static void
bbr_log_startup_event(struct tcp_bbr *bbr, uint32_t cts, uint32_t flex1, uint32_t flex2, uint32_t flex3, uint8_t reason)
{
	if (bbr->rc_tp->t_logstate != TCP_LOG_STATE_OFF) {
		union tcp_log_stackspecific log;

		bbr_fill_in_logging_data(bbr, &log.u_bbr, cts);
		log.u_bbr.flex1 = flex1;
		log.u_bbr.flex2 = flex2;
		log.u_bbr.flex3 = flex3;
		log.u_bbr.flex4 = 0; 
		log.u_bbr.flex5 = bbr->r_ctl.rc_target_at_state;
		log.u_bbr.flex6 = bbr->r_ctl.rc_lost_at_startup;
		log.u_bbr.flex8 = reason;
		log.u_bbr.cur_del_rate = bbr->r_ctl.rc_bbr_lastbtlbw;
		TCP_LOG_EVENTP(bbr->rc_tp, NULL,
		    &bbr->rc_inp->inp_socket->so_rcv,
		    &bbr->rc_inp->inp_socket->so_snd,
		    BBR_LOG_REDUCE, 0,
		    0, &log, false, &bbr->rc_tv);
	}
}