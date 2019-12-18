#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct tcptemp {int /*<<< orphan*/  tt_t; int /*<<< orphan*/  tt_ipgen; } ;
struct tcpcb {scalar_t__ t_state; scalar_t__ t_rcvtime; scalar_t__ snd_una; int /*<<< orphan*/  rcv_nxt; struct inpcb* t_inpcb; } ;
struct TYPE_3__ {int /*<<< orphan*/  rc_hpts_flags; } ;
struct tcp_bbr {int /*<<< orphan*/  rc_inp; TYPE_1__ r_ctl; scalar_t__ rc_all_timers_stopped; } ;
struct mbuf {int dummy; } ;
struct inpcb {TYPE_2__* inp_socket; } ;
struct TYPE_4__ {int so_options; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBR_TO_FRM_KEEP ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  PACE_TMR_KEEP ; 
 int SO_KEEPALIVE ; 
 int /*<<< orphan*/  TCPSTAT_INC (int /*<<< orphan*/ ) ; 
 scalar_t__ TCPS_CLOSING ; 
 scalar_t__ TCPS_ESTABLISHED ; 
 scalar_t__ TP_KEEPIDLE (struct tcpcb*) ; 
 scalar_t__ TP_MAXIDLE (struct tcpcb*) ; 
 int /*<<< orphan*/  bbr_log_to_event (struct tcp_bbr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bbr_start_hpts_timer (struct tcp_bbr*,struct tcpcb*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct tcptemp*,int /*<<< orphan*/ ) ; 
 scalar_t__ tcp_always_keepalive ; 
 int /*<<< orphan*/  tcp_respond (struct tcpcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mbuf*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_set_inp_to_drop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tcptemp* tcpip_maketemplate (struct inpcb*) ; 
 int /*<<< orphan*/  tcps_keepdrops ; 
 int /*<<< orphan*/  tcps_keepprobe ; 
 int /*<<< orphan*/  tcps_keeptimeo ; 
 scalar_t__ ticks ; 

__attribute__((used)) static int
bbr_timeout_keepalive(struct tcpcb *tp, struct tcp_bbr *bbr, uint32_t cts)
{
	struct tcptemp *t_template;
	struct inpcb *inp;

	if (bbr->rc_all_timers_stopped) {
		return (1);
	}
	bbr->r_ctl.rc_hpts_flags &= ~PACE_TMR_KEEP;
	inp = tp->t_inpcb;
	bbr_log_to_event(bbr, cts, BBR_TO_FRM_KEEP);
	/*
	 * Keep-alive timer went off; send something or drop connection if
	 * idle for too long.
	 */
	TCPSTAT_INC(tcps_keeptimeo);
	if (tp->t_state < TCPS_ESTABLISHED)
		goto dropit;
	if ((tcp_always_keepalive || inp->inp_socket->so_options & SO_KEEPALIVE) &&
	    tp->t_state <= TCPS_CLOSING) {
		if (ticks - tp->t_rcvtime >= TP_KEEPIDLE(tp) + TP_MAXIDLE(tp))
			goto dropit;
		/*
		 * Send a packet designed to force a response if the peer is
		 * up and reachable: either an ACK if the connection is
		 * still alive, or an RST if the peer has closed the
		 * connection due to timeout or reboot. Using sequence
		 * number tp->snd_una-1 causes the transmitted zero-length
		 * segment to lie outside the receive window; by the
		 * protocol spec, this requires the correspondent TCP to
		 * respond.
		 */
		TCPSTAT_INC(tcps_keepprobe);
		t_template = tcpip_maketemplate(inp);
		if (t_template) {
			tcp_respond(tp, t_template->tt_ipgen,
			    &t_template->tt_t, (struct mbuf *)NULL,
			    tp->rcv_nxt, tp->snd_una - 1, 0);
			free(t_template, M_TEMP);
		}
	}
	bbr_start_hpts_timer(bbr, tp, cts, 4, 0, 0);
	return (1);
dropit:
	TCPSTAT_INC(tcps_keepdrops);
	tcp_set_inp_to_drop(bbr->rc_inp, ETIMEDOUT);
	return (1);
}