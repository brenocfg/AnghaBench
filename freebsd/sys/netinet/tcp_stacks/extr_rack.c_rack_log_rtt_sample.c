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
struct TYPE_7__ {int flex1; int /*<<< orphan*/  inflight; int /*<<< orphan*/  timeStamp; int /*<<< orphan*/  flex8; int /*<<< orphan*/  flex5; int /*<<< orphan*/  flex4; int /*<<< orphan*/  flex3; int /*<<< orphan*/  flex2; } ;
union tcp_log_stackspecific {TYPE_1__ u_bbr; } ;
typedef  int uint32_t ;
struct timeval {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  rc_sacked; int /*<<< orphan*/  sack_moved_extra; int /*<<< orphan*/  sack_noextra_move; int /*<<< orphan*/  sack_count; int /*<<< orphan*/  ack_count; } ;
struct tcp_rack {TYPE_4__* rc_inp; TYPE_5__* rc_tp; TYPE_2__ r_ctl; int /*<<< orphan*/  sack_attack_disable; } ;
typedef  int /*<<< orphan*/  log ;
struct TYPE_11__ {scalar_t__ t_logstate; } ;
struct TYPE_10__ {TYPE_3__* inp_socket; } ;
struct TYPE_9__ {int /*<<< orphan*/  so_snd; int /*<<< orphan*/  so_rcv; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_LOG_EVENTP (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union tcp_log_stackspecific*,int,struct timeval*) ; 
 int /*<<< orphan*/  TCP_LOG_RTT ; 
 scalar_t__ TCP_LOG_STATE_OFF ; 
 int /*<<< orphan*/  ctf_flight_size (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (union tcp_log_stackspecific*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcp_get_usecs (struct timeval*) ; 

__attribute__((used)) static void
rack_log_rtt_sample(struct tcp_rack *rack, uint32_t rtt)
{
	/* 
	 * Log the rtt sample we are
	 * applying to the srtt algorithm in
	 * useconds.
	 */
	if (rack->rc_tp->t_logstate != TCP_LOG_STATE_OFF) {
		union tcp_log_stackspecific log;
		struct timeval tv;
		
		/* Convert our ms to a microsecond */
		memset(&log, 0, sizeof(log));
		log.u_bbr.flex1 = rtt * 1000;
		log.u_bbr.flex2 = rack->r_ctl.ack_count;
		log.u_bbr.flex3 = rack->r_ctl.sack_count;
		log.u_bbr.flex4 = rack->r_ctl.sack_noextra_move;
		log.u_bbr.flex5 = rack->r_ctl.sack_moved_extra;
		log.u_bbr.flex8 = rack->sack_attack_disable;
		log.u_bbr.timeStamp = tcp_get_usecs(&tv);
		log.u_bbr.inflight = ctf_flight_size(rack->rc_tp, rack->r_ctl.rc_sacked);
		TCP_LOG_EVENTP(rack->rc_tp, NULL,
		    &rack->rc_inp->inp_socket->so_rcv,
		    &rack->rc_inp->inp_socket->so_snd,
		    TCP_LOG_RTT, 0,
		    0, &log, false, &tv);
	}
}