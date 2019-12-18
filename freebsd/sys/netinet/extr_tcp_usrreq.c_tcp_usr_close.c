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
struct tcpcb {int dummy; } ;
struct socket {int /*<<< orphan*/  so_state; } ;
struct inpcb {int inp_flags; int /*<<< orphan*/ * inp_socket; } ;
struct epoch_tracker {int dummy; } ;

/* Variables and functions */
 int INP_DROPPED ; 
 int INP_SOCKREF ; 
 int INP_TIMEWAIT ; 
 int /*<<< orphan*/  INP_WLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  INP_WUNLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NET_EPOCH_ENTER (struct epoch_tracker) ; 
 int /*<<< orphan*/  NET_EPOCH_EXIT (struct epoch_tracker) ; 
 int /*<<< orphan*/  PRU_CLOSE ; 
 int /*<<< orphan*/  SOCK_LOCK (struct socket*) ; 
 int /*<<< orphan*/  SOCK_UNLOCK (struct socket*) ; 
 int /*<<< orphan*/  SS_PROTOREF ; 
 int /*<<< orphan*/  TCPDEBUG0 ; 
 int /*<<< orphan*/  TCPDEBUG1 () ; 
 int /*<<< orphan*/  TCPDEBUG2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCP_PROBE2 (int /*<<< orphan*/ ,struct tcpcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug__user ; 
 struct tcpcb* intotcpcb (struct inpcb*) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 
 int /*<<< orphan*/  tcp_disconnect (struct tcpcb*) ; 

__attribute__((used)) static void
tcp_usr_close(struct socket *so)
{
	struct inpcb *inp;
	struct tcpcb *tp = NULL;
	struct epoch_tracker et;
	TCPDEBUG0;

	inp = sotoinpcb(so);
	KASSERT(inp != NULL, ("tcp_usr_close: inp == NULL"));

	NET_EPOCH_ENTER(et);
	INP_WLOCK(inp);
	KASSERT(inp->inp_socket != NULL,
	    ("tcp_usr_close: inp_socket == NULL"));

	/*
	 * If we still have full TCP state, and we're not dropped, initiate
	 * a disconnect.
	 */
	if (!(inp->inp_flags & INP_TIMEWAIT) &&
	    !(inp->inp_flags & INP_DROPPED)) {
		tp = intotcpcb(inp);
		TCPDEBUG1();
		tcp_disconnect(tp);
		TCPDEBUG2(PRU_CLOSE);
		TCP_PROBE2(debug__user, tp, PRU_CLOSE);
	}
	if (!(inp->inp_flags & INP_DROPPED)) {
		SOCK_LOCK(so);
		so->so_state |= SS_PROTOREF;
		SOCK_UNLOCK(so);
		inp->inp_flags |= INP_SOCKREF;
	}
	INP_WUNLOCK(inp);
	NET_EPOCH_EXIT(et);
}