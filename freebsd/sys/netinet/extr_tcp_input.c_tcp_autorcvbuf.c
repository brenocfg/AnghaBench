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
struct tcphdr {int dummy; } ;
struct tcpcb {int t_srtt; scalar_t__ rfbuf_ts; int rfbuf_cnt; } ;
struct TYPE_2__ {int sb_flags; int sb_hiwat; } ;
struct socket {TYPE_1__ so_rcv; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int SB_AUTOSIZE ; 
 int /*<<< orphan*/  TCP_PROBE6 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct tcpcb*,struct mbuf*,struct tcpcb*,struct tcphdr*,int) ; 
 int TCP_RTT_SHIFT ; 
 int TCP_TS_TO_TICKS (scalar_t__) ; 
 int V_tcp_autorcvbuf_max ; 
 scalar_t__ V_tcp_do_autorcvbuf ; 
 int min (int,int) ; 
 int /*<<< orphan*/  receive__autoresize ; 
 scalar_t__ tcp_ts_getticks () ; 

int
tcp_autorcvbuf(struct mbuf *m, struct tcphdr *th, struct socket *so,
    struct tcpcb *tp, int tlen)
{
	int newsize = 0;

	if (V_tcp_do_autorcvbuf && (so->so_rcv.sb_flags & SB_AUTOSIZE) &&
	    tp->t_srtt != 0 && tp->rfbuf_ts != 0 &&
	    TCP_TS_TO_TICKS(tcp_ts_getticks() - tp->rfbuf_ts) >
	    ((tp->t_srtt >> TCP_RTT_SHIFT)/2)) {
		if (tp->rfbuf_cnt > ((so->so_rcv.sb_hiwat / 2)/ 4 * 3) &&
		    so->so_rcv.sb_hiwat < V_tcp_autorcvbuf_max) {
			newsize = min((so->so_rcv.sb_hiwat + (so->so_rcv.sb_hiwat/2)), V_tcp_autorcvbuf_max);
		}
		TCP_PROBE6(receive__autoresize, NULL, tp, m, tp, th, newsize);

		/* Start over with next RTT. */
		tp->rfbuf_ts = 0;
		tp->rfbuf_cnt = 0;
	} else {
		tp->rfbuf_cnt += tlen;	/* add up */
	}
	return (newsize);
}