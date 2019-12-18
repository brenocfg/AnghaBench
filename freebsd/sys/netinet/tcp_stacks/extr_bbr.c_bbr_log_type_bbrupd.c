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
struct TYPE_9__ {int flex7; scalar_t__ epoch; int /*<<< orphan*/  flex8; void* pkts_out; void* flex6; void* flex5; void* flex4; void* flex3; void* flex2; void* flex1; } ;
union tcp_log_stackspecific {TYPE_4__ u_bbr; } ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  void* uint32_t ;
struct TYPE_6__ {scalar_t__ rc_ack_hdwr_delay; } ;
struct tcp_bbr {int /*<<< orphan*/  rc_tv; TYPE_3__* rc_inp; TYPE_5__* rc_tp; TYPE_1__ r_ctl; scalar_t__ rc_ack_was_delayed; } ;
struct TYPE_10__ {scalar_t__ t_logstate; } ;
struct TYPE_8__ {TYPE_2__* inp_socket; } ;
struct TYPE_7__ {int /*<<< orphan*/  so_snd; int /*<<< orphan*/  so_rcv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBR_LOG_BBRUPD ; 
 int /*<<< orphan*/  TCP_LOG_EVENTP (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,union tcp_log_stackspecific*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ TCP_LOG_STATE_OFF ; 
 int /*<<< orphan*/  bbr_fill_in_logging_data (struct tcp_bbr*,TYPE_4__*,void*) ; 

__attribute__((used)) static void
bbr_log_type_bbrupd(struct tcp_bbr *bbr, uint8_t flex8, uint32_t cts,
    uint32_t flex3, uint32_t flex2, uint32_t flex5,
    uint32_t flex6, uint32_t pkts_out, int flex7,
    uint32_t flex4, uint32_t flex1)
{

	if (bbr->rc_tp->t_logstate != TCP_LOG_STATE_OFF) {
		union tcp_log_stackspecific log;

		bbr_fill_in_logging_data(bbr, &log.u_bbr, cts);
		log.u_bbr.flex1 = flex1;
		log.u_bbr.flex2 = flex2;
		log.u_bbr.flex3 = flex3;
		log.u_bbr.flex4 = flex4;
		log.u_bbr.flex5 = flex5;
		log.u_bbr.flex6 = flex6;
		log.u_bbr.flex7 = flex7;
		/* Hijack the pkts_out fids */
		log.u_bbr.pkts_out = pkts_out;
		log.u_bbr.flex8 = flex8;
		if (bbr->rc_ack_was_delayed)
			log.u_bbr.epoch = bbr->r_ctl.rc_ack_hdwr_delay;
		else 
			log.u_bbr.epoch = 0;
		TCP_LOG_EVENTP(bbr->rc_tp, NULL,
		    &bbr->rc_inp->inp_socket->so_rcv,
		    &bbr->rc_inp->inp_socket->so_snd,
		    BBR_LOG_BBRUPD, 0,
		    flex2, &log, false, &bbr->rc_tv);
	}
}