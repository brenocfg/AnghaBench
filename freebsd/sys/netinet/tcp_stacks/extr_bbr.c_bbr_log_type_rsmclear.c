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
struct TYPE_7__ {void* applimited; int /*<<< orphan*/  flex8; int /*<<< orphan*/  flex7; int /*<<< orphan*/  flex6; int /*<<< orphan*/  flex5; int /*<<< orphan*/  flex4; int /*<<< orphan*/  flex3; int /*<<< orphan*/  flex2; void* flex1; } ;
union tcp_log_stackspecific {TYPE_3__ u_bbr; } ;
typedef  void* uint32_t ;
struct tcp_bbr {int /*<<< orphan*/  rc_tv; TYPE_2__* rc_inp; TYPE_4__* rc_tp; } ;
struct bbr_sendmap {int /*<<< orphan*/  r_flags; int /*<<< orphan*/ * r_tim_lastsent; int /*<<< orphan*/  r_dupack; int /*<<< orphan*/  r_rtr_cnt; int /*<<< orphan*/  r_delivered; int /*<<< orphan*/  r_end; int /*<<< orphan*/  r_start; } ;
struct TYPE_8__ {scalar_t__ t_logstate; } ;
struct TYPE_6__ {TYPE_1__* inp_socket; } ;
struct TYPE_5__ {int /*<<< orphan*/  so_snd; int /*<<< orphan*/  so_rcv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBR_RSM_CLEARED ; 
 int /*<<< orphan*/  TCP_LOG_EVENTP (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union tcp_log_stackspecific*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ TCP_LOG_STATE_OFF ; 
 int /*<<< orphan*/  bbr_fill_in_logging_data (struct tcp_bbr*,TYPE_3__*,void*) ; 

__attribute__((used)) static void
bbr_log_type_rsmclear(struct tcp_bbr *bbr, uint32_t cts, struct bbr_sendmap *rsm,
		      uint32_t flags, uint32_t line)
{
	if (bbr->rc_tp->t_logstate != TCP_LOG_STATE_OFF) {
		union tcp_log_stackspecific log;

		bbr_fill_in_logging_data(bbr, &log.u_bbr, cts);
		log.u_bbr.flex1 = line;
		log.u_bbr.flex2 = rsm->r_start;
		log.u_bbr.flex3 = rsm->r_end;
		log.u_bbr.flex4 = rsm->r_delivered;
		log.u_bbr.flex5 = rsm->r_rtr_cnt;
		log.u_bbr.flex6 = rsm->r_dupack;
		log.u_bbr.flex7 = rsm->r_tim_lastsent[0];
		log.u_bbr.flex8 = rsm->r_flags;
		/* Hijack the pkts_out fids */
		log.u_bbr.applimited = flags;
		TCP_LOG_EVENTP(bbr->rc_tp, NULL,
		    &bbr->rc_inp->inp_socket->so_rcv,
		    &bbr->rc_inp->inp_socket->so_snd,
		    BBR_RSM_CLEARED, 0,
		    0, &log, false, &bbr->rc_tv);
	}
}