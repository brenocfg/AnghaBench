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
struct TYPE_9__ {int flex2; int flex3; int flex4; int flex5; int /*<<< orphan*/  flex8; int /*<<< orphan*/  flex7; int /*<<< orphan*/  flex1; } ;
union tcp_log_stackspecific {TYPE_4__ u_bbr; } ;
typedef  int uint64_t ;
struct TYPE_6__ {int /*<<< orphan*/  bbr_peer_tsratio; int /*<<< orphan*/  rc_rcvtime; } ;
struct tcp_bbr {int /*<<< orphan*/  rc_tv; TYPE_3__* rc_inp; TYPE_5__* rc_tp; int /*<<< orphan*/  rc_ts_cant_be_used; int /*<<< orphan*/  rc_ts_clock_set; TYPE_1__ r_ctl; } ;
struct TYPE_10__ {scalar_t__ t_logstate; } ;
struct TYPE_8__ {TYPE_2__* inp_socket; } ;
struct TYPE_7__ {int /*<<< orphan*/  so_snd; int /*<<< orphan*/  so_rcv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBR_LOG_TSTMP_VAL ; 
 int /*<<< orphan*/  TCP_LOG_EVENTP (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union tcp_log_stackspecific*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ TCP_LOG_STATE_OFF ; 
 int /*<<< orphan*/  bbr_fill_in_logging_data (struct tcp_bbr*,TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bbr_log_tstmp_validation(struct tcp_bbr *bbr, uint64_t peer_delta, uint64_t delta)
{
	if (bbr->rc_tp->t_logstate != TCP_LOG_STATE_OFF) {
		union tcp_log_stackspecific log;

		bbr_fill_in_logging_data(bbr, &log.u_bbr, bbr->r_ctl.rc_rcvtime);
		log.u_bbr.flex1 = bbr->r_ctl.bbr_peer_tsratio;
		log.u_bbr.flex2 = (peer_delta >> 32);
		log.u_bbr.flex3 = (peer_delta & 0x00000000ffffffff);
		log.u_bbr.flex4 = (delta >> 32);
		log.u_bbr.flex5 = (delta & 0x00000000ffffffff);
		log.u_bbr.flex7 = bbr->rc_ts_clock_set;
		log.u_bbr.flex8 = bbr->rc_ts_cant_be_used;
		TCP_LOG_EVENTP(bbr->rc_tp, NULL,
		    &bbr->rc_inp->inp_socket->so_rcv,
		    &bbr->rc_inp->inp_socket->so_snd,
		    BBR_LOG_TSTMP_VAL, 0,
		    0, &log, false, &bbr->rc_tv);

	}
}