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
struct TYPE_7__ {int flex5; int flex8; int /*<<< orphan*/  flex7; void* flex6; void* flex4; void* flex3; void* flex2; void* flex1; } ;
union tcp_log_stackspecific {TYPE_3__ u_bbr; } ;
typedef  int uint64_t ;
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct tcp_bbr {int /*<<< orphan*/  rc_tv; TYPE_2__* rc_inp; TYPE_4__* rc_tp; } ;
struct TYPE_8__ {scalar_t__ t_logstate; } ;
struct TYPE_6__ {TYPE_1__* inp_socket; } ;
struct TYPE_5__ {int /*<<< orphan*/  so_snd; int /*<<< orphan*/  so_rcv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBR_LOG_HPTSI_CALC ; 
 int /*<<< orphan*/  TCP_LOG_EVENTP (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,union tcp_log_stackspecific*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ TCP_LOG_STATE_OFF ; 
 int /*<<< orphan*/  bbr_fill_in_logging_data (struct tcp_bbr*,TYPE_3__*,void*) ; 

__attribute__((used)) static void
bbr_log_pacing_delay_calc(struct tcp_bbr *bbr, uint16_t gain, uint32_t len,
    uint32_t cts, uint32_t usecs, uint64_t bw, uint32_t override, int mod)
{
	if (bbr->rc_tp->t_logstate != TCP_LOG_STATE_OFF) {
		union tcp_log_stackspecific log;

		bbr_fill_in_logging_data(bbr, &log.u_bbr, cts);
		log.u_bbr.flex1 = usecs;
		log.u_bbr.flex2 = len;
		log.u_bbr.flex3 = (uint32_t)((bw >> 32) & 0x00000000ffffffff);
		log.u_bbr.flex4 = (uint32_t)(bw & 0x00000000ffffffff);
		if (override)
			log.u_bbr.flex5 = (1 << 2);
		else
			log.u_bbr.flex5 = 0;
		log.u_bbr.flex6 = override;
		log.u_bbr.flex7 = gain;
		log.u_bbr.flex8 = mod;
		TCP_LOG_EVENTP(bbr->rc_tp, NULL,
		    &bbr->rc_inp->inp_socket->so_rcv,
		    &bbr->rc_inp->inp_socket->so_snd,
		    BBR_LOG_HPTSI_CALC, 0,
		    len, &log, false, &bbr->rc_tv);
	}
}