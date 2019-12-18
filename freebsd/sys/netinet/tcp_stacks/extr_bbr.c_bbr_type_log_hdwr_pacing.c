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
struct TYPE_7__ {int flex1; int flex2; int flex3; int flex4; int bw_inuse; int flex5; int flex6; int flex8; int /*<<< orphan*/  pkts_out; } ;
union tcp_log_stackspecific {TYPE_3__ u_bbr; } ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct tcp_bbr {int skip_gain; int gain_is_limited; int bbr_hdrw_pacing; int /*<<< orphan*/  rc_tv; TYPE_2__* rc_inp; TYPE_4__* rc_tp; } ;
struct ifnet {int dummy; } ;
struct TYPE_8__ {scalar_t__ t_logstate; int /*<<< orphan*/  t_maxseg; } ;
struct TYPE_6__ {TYPE_1__* inp_socket; } ;
struct TYPE_5__ {int /*<<< orphan*/  so_snd; int /*<<< orphan*/  so_rcv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBR_LOG_HDWR_PACE ; 
 int /*<<< orphan*/  TCP_LOG_EVENTP (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union tcp_log_stackspecific*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ TCP_LOG_STATE_OFF ; 
 int /*<<< orphan*/  bbr_fill_in_logging_data (struct tcp_bbr*,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bbr_type_log_hdwr_pacing(struct tcp_bbr *bbr, const struct ifnet *ifp,
			 uint64_t rate, uint64_t hw_rate, int line, uint32_t cts,
			 int error)
{
	if (bbr->rc_tp->t_logstate != TCP_LOG_STATE_OFF) {
		union tcp_log_stackspecific log;

		bbr_fill_in_logging_data(bbr, &log.u_bbr, cts);
		log.u_bbr.flex1 = ((hw_rate >> 32) & 0x00000000ffffffff);
		log.u_bbr.flex2 = (hw_rate & 0x00000000ffffffff);
		log.u_bbr.flex3 = (((uint64_t)ifp  >> 32) & 0x00000000ffffffff);
		log.u_bbr.flex4 = ((uint64_t)ifp & 0x00000000ffffffff);
		log.u_bbr.bw_inuse = rate;
		log.u_bbr.flex5 = line;
		log.u_bbr.flex6 = error;
		log.u_bbr.flex8 = bbr->skip_gain;
		log.u_bbr.flex8 <<= 1;
		log.u_bbr.flex8 |= bbr->gain_is_limited;
		log.u_bbr.flex8 <<= 1;
		log.u_bbr.flex8 |= bbr->bbr_hdrw_pacing;
		log.u_bbr.pkts_out = bbr->rc_tp->t_maxseg;
		TCP_LOG_EVENTP(bbr->rc_tp, NULL,
		    &bbr->rc_inp->inp_socket->so_rcv,
		    &bbr->rc_inp->inp_socket->so_snd,
		    BBR_LOG_HDWR_PACE, 0,
		    0, &log, false, &bbr->rc_tv);
	}
}