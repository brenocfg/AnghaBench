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
struct tcphdr {scalar_t__ th_seq; } ;
struct tcpcb {int /*<<< orphan*/  t_flags2; scalar_t__ rcv_nxt; scalar_t__ t_fb_ptr; } ;
struct tcp_rack {scalar_t__ rc_allow_data_af_clo; int r_wanted_output; } ;
struct socket {int /*<<< orphan*/  so_snd; } ;
struct mbuf {int dummy; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  BANDLIM_UNLIMITED ; 
 int /*<<< orphan*/  TCPSTAT_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TF2_DROP_AF_DATA ; 
 int /*<<< orphan*/  ctf_do_dropwithreset (struct mbuf*,struct tcpcb*,struct tcphdr*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ sbavail (int /*<<< orphan*/ *) ; 
 struct tcpcb* tcp_close (struct tcpcb*) ; 
 int /*<<< orphan*/  tcps_rcvafterclose ; 

__attribute__((used)) static int
rack_check_data_after_close(struct mbuf *m, 
    struct tcpcb *tp, int32_t *tlen, struct tcphdr *th, struct socket *so)
{
	struct tcp_rack *rack;

	rack = (struct tcp_rack *)tp->t_fb_ptr;
	if (rack->rc_allow_data_af_clo == 0) {
	close_now:
		tp = tcp_close(tp);
		TCPSTAT_INC(tcps_rcvafterclose);
		ctf_do_dropwithreset(m, tp, th, BANDLIM_UNLIMITED, (*tlen));
		return (1);
	}
	if (sbavail(&so->so_snd) == 0)
		goto close_now;
	/* Ok we allow data that is ignored and a followup reset */
	tp->rcv_nxt = th->th_seq + *tlen;
	tp->t_flags2 |= TF2_DROP_AF_DATA;
	rack->r_wanted_output = 1;
	*tlen = 0;
	return (0);
}