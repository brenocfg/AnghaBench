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
struct TYPE_9__ {int flex7; int flex8; void* flex6; void* flex5; int /*<<< orphan*/  flex4; int /*<<< orphan*/  flex3; void* flex2; void* flex1; } ;
union tcp_log_stackspecific {TYPE_4__ u_bbr; } ;
typedef  void* uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  bbr_hptsi_bytes_min; } ;
struct tcp_bbr {int rc_no_pacing; int rc_past_init_win; int rc_use_google; int /*<<< orphan*/  rc_tv; TYPE_3__* rc_inp; TYPE_5__* rc_tp; TYPE_1__ r_ctl; } ;
struct TYPE_10__ {scalar_t__ t_logstate; } ;
struct TYPE_8__ {TYPE_2__* inp_socket; } ;
struct TYPE_7__ {int /*<<< orphan*/  so_snd; int /*<<< orphan*/  so_rcv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBR_LOG_BBRTSO ; 
 int /*<<< orphan*/  TCP_LOG_EVENTP (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union tcp_log_stackspecific*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ TCP_LOG_STATE_OFF ; 
 int /*<<< orphan*/  bbr_fill_in_logging_data (struct tcp_bbr*,TYPE_4__*,void*) ; 
 int /*<<< orphan*/  tcp_min_hptsi_time ; 

__attribute__((used)) static void
bbr_log_type_tsosize(struct tcp_bbr *bbr, uint32_t cts, uint32_t tsosz, uint32_t tls, uint32_t old_val, uint32_t maxseg, int hdwr)
{
	if (bbr->rc_tp->t_logstate != TCP_LOG_STATE_OFF) {
		union tcp_log_stackspecific log;

		bbr_fill_in_logging_data(bbr, &log.u_bbr, cts);
		log.u_bbr.flex1 = tsosz;
		log.u_bbr.flex2 = tls;
		log.u_bbr.flex3 = tcp_min_hptsi_time;
		log.u_bbr.flex4 = bbr->r_ctl.bbr_hptsi_bytes_min;
		log.u_bbr.flex5 = old_val;
		log.u_bbr.flex6 = maxseg;
		log.u_bbr.flex7 = bbr->rc_no_pacing;
		log.u_bbr.flex7 <<= 1;
		log.u_bbr.flex7 |= bbr->rc_past_init_win;
		if (hdwr)
			log.u_bbr.flex8 = 0x80 | bbr->rc_use_google;
		else
			log.u_bbr.flex8 = bbr->rc_use_google;
		TCP_LOG_EVENTP(bbr->rc_tp, NULL,
		    &bbr->rc_inp->inp_socket->so_rcv,
		    &bbr->rc_inp->inp_socket->so_snd,
		    BBR_LOG_BBRTSO, 0,
		    0, &log, false, &bbr->rc_tv);
	}
}