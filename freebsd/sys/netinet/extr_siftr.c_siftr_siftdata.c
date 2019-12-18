#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct tcpcb {int t_flags; int /*<<< orphan*/  t_segqlen; scalar_t__ snd_una; scalar_t__ snd_max; int /*<<< orphan*/  t_rxtcur; int /*<<< orphan*/  t_srtt; int /*<<< orphan*/  t_maxseg; int /*<<< orphan*/  t_state; int /*<<< orphan*/  rcv_scale; int /*<<< orphan*/  snd_scale; int /*<<< orphan*/  snd_ssthresh; int /*<<< orphan*/  rcv_wnd; int /*<<< orphan*/  snd_wnd; int /*<<< orphan*/  snd_cwnd; } ;
struct pkt_node {int sack_enabled; int flags; int ipver; int /*<<< orphan*/  tval; int /*<<< orphan*/  direction; int /*<<< orphan*/  flowtype; int /*<<< orphan*/  flowid; int /*<<< orphan*/  t_segqlen; scalar_t__ sent_inflight_bytes; void* rcv_buf_cc; int /*<<< orphan*/  rcv_buf_hiwater; void* snd_buf_cc; int /*<<< orphan*/  snd_buf_hiwater; int /*<<< orphan*/  rxt_length; int /*<<< orphan*/  smoothed_rtt; int /*<<< orphan*/  max_seg_size; int /*<<< orphan*/  conn_state; int /*<<< orphan*/  rcv_scale; int /*<<< orphan*/  snd_scale; int /*<<< orphan*/  snd_ssthresh; scalar_t__ snd_bwnd; int /*<<< orphan*/  rcv_wnd; int /*<<< orphan*/  snd_wnd; int /*<<< orphan*/  snd_cwnd; int /*<<< orphan*/  tcp_foreignport; int /*<<< orphan*/  tcp_localport; int /*<<< orphan*/ * ip_faddr; int /*<<< orphan*/ * ip_laddr; } ;
struct TYPE_10__ {int /*<<< orphan*/ * s6_addr32; } ;
struct TYPE_9__ {int /*<<< orphan*/ * s6_addr32; } ;
struct TYPE_8__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  s_addr; } ;
struct inpcb {int /*<<< orphan*/  inp_flowtype; int /*<<< orphan*/  inp_flowid; TYPE_5__* inp_socket; int /*<<< orphan*/  inp_fport; int /*<<< orphan*/  inp_lport; TYPE_4__ in6p_faddr; TYPE_3__ in6p_laddr; TYPE_2__ inp_faddr; TYPE_1__ inp_laddr; } ;
struct TYPE_12__ {int /*<<< orphan*/  sb_hiwat; } ;
struct TYPE_11__ {TYPE_6__ so_rcv; TYPE_6__ so_snd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIR_IN ; 
 int /*<<< orphan*/  DIR_OUT ; 
 int INP_IPV4 ; 
 int /*<<< orphan*/  INP_RUNLOCK (struct inpcb*) ; 
 int PFIL_IN ; 
 int /*<<< orphan*/  TCP_PROBE1 (int /*<<< orphan*/ ,struct pkt_node**) ; 
 int TF_SACK_PERMIT ; 
 int /*<<< orphan*/  microtime (int /*<<< orphan*/ *) ; 
 void* sbused (TYPE_6__*) ; 
 int /*<<< orphan*/  siftr ; 

__attribute__((used)) static inline void
siftr_siftdata(struct pkt_node *pn, struct inpcb *inp, struct tcpcb *tp,
    int ipver, int dir, int inp_locally_locked)
{
#ifdef SIFTR_IPV6
	if (ipver == INP_IPV4) {
		pn->ip_laddr[3] = inp->inp_laddr.s_addr;
		pn->ip_faddr[3] = inp->inp_faddr.s_addr;
#else
		*((uint32_t *)pn->ip_laddr) = inp->inp_laddr.s_addr;
		*((uint32_t *)pn->ip_faddr) = inp->inp_faddr.s_addr;
#endif
#ifdef SIFTR_IPV6
	} else {
		pn->ip_laddr[0] = inp->in6p_laddr.s6_addr32[0];
		pn->ip_laddr[1] = inp->in6p_laddr.s6_addr32[1];
		pn->ip_laddr[2] = inp->in6p_laddr.s6_addr32[2];
		pn->ip_laddr[3] = inp->in6p_laddr.s6_addr32[3];
		pn->ip_faddr[0] = inp->in6p_faddr.s6_addr32[0];
		pn->ip_faddr[1] = inp->in6p_faddr.s6_addr32[1];
		pn->ip_faddr[2] = inp->in6p_faddr.s6_addr32[2];
		pn->ip_faddr[3] = inp->in6p_faddr.s6_addr32[3];
	}
#endif
	pn->tcp_localport = inp->inp_lport;
	pn->tcp_foreignport = inp->inp_fport;
	pn->snd_cwnd = tp->snd_cwnd;
	pn->snd_wnd = tp->snd_wnd;
	pn->rcv_wnd = tp->rcv_wnd;
	pn->snd_bwnd = 0;		/* Unused, kept for compat. */
	pn->snd_ssthresh = tp->snd_ssthresh;
	pn->snd_scale = tp->snd_scale;
	pn->rcv_scale = tp->rcv_scale;
	pn->conn_state = tp->t_state;
	pn->max_seg_size = tp->t_maxseg;
	pn->smoothed_rtt = tp->t_srtt;
	pn->sack_enabled = (tp->t_flags & TF_SACK_PERMIT) != 0;
	pn->flags = tp->t_flags;
	pn->rxt_length = tp->t_rxtcur;
	pn->snd_buf_hiwater = inp->inp_socket->so_snd.sb_hiwat;
	pn->snd_buf_cc = sbused(&inp->inp_socket->so_snd);
	pn->rcv_buf_hiwater = inp->inp_socket->so_rcv.sb_hiwat;
	pn->rcv_buf_cc = sbused(&inp->inp_socket->so_rcv);
	pn->sent_inflight_bytes = tp->snd_max - tp->snd_una;
	pn->t_segqlen = tp->t_segqlen;
	pn->flowid = inp->inp_flowid;
	pn->flowtype = inp->inp_flowtype;

	/* We've finished accessing the tcb so release the lock. */
	if (inp_locally_locked)
		INP_RUNLOCK(inp);

	pn->ipver = ipver;
	pn->direction = (dir == PFIL_IN ? DIR_IN : DIR_OUT);

	/*
	 * Significantly more accurate than using getmicrotime(), but slower!
	 * Gives true microsecond resolution at the expense of a hit to
	 * maximum pps throughput processing when SIFTR is loaded and enabled.
	 */
	microtime(&pn->tval);
	TCP_PROBE1(siftr, &pn);

}