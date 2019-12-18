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
struct tcptw {struct inpcb* tw_inpcb; } ;
struct socket {int so_state; } ;
struct inpcb {int inp_flags; struct socket* inp_socket; int /*<<< orphan*/ * inp_ppcb; } ;

/* Variables and functions */
 int INP_SOCKREF ; 
 int INP_TIMEWAIT ; 
 int /*<<< orphan*/  INP_WLOCK_ASSERT (struct inpcb*) ; 
 int /*<<< orphan*/  INP_WUNLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  NET_EPOCH_ASSERT () ; 
 int /*<<< orphan*/  SOCK_LOCK (struct socket*) ; 
 int SS_PROTOREF ; 
 int /*<<< orphan*/  TCPSTAT_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_pcbdrop (struct inpcb*) ; 
 int /*<<< orphan*/  in_pcbfree (struct inpcb*) ; 
 struct tcptw* intotw (struct inpcb*) ; 
 int /*<<< orphan*/  sofree (struct socket*) ; 
 int /*<<< orphan*/  tcp_tw_2msl_stop (struct tcptw*,int) ; 
 int /*<<< orphan*/  tcps_closed ; 

void
tcp_twclose(struct tcptw *tw, int reuse)
{
	struct socket *so;
	struct inpcb *inp;

	/*
	 * At this point, we are in one of two situations:
	 *
	 * (1) We have no socket, just an inpcb<->twtcp pair.  We can free
	 *     all state.
	 *
	 * (2) We have a socket -- if we own a reference, release it and
	 *     notify the socket layer.
	 */
	inp = tw->tw_inpcb;
	KASSERT((inp->inp_flags & INP_TIMEWAIT), ("tcp_twclose: !timewait"));
	KASSERT(intotw(inp) == tw, ("tcp_twclose: inp_ppcb != tw"));
	NET_EPOCH_ASSERT();
	INP_WLOCK_ASSERT(inp);

	tcp_tw_2msl_stop(tw, reuse);
	inp->inp_ppcb = NULL;
	in_pcbdrop(inp);

	so = inp->inp_socket;
	if (so != NULL) {
		/*
		 * If there's a socket, handle two cases: first, we own a
		 * strong reference, which we will now release, or we don't
		 * in which case another reference exists (XXXRW: think
		 * about this more), and we don't need to take action.
		 */
		if (inp->inp_flags & INP_SOCKREF) {
			inp->inp_flags &= ~INP_SOCKREF;
			INP_WUNLOCK(inp);
			SOCK_LOCK(so);
			KASSERT(so->so_state & SS_PROTOREF,
			    ("tcp_twclose: INP_SOCKREF && !SS_PROTOREF"));
			so->so_state &= ~SS_PROTOREF;
			sofree(so);
		} else {
			/*
			 * If we don't own the only reference, the socket and
			 * inpcb need to be left around to be handled by
			 * tcp_usr_detach() later.
			 */
			INP_WUNLOCK(inp);
		}
	} else {
		/*
		 * The socket has been already cleaned-up for us, only free the
		 * inpcb.
		 */
		in_pcbfree(inp);
	}
	TCPSTAT_INC(tcps_closed);
}