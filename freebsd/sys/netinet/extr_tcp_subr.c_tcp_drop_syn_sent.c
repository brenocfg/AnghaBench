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
struct tcpcb {scalar_t__ t_state; int /*<<< orphan*/  t_flags; } ;
struct inpcb {int inp_flags; } ;

/* Variables and functions */
 int INP_DROPPED ; 
 int INP_TIMEWAIT ; 
 int /*<<< orphan*/  INP_WLOCK_ASSERT (struct inpcb*) ; 
 scalar_t__ IS_FASTOPEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NET_EPOCH_ASSERT () ; 
 scalar_t__ TCPS_SYN_SENT ; 
 struct tcpcb* intotcpcb (struct inpcb*) ; 
 struct tcpcb* tcp_drop (struct tcpcb*,int) ; 
 int /*<<< orphan*/  tcp_fastopen_disable_path (struct tcpcb*) ; 

struct inpcb *
tcp_drop_syn_sent(struct inpcb *inp, int errno)
{
	struct tcpcb *tp;

	NET_EPOCH_ASSERT();
	INP_WLOCK_ASSERT(inp);

	if ((inp->inp_flags & INP_TIMEWAIT) ||
	    (inp->inp_flags & INP_DROPPED))
		return (inp);

	tp = intotcpcb(inp);
	if (tp->t_state != TCPS_SYN_SENT)
		return (inp);

	if (IS_FASTOPEN(tp->t_flags))
		tcp_fastopen_disable_path(tp);
	
	tp = tcp_drop(tp, errno);
	if (tp != NULL)
		return (inp);
	else
		return (NULL);
}