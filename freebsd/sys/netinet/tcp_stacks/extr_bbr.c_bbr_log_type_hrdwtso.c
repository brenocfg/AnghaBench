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
struct TYPE_8__ {int flex2; int flex4; int flex7; int flex8; scalar_t__ flex5; int /*<<< orphan*/  flex3; int /*<<< orphan*/  flex1; } ;
union tcp_log_stackspecific {TYPE_4__ u_bbr; } ;
typedef  int /*<<< orphan*/  uint32_t ;
struct timeval {int dummy; } ;
struct tcpcb {scalar_t__ t_logstate; TYPE_3__* t_inpcb; } ;
struct TYPE_5__ {int /*<<< orphan*/  rc_pace_max_segs; int /*<<< orphan*/  rc_pace_min_segs; } ;
struct tcp_bbr {TYPE_1__ r_ctl; } ;
struct TYPE_7__ {TYPE_2__* inp_socket; } ;
struct TYPE_6__ {int /*<<< orphan*/  so_snd; int /*<<< orphan*/  so_rcv; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_HDWR_TLS ; 
 int /*<<< orphan*/  TCP_LOG_EVENTP (struct tcpcb*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union tcp_log_stackspecific*,int,struct timeval*) ; 
 scalar_t__ TCP_LOG_STATE_OFF ; 
 int /*<<< orphan*/  bbr_fill_in_logging_data (struct tcp_bbr*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_get_usecs (struct timeval*) ; 

__attribute__((used)) static void
bbr_log_type_hrdwtso(struct tcpcb *tp, struct tcp_bbr *bbr, int len, int mod, int what_we_can_send)
{
	if (tp->t_logstate != TCP_LOG_STATE_OFF) {
		union tcp_log_stackspecific log;
		struct timeval tv;
		uint32_t cts;

		cts = tcp_get_usecs(&tv);
		bbr_fill_in_logging_data(bbr, &log.u_bbr, cts);
		log.u_bbr.flex1 = bbr->r_ctl.rc_pace_min_segs;
		log.u_bbr.flex2 = what_we_can_send;
		log.u_bbr.flex3 = bbr->r_ctl.rc_pace_max_segs;
		log.u_bbr.flex4 = len;
		log.u_bbr.flex5 = 0;
		log.u_bbr.flex7 = mod;
		log.u_bbr.flex8 = 1;
		TCP_LOG_EVENTP(tp, NULL,
		    &tp->t_inpcb->inp_socket->so_rcv,
		    &tp->t_inpcb->inp_socket->so_snd,
		    TCP_HDWR_TLS, 0,
		    0, &log, false, &tv);
	}
}