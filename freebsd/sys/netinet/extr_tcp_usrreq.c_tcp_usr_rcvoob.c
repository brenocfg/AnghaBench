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
struct tcpcb {int t_oobflags; int /*<<< orphan*/  t_iobc; } ;
struct TYPE_2__ {int sb_state; } ;
struct socket {scalar_t__ so_oobmark; int so_options; TYPE_1__ so_rcv; } ;
struct mbuf {int m_len; } ;
struct inpcb {int inp_flags; } ;

/* Variables and functions */
 int ECONNRESET ; 
 int EINVAL ; 
 int EWOULDBLOCK ; 
 int INP_DROPPED ; 
 int INP_TIMEWAIT ; 
 int /*<<< orphan*/  INP_WLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  INP_WUNLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int MSG_PEEK ; 
 int /*<<< orphan*/  PRU_RCVOOB ; 
 int SBS_RCVATMARK ; 
 int SO_OOBINLINE ; 
 int /*<<< orphan*/  TCPDEBUG0 ; 
 int /*<<< orphan*/  TCPDEBUG1 () ; 
 int /*<<< orphan*/  TCPDEBUG2 (int /*<<< orphan*/ ) ; 
 int TCPOOB_HADDATA ; 
 int TCPOOB_HAVEDATA ; 
 int /*<<< orphan*/  TCP_PROBE2 (int /*<<< orphan*/ ,struct tcpcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caddr_t ; 
 int /*<<< orphan*/  debug__user ; 
 struct tcpcb* intotcpcb (struct inpcb*) ; 
 int /*<<< orphan*/ * mtod (struct mbuf*,int /*<<< orphan*/ ) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 

__attribute__((used)) static int
tcp_usr_rcvoob(struct socket *so, struct mbuf *m, int flags)
{
	int error = 0;
	struct inpcb *inp;
	struct tcpcb *tp = NULL;

	TCPDEBUG0;
	inp = sotoinpcb(so);
	KASSERT(inp != NULL, ("tcp_usr_rcvoob: inp == NULL"));
	INP_WLOCK(inp);
	if (inp->inp_flags & (INP_TIMEWAIT | INP_DROPPED)) {
		error = ECONNRESET;
		goto out;
	}
	tp = intotcpcb(inp);
	TCPDEBUG1();
	if ((so->so_oobmark == 0 &&
	     (so->so_rcv.sb_state & SBS_RCVATMARK) == 0) ||
	    so->so_options & SO_OOBINLINE ||
	    tp->t_oobflags & TCPOOB_HADDATA) {
		error = EINVAL;
		goto out;
	}
	if ((tp->t_oobflags & TCPOOB_HAVEDATA) == 0) {
		error = EWOULDBLOCK;
		goto out;
	}
	m->m_len = 1;
	*mtod(m, caddr_t) = tp->t_iobc;
	if ((flags & MSG_PEEK) == 0)
		tp->t_oobflags ^= (TCPOOB_HAVEDATA | TCPOOB_HADDATA);

out:
	TCPDEBUG2(PRU_RCVOOB);
	TCP_PROBE2(debug__user, tp, PRU_RCVOOB);
	INP_WUNLOCK(inp);
	return (error);
}