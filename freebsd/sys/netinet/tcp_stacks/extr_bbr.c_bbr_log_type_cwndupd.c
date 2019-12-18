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
struct TYPE_9__ {void* flex8; void* flex6; void* flex5; void* flex4; void* flex3; void* flex2; void* flex1; } ;
union tcp_log_stackspecific {TYPE_4__ u_bbr; } ;
typedef  void* uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  rc_rcvtime; } ;
struct tcp_bbr {int /*<<< orphan*/  rc_tv; TYPE_3__* rc_inp; TYPE_5__* rc_tp; TYPE_1__ r_ctl; } ;
typedef  void* int32_t ;
struct TYPE_10__ {scalar_t__ t_logstate; } ;
struct TYPE_8__ {TYPE_2__* inp_socket; } ;
struct TYPE_7__ {int /*<<< orphan*/  so_snd; int /*<<< orphan*/  so_rcv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBR_LOG_CWND ; 
 int /*<<< orphan*/  TCP_LOG_EVENTP (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union tcp_log_stackspecific*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ TCP_LOG_STATE_OFF ; 
 int /*<<< orphan*/  bbr_fill_in_logging_data (struct tcp_bbr*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ bbr_verbose_logging ; 

__attribute__((used)) static void
bbr_log_type_cwndupd(struct tcp_bbr *bbr, uint32_t bytes_this_ack, uint32_t chg,
    uint32_t prev_acked, int32_t meth, uint32_t target, uint32_t th_ack, int32_t line)
{
	if (bbr_verbose_logging && (bbr->rc_tp->t_logstate != TCP_LOG_STATE_OFF)) {
		union tcp_log_stackspecific log;

		bbr_fill_in_logging_data(bbr, &log.u_bbr, bbr->r_ctl.rc_rcvtime);
		log.u_bbr.flex1 = line;
		log.u_bbr.flex2 = prev_acked;
		log.u_bbr.flex3 = bytes_this_ack;
		log.u_bbr.flex4 = chg;
		log.u_bbr.flex5 = th_ack;
		log.u_bbr.flex6 = target;
		log.u_bbr.flex8 = meth;
		TCP_LOG_EVENTP(bbr->rc_tp, NULL,
		    &bbr->rc_inp->inp_socket->so_rcv,
		    &bbr->rc_inp->inp_socket->so_snd,
		    BBR_LOG_CWND, 0,
		    0, &log, false, &bbr->rc_tv);
	}
}