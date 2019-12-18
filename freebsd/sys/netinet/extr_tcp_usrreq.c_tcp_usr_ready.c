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
struct tcpcb {TYPE_1__* t_fb; } ;
struct socket {int /*<<< orphan*/  so_snd; } ;
struct mbuf {int dummy; } ;
struct inpcb {int inp_flags; } ;
struct TYPE_2__ {int (* tfb_tcp_output ) (struct tcpcb*) ;} ;

/* Variables and functions */
 int ECONNRESET ; 
 int INP_DROPPED ; 
 int INP_TIMEWAIT ; 
 int /*<<< orphan*/  INP_WLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  INP_WUNLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  SOCKBUF_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOCKBUF_UNLOCK (int /*<<< orphan*/ *) ; 
 struct tcpcb* intotcpcb (struct inpcb*) ; 
 int /*<<< orphan*/  mb_free_notready (struct mbuf*,int) ; 
 int sbready (int /*<<< orphan*/ *,struct mbuf*,int) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 
 int stub1 (struct tcpcb*) ; 

__attribute__((used)) static int
tcp_usr_ready(struct socket *so, struct mbuf *m, int count)
{
	struct inpcb *inp;
	struct tcpcb *tp;
	int error;

	inp = sotoinpcb(so);
	INP_WLOCK(inp);
	if (inp->inp_flags & (INP_TIMEWAIT | INP_DROPPED)) {
		INP_WUNLOCK(inp);
		mb_free_notready(m, count);
		return (ECONNRESET);
	}
	tp = intotcpcb(inp);

	SOCKBUF_LOCK(&so->so_snd);
	error = sbready(&so->so_snd, m, count);
	SOCKBUF_UNLOCK(&so->so_snd);
	if (error == 0)
		error = tp->t_fb->tfb_tcp_output(tp);
	INP_WUNLOCK(inp);

	return (error);
}