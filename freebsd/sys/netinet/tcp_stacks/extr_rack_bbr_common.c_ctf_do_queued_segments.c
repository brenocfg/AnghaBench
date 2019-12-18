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
struct tcpcb {int /*<<< orphan*/ * t_tail_pkt; struct mbuf* t_in_pkt; } ;
struct socket {int dummy; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 scalar_t__ ctf_process_inbound_raw (struct tcpcb*,struct socket*,struct mbuf*,int) ; 

int
ctf_do_queued_segments(struct socket *so, struct tcpcb *tp, int have_pkt)
{
	struct mbuf *m;

	/* First lets see if we have old packets */
	if (tp->t_in_pkt) {
		m = tp->t_in_pkt;
		tp->t_in_pkt = NULL;
		tp->t_tail_pkt = NULL;
		if (ctf_process_inbound_raw(tp, so, m, have_pkt)) {
			/* We lost the tcpcb (maybe a RST came in)? */
			return(1);
		}
	}
	return (0);
}