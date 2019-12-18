#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tcpcb {scalar_t__ t_state; int /*<<< orphan*/ * t_tfo_pending; struct inpcb* t_inpcb; } ;
struct socket {int so_state; } ;
struct inpcb {int inp_flags; struct socket* inp_socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  INP_INFO_LOCK_ASSERT (int /*<<< orphan*/ *) ; 
 int INP_SOCKREF ; 
 int /*<<< orphan*/  INP_WLOCK_ASSERT (struct inpcb*) ; 
 int /*<<< orphan*/  INP_WUNLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  SOCK_LOCK (struct socket*) ; 
 int SS_PROTOREF ; 
 int /*<<< orphan*/  TCPSTAT_INC (int /*<<< orphan*/ ) ; 
 scalar_t__ TCPS_CLOSED ; 
 scalar_t__ TCPS_LISTEN ; 
 int /*<<< orphan*/  V_tcbinfo ; 
 int /*<<< orphan*/  in_pcbdrop (struct inpcb*) ; 
 int /*<<< orphan*/  sofree (struct socket*) ; 
 int /*<<< orphan*/  soisdisconnected (struct socket*) ; 
 int /*<<< orphan*/  tcp_fastopen_decrement_counter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_offload_listen_stop (struct tcpcb*) ; 
 int /*<<< orphan*/  tcp_state_change (struct tcpcb*,scalar_t__) ; 
 int /*<<< orphan*/  tcps_closed ; 

struct tcpcb *
tcp_close(struct tcpcb *tp)
{
	struct inpcb *inp = tp->t_inpcb;
	struct socket *so;

	INP_INFO_LOCK_ASSERT(&V_tcbinfo);
	INP_WLOCK_ASSERT(inp);

#ifdef TCP_OFFLOAD
	if (tp->t_state == TCPS_LISTEN)
		tcp_offload_listen_stop(tp);
#endif
	/*
	 * This releases the TFO pending counter resource for TFO listen
	 * sockets as well as passively-created TFO sockets that transition
	 * from SYN_RECEIVED to CLOSED.
	 */
	if (tp->t_tfo_pending) {
		tcp_fastopen_decrement_counter(tp->t_tfo_pending);
		tp->t_tfo_pending = NULL;
	}
	in_pcbdrop(inp);
	TCPSTAT_INC(tcps_closed);
	if (tp->t_state != TCPS_CLOSED)
		tcp_state_change(tp, TCPS_CLOSED);
	KASSERT(inp->inp_socket != NULL, ("tcp_close: inp_socket NULL"));
	so = inp->inp_socket;
	soisdisconnected(so);
	if (inp->inp_flags & INP_SOCKREF) {
		KASSERT(so->so_state & SS_PROTOREF,
		    ("tcp_close: !SS_PROTOREF"));
		inp->inp_flags &= ~INP_SOCKREF;
		INP_WUNLOCK(inp);
		SOCK_LOCK(so);
		so->so_state &= ~SS_PROTOREF;
		sofree(so);
		return (NULL);
	}
	return (tp);
}