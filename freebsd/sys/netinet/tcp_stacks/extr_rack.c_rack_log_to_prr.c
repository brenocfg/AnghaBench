#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int flex8; int /*<<< orphan*/  inflight; int /*<<< orphan*/  timeStamp; int /*<<< orphan*/  flex6; int /*<<< orphan*/  flex5; int /*<<< orphan*/  flex4; int /*<<< orphan*/  flex3; int /*<<< orphan*/  flex2; int /*<<< orphan*/  flex1; } ;
union tcp_log_stackspecific {TYPE_4__ u_bbr; } ;
struct timeval {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  rc_sacked; int /*<<< orphan*/  rc_holes_rxt; int /*<<< orphan*/  rc_prr_delivered; int /*<<< orphan*/  rc_prr_sndcnt; int /*<<< orphan*/  rc_prr_recovery_fs; int /*<<< orphan*/  rc_prr_out; } ;
struct tcp_rack {TYPE_3__* rc_inp; TYPE_5__* rc_tp; TYPE_1__ r_ctl; } ;
struct TYPE_11__ {scalar_t__ t_logstate; } ;
struct TYPE_9__ {TYPE_2__* inp_socket; } ;
struct TYPE_8__ {int /*<<< orphan*/  so_snd; int /*<<< orphan*/  so_rcv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBR_LOG_BBRUPD ; 
 int /*<<< orphan*/  TCP_LOG_EVENTP (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union tcp_log_stackspecific*,int,struct timeval*) ; 
 scalar_t__ TCP_LOG_STATE_OFF ; 
 int /*<<< orphan*/  ctf_flight_size (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcp_get_usecs (struct timeval*) ; 

__attribute__((used)) static void
rack_log_to_prr(struct tcp_rack *rack, int frm)
{
	if (rack->rc_tp->t_logstate != TCP_LOG_STATE_OFF) {
		union tcp_log_stackspecific log;
		struct timeval tv;

		memset(&log.u_bbr, 0, sizeof(log.u_bbr));
		log.u_bbr.flex1 = rack->r_ctl.rc_prr_out;
		log.u_bbr.flex2 = rack->r_ctl.rc_prr_recovery_fs;
		log.u_bbr.flex3 = rack->r_ctl.rc_prr_sndcnt;
		log.u_bbr.flex4 = rack->r_ctl.rc_prr_delivered;
		log.u_bbr.flex5 = rack->r_ctl.rc_sacked;
		log.u_bbr.flex6 = rack->r_ctl.rc_holes_rxt;
		log.u_bbr.flex8 = frm;
		log.u_bbr.timeStamp = tcp_get_usecs(&tv);
		log.u_bbr.inflight = ctf_flight_size(rack->rc_tp, rack->r_ctl.rc_sacked);
		TCP_LOG_EVENTP(rack->rc_tp, NULL,
		    &rack->rc_inp->inp_socket->so_rcv,
		    &rack->rc_inp->inp_socket->so_snd,
		    BBR_LOG_BBRUPD, 0,
		    0, &log, false, &tv);
	}
}