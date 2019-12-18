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
struct TYPE_9__ {scalar_t__ epoch; int /*<<< orphan*/  bw_inuse; void* pkts_out; int /*<<< orphan*/  flex7; int /*<<< orphan*/  flex6; int /*<<< orphan*/  flex5; void* flex4; void* flex3; void* flex2; int /*<<< orphan*/  flex1; } ;
union tcp_log_stackspecific {TYPE_4__ u_bbr; } ;
typedef  void* uint32_t ;
struct TYPE_6__ {scalar_t__ rc_lt_epoch_use; scalar_t__ rc_pkt_epoch; scalar_t__ rc_lt_epoch; int /*<<< orphan*/  rc_lt_bw; int /*<<< orphan*/  rc_lt_del; int /*<<< orphan*/  rc_lt_lost; } ;
struct tcp_bbr {scalar_t__ rc_lt_use_bw; int /*<<< orphan*/  rc_tv; TYPE_3__* rc_inp; TYPE_5__* rc_tp; TYPE_1__ r_ctl; int /*<<< orphan*/  rc_lt_is_sampling; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_10__ {scalar_t__ t_logstate; } ;
struct TYPE_8__ {TYPE_2__* inp_socket; } ;
struct TYPE_7__ {int /*<<< orphan*/  so_snd; int /*<<< orphan*/  so_rcv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBR_LOG_BWSAMP ; 
 int /*<<< orphan*/  TCP_LOG_EVENTP (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union tcp_log_stackspecific*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ TCP_LOG_STATE_OFF ; 
 int /*<<< orphan*/  bbr_fill_in_logging_data (struct tcp_bbr*,TYPE_4__*,void*) ; 

__attribute__((used)) static void
bbr_log_type_ltbw(struct tcp_bbr *bbr, uint32_t cts, int32_t reason,
	uint32_t newbw, uint32_t obw, uint32_t diff,
	uint32_t tim)
{
	if (/*bbr_verbose_logging && */(bbr->rc_tp->t_logstate != TCP_LOG_STATE_OFF)) {
		union tcp_log_stackspecific log;

		bbr_fill_in_logging_data(bbr, &log.u_bbr, cts);
		log.u_bbr.flex1 = reason;
		log.u_bbr.flex2 = newbw;
		log.u_bbr.flex3 = obw;
		log.u_bbr.flex4 = diff;
		log.u_bbr.flex5 = bbr->r_ctl.rc_lt_lost;
		log.u_bbr.flex6 = bbr->r_ctl.rc_lt_del;
		log.u_bbr.flex7 = bbr->rc_lt_is_sampling;
		log.u_bbr.pkts_out = tim;
		log.u_bbr.bw_inuse = bbr->r_ctl.rc_lt_bw;
		if (bbr->rc_lt_use_bw == 0)
			log.u_bbr.epoch = bbr->r_ctl.rc_pkt_epoch - bbr->r_ctl.rc_lt_epoch;
		else
			log.u_bbr.epoch = bbr->r_ctl.rc_pkt_epoch - bbr->r_ctl.rc_lt_epoch_use;			
		TCP_LOG_EVENTP(bbr->rc_tp, NULL,
		    &bbr->rc_inp->inp_socket->so_rcv,
		    &bbr->rc_inp->inp_socket->so_snd,
		    BBR_LOG_BWSAMP, 0,
		    0, &log, false, &bbr->rc_tv);
	}
}