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
struct socket {int dummy; } ;
struct inpcb {int inp_flags; } ;
struct epoch_tracker {int dummy; } ;

/* Variables and functions */
 int ECONNRESET ; 
 int INP_DROPPED ; 
 int INP_TIMEWAIT ; 
 int /*<<< orphan*/  INP_WLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  INP_WUNLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NET_EPOCH_ENTER (struct epoch_tracker) ; 
 int /*<<< orphan*/  NET_EPOCH_EXIT (struct epoch_tracker) ; 
 int /*<<< orphan*/  PRU_DISCONNECT ; 
 int /*<<< orphan*/  TCPDEBUG0 ; 
 int /*<<< orphan*/  TCPDEBUG1 () ; 
 int /*<<< orphan*/  TCPDEBUG2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCP_PROBE2 (int /*<<< orphan*/ ,struct tcpcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug__user ; 
 struct tcpcb* intotcpcb (struct inpcb*) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 
 int /*<<< orphan*/  tcp_disconnect (struct tcpcb*) ; 

__attribute__((used)) static int
tcp_usr_disconnect(struct socket *so)
{
	struct inpcb *inp;
	struct tcpcb *tp = NULL;
	struct epoch_tracker et;
	int error = 0;

	TCPDEBUG0;
	NET_EPOCH_ENTER(et);
	inp = sotoinpcb(so);
	KASSERT(inp != NULL, ("tcp_usr_disconnect: inp == NULL"));
	INP_WLOCK(inp);
	if (inp->inp_flags & INP_TIMEWAIT)
		goto out;
	if (inp->inp_flags & INP_DROPPED) {
		error = ECONNRESET;
		goto out;
	}
	tp = intotcpcb(inp);
	TCPDEBUG1();
	tcp_disconnect(tp);
out:
	TCPDEBUG2(PRU_DISCONNECT);
	TCP_PROBE2(debug__user, tp, PRU_DISCONNECT);
	INP_WUNLOCK(inp);
	NET_EPOCH_EXIT(et);
	return (error);
}