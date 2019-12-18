#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* flex4; void* flex3; void* flex2; void* flex1; } ;
union tcp_log_stackspecific {TYPE_3__ u_bbr; } ;
typedef  void* uint32_t ;
struct tcpcb {scalar_t__ t_logstate; } ;
struct tcp_bbr {int /*<<< orphan*/  rc_tv; TYPE_2__* rc_inp; } ;
typedef  void* int32_t ;
struct TYPE_5__ {TYPE_1__* inp_socket; } ;
struct TYPE_4__ {int /*<<< orphan*/  so_snd; int /*<<< orphan*/  so_rcv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBR_LOG_MSGSIZE ; 
 int /*<<< orphan*/  TCP_LOG_EVENTP (struct tcpcb*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union tcp_log_stackspecific*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ TCP_LOG_STATE_OFF ; 
 int /*<<< orphan*/  bbr_fill_in_logging_data (struct tcp_bbr*,TYPE_3__*,void*) ; 

__attribute__((used)) static void
bbr_log_msgsize_fail(struct tcp_bbr *bbr, struct tcpcb *tp, uint32_t len, uint32_t maxseg, uint32_t mtu, int32_t csum_flags, int32_t tso, uint32_t cts)
{
	if (tp->t_logstate != TCP_LOG_STATE_OFF) {
		union tcp_log_stackspecific log;

		bbr_fill_in_logging_data(bbr, &log.u_bbr, cts);
		log.u_bbr.flex1 = tso;
		log.u_bbr.flex2 = maxseg;
		log.u_bbr.flex3 = mtu;
		log.u_bbr.flex4 = csum_flags;
		TCP_LOG_EVENTP(tp, NULL,
		    &bbr->rc_inp->inp_socket->so_rcv,
		    &bbr->rc_inp->inp_socket->so_snd,
		    BBR_LOG_MSGSIZE, 0,
		    0, &log, false, &bbr->rc_tv);
	}
}