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
struct TYPE_9__ {int /*<<< orphan*/  flex8; scalar_t__ flex7; int /*<<< orphan*/  flex6; int /*<<< orphan*/  flex5; int /*<<< orphan*/  flex4; int /*<<< orphan*/  flex3; scalar_t__ flex2; int /*<<< orphan*/  flex1; } ;
union tcp_log_stackspecific {TYPE_4__ u_bbr; } ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  rc_bbr_state_atflight; int /*<<< orphan*/  rc_pace_min_segs; int /*<<< orphan*/  rc_pace_max_segs; int /*<<< orphan*/  gain_epoch; int /*<<< orphan*/  rc_target_at_state; } ;
struct tcp_bbr {int /*<<< orphan*/  rc_tv; TYPE_3__* rc_inp; TYPE_5__* rc_tp; TYPE_1__ r_ctl; scalar_t__ rc_last_options; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_10__ {scalar_t__ t_logstate; scalar_t__ t_maxseg; } ;
struct TYPE_8__ {TYPE_2__* inp_socket; } ;
struct TYPE_7__ {int /*<<< orphan*/  so_snd; int /*<<< orphan*/  so_rcv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBR_LOG_EXIT_GAIN ; 
 int /*<<< orphan*/  TCP_LOG_EVENTP (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union tcp_log_stackspecific*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ TCP_LOG_STATE_OFF ; 
 int /*<<< orphan*/  bbr_fill_in_logging_data (struct tcp_bbr*,TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bbr_log_exit_gain(struct tcp_bbr *bbr, uint32_t cts, int32_t entry_method)
{
	if (bbr->rc_tp->t_logstate != TCP_LOG_STATE_OFF) {
		union tcp_log_stackspecific log;

		bbr_fill_in_logging_data(bbr, &log.u_bbr, cts);
		log.u_bbr.flex1 = bbr->r_ctl.rc_target_at_state;
		log.u_bbr.flex2 = (bbr->rc_tp->t_maxseg - bbr->rc_last_options);
		log.u_bbr.flex3 = bbr->r_ctl.gain_epoch;
		log.u_bbr.flex4 = bbr->r_ctl.rc_pace_max_segs;
		log.u_bbr.flex5 = bbr->r_ctl.rc_pace_min_segs;
		log.u_bbr.flex6 = bbr->r_ctl.rc_bbr_state_atflight;
		log.u_bbr.flex7 = 0;
		log.u_bbr.flex8 = entry_method;
		TCP_LOG_EVENTP(bbr->rc_tp, NULL,
		    &bbr->rc_inp->inp_socket->so_rcv,
		    &bbr->rc_inp->inp_socket->so_snd,
		    BBR_LOG_EXIT_GAIN, 0,
		    0, &log, false, &bbr->rc_tv);
	}
}