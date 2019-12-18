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
struct thread {int dummy; } ;
struct tcpcb {int dummy; } ;
struct socket {int so_options; scalar_t__ so_linger; } ;
struct inpcb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PRU_ATTACH ; 
 int SO_LINGER ; 
 int /*<<< orphan*/  TCPDEBUG0 ; 
 int /*<<< orphan*/  TCPDEBUG1 () ; 
 int /*<<< orphan*/  TCPDEBUG2 (int /*<<< orphan*/ ) ; 
 scalar_t__ TCP_LINGERTIME ; 
 int /*<<< orphan*/  TCP_PROBE2 (int /*<<< orphan*/ ,struct tcpcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug__user ; 
 struct tcpcb* intotcpcb (struct inpcb*) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 
 int tcp_attach (struct socket*) ; 

__attribute__((used)) static int
tcp_usr_attach(struct socket *so, int proto, struct thread *td)
{
	struct inpcb *inp;
	struct tcpcb *tp = NULL;
	int error;
	TCPDEBUG0;

	inp = sotoinpcb(so);
	KASSERT(inp == NULL, ("tcp_usr_attach: inp != NULL"));
	TCPDEBUG1();

	error = tcp_attach(so);
	if (error)
		goto out;

	if ((so->so_options & SO_LINGER) && so->so_linger == 0)
		so->so_linger = TCP_LINGERTIME;

	inp = sotoinpcb(so);
	tp = intotcpcb(inp);
out:
	TCPDEBUG2(PRU_ATTACH);
	TCP_PROBE2(debug__user, tp, PRU_ATTACH);
	return error;
}