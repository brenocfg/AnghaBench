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
struct TYPE_7__ {void* flex4; void* flex3; void* flex2; int /*<<< orphan*/  flex1; } ;
union tcp_log_stackspecific {TYPE_3__ u_bbr; } ;
typedef  void* uint32_t ;
struct tcp_bbr {int /*<<< orphan*/  rc_tv; TYPE_2__* rc_inp; TYPE_4__* rc_tp; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_8__ {scalar_t__ t_logstate; } ;
struct TYPE_6__ {TYPE_1__* inp_socket; } ;
struct TYPE_5__ {int /*<<< orphan*/  so_snd; int /*<<< orphan*/  so_rcv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBR_LOG_ENOBUF_JMP ; 
 int /*<<< orphan*/  ENOBUFS ; 
 int /*<<< orphan*/  TCP_LOG_EVENTP (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,union tcp_log_stackspecific*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ TCP_LOG_STATE_OFF ; 
 int /*<<< orphan*/  bbr_fill_in_logging_data (struct tcp_bbr*,TYPE_3__*,void*) ; 

__attribute__((used)) static void
bbr_log_enobuf_jmp(struct tcp_bbr *bbr, uint32_t len, uint32_t cts,
    int32_t line, uint32_t o_len, uint32_t segcnt, uint32_t segsiz)
{
	if (bbr->rc_tp->t_logstate != TCP_LOG_STATE_OFF) {
		union tcp_log_stackspecific log;

		bbr_fill_in_logging_data(bbr, &log.u_bbr, cts);
		log.u_bbr.flex1 = line;
		log.u_bbr.flex2 = o_len;
		log.u_bbr.flex3 = segcnt;
		log.u_bbr.flex4 = segsiz;
		TCP_LOG_EVENTP(bbr->rc_tp, NULL,
		    &bbr->rc_inp->inp_socket->so_rcv,
		    &bbr->rc_inp->inp_socket->so_snd,
		    BBR_LOG_ENOBUF_JMP, ENOBUFS,
		    len, &log, true, &bbr->rc_tv);
	}
}