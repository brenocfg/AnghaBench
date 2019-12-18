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
struct TYPE_10__ {int /*<<< orphan*/  inflight; int /*<<< orphan*/  timeStamp; int /*<<< orphan*/  flex8; int /*<<< orphan*/  flex7; int /*<<< orphan*/  flex5; int /*<<< orphan*/  flex2; int /*<<< orphan*/  flex1; int /*<<< orphan*/  ininput; int /*<<< orphan*/  inhpts; } ;
union tcp_log_stackspecific {TYPE_4__ u_bbr; } ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct timeval {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  rc_sacked; int /*<<< orphan*/  rc_prr_sndcnt; int /*<<< orphan*/  rc_hpts_flags; } ;
struct tcp_rack {TYPE_3__* rc_inp; TYPE_5__* rc_tp; TYPE_1__ r_ctl; int /*<<< orphan*/  rc_in_persist; } ;
struct TYPE_11__ {scalar_t__ t_logstate; } ;
struct TYPE_9__ {TYPE_2__* inp_socket; int /*<<< orphan*/  inp_in_input; int /*<<< orphan*/  inp_in_hpts; } ;
struct TYPE_8__ {int /*<<< orphan*/  so_snd; int /*<<< orphan*/  so_rcv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBR_LOG_JUSTRET ; 
 int /*<<< orphan*/  TCP_LOG_EVENTP (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union tcp_log_stackspecific*,int,struct timeval*) ; 
 scalar_t__ TCP_LOG_STATE_OFF ; 
 int /*<<< orphan*/  ctf_flight_size (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcp_get_usecs (struct timeval*) ; 

__attribute__((used)) static void
rack_log_type_just_return(struct tcp_rack *rack, uint32_t cts, uint32_t tlen, uint32_t slot, uint8_t hpts_calling)
{
	if (rack->rc_tp->t_logstate != TCP_LOG_STATE_OFF) {
		union tcp_log_stackspecific log;
		struct timeval tv;

		memset(&log.u_bbr, 0, sizeof(log.u_bbr));
		log.u_bbr.inhpts = rack->rc_inp->inp_in_hpts;
		log.u_bbr.ininput = rack->rc_inp->inp_in_input;
		log.u_bbr.flex1 = slot;
		log.u_bbr.flex2 = rack->r_ctl.rc_hpts_flags;
		log.u_bbr.flex5 = rack->r_ctl.rc_prr_sndcnt;
		log.u_bbr.flex7 = hpts_calling;
		log.u_bbr.flex8 = rack->rc_in_persist;
		log.u_bbr.timeStamp = tcp_get_usecs(&tv);
		log.u_bbr.inflight = ctf_flight_size(rack->rc_tp, rack->r_ctl.rc_sacked);
		TCP_LOG_EVENTP(rack->rc_tp, NULL,
		    &rack->rc_inp->inp_socket->so_rcv,
		    &rack->rc_inp->inp_socket->so_snd,
		    BBR_LOG_JUSTRET, 0,
		    tlen, &log, false, &tv);
	}
}