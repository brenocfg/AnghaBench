#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tcpcb {int t_state; TYPE_1__* t_inpcb; int /*<<< orphan*/  t_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  inp_socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  INP_WLOCK_ASSERT (TYPE_1__*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NET_EPOCH_ASSERT () ; 
#define  TCPS_CLOSED 133 
#define  TCPS_CLOSE_WAIT 132 
#define  TCPS_ESTABLISHED 131 
 int TCPS_FIN_WAIT_1 ; 
 int TCPS_FIN_WAIT_2 ; 
 int TCPS_LAST_ACK ; 
#define  TCPS_LISTEN 130 
#define  TCPS_SYN_RECEIVED 129 
#define  TCPS_SYN_SENT 128 
 int /*<<< orphan*/  TF_NEEDFIN ; 
 int TP_MAXIDLE (struct tcpcb*) ; 
 int /*<<< orphan*/  TT_2MSL ; 
 int /*<<< orphan*/  soisdisconnected (int /*<<< orphan*/ ) ; 
 struct tcpcb* tcp_close (struct tcpcb*) ; 
 scalar_t__ tcp_fast_finwait2_recycle ; 
 int tcp_finwait2_timeout ; 
 int /*<<< orphan*/  tcp_offload_listen_stop (struct tcpcb*) ; 
 int /*<<< orphan*/  tcp_state_change (struct tcpcb*,int) ; 
 int /*<<< orphan*/  tcp_timer_activate (struct tcpcb*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
tcp_usrclosed(struct tcpcb *tp)
{

	NET_EPOCH_ASSERT();
	INP_WLOCK_ASSERT(tp->t_inpcb);

	switch (tp->t_state) {
	case TCPS_LISTEN:
#ifdef TCP_OFFLOAD
		tcp_offload_listen_stop(tp);
#endif
		tcp_state_change(tp, TCPS_CLOSED);
		/* FALLTHROUGH */
	case TCPS_CLOSED:
		tp = tcp_close(tp);
		/*
		 * tcp_close() should never return NULL here as the socket is
		 * still open.
		 */
		KASSERT(tp != NULL,
		    ("tcp_usrclosed: tcp_close() returned NULL"));
		break;

	case TCPS_SYN_SENT:
	case TCPS_SYN_RECEIVED:
		tp->t_flags |= TF_NEEDFIN;
		break;

	case TCPS_ESTABLISHED:
		tcp_state_change(tp, TCPS_FIN_WAIT_1);
		break;

	case TCPS_CLOSE_WAIT:
		tcp_state_change(tp, TCPS_LAST_ACK);
		break;
	}
	if (tp->t_state >= TCPS_FIN_WAIT_2) {
		soisdisconnected(tp->t_inpcb->inp_socket);
		/* Prevent the connection hanging in FIN_WAIT_2 forever. */
		if (tp->t_state == TCPS_FIN_WAIT_2) {
			int timeout;

			timeout = (tcp_fast_finwait2_recycle) ? 
			    tcp_finwait2_timeout : TP_MAXIDLE(tp);
			tcp_timer_activate(tp, TT_2MSL, timeout);
		}
	}
}