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
struct udphdr {int dummy; } ;
struct udpcb {int /*<<< orphan*/  u_tun_ctx; int /*<<< orphan*/  (* u_tun_func ) (struct mbuf*,int,struct inpcb*,struct sockaddr*,int /*<<< orphan*/ ) ;} ;
struct socket {int so_options; int /*<<< orphan*/  so_rcv; } ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr {int dummy; } ;
struct mbuf {struct mbuf* m_next; } ;
struct inpcb {int inp_flags; int inp_vflag; int inp_flags2; struct socket* inp_socket; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int INP_CONTROLOPTS ; 
 int INP_IPV6 ; 
 int /*<<< orphan*/  INP_LOCK_ASSERT (struct inpcb*) ; 
 int INP_ORIGDSTADDR ; 
 int /*<<< orphan*/  INP_RLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  INP_RUNLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 scalar_t__ IPSEC_CHECK_POLICY (int /*<<< orphan*/ ,struct mbuf*,struct inpcb*) ; 
 scalar_t__ IPSEC_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPV6_ORIGDSTADDR ; 
 int /*<<< orphan*/  SOCKBUF_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOCKBUF_UNLOCK (int /*<<< orphan*/ *) ; 
 int SO_TIMESTAMP ; 
 int /*<<< orphan*/  UDPSTAT_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_pcbref (struct inpcb*) ; 
 int in_pcbrele_rlocked (struct inpcb*) ; 
 struct udpcb* intoudpcb (struct inpcb*) ; 
 int /*<<< orphan*/  ip6_savecontrol (struct inpcb*,struct mbuf*,struct mbuf**) ; 
 int /*<<< orphan*/  ipv6 ; 
 int /*<<< orphan*/  m_adj (struct mbuf*,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 scalar_t__ mac_inpcb_check_deliver (struct inpcb*,struct mbuf*) ; 
 scalar_t__ sbappendaddr_locked (int /*<<< orphan*/ *,struct sockaddr*,struct mbuf*,struct mbuf*) ; 
 struct mbuf* sbcreatecontrol (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sorwakeup_locked (struct socket*) ; 
 int /*<<< orphan*/  stub1 (struct mbuf*,int,struct inpcb*,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udps_fullsock ; 

__attribute__((used)) static int
udp6_append(struct inpcb *inp, struct mbuf *n, int off,
    struct sockaddr_in6 *fromsa)
{
	struct socket *so;
	struct mbuf *opts = NULL, *tmp_opts;
	struct udpcb *up;

	INP_LOCK_ASSERT(inp);

	/*
	 * Engage the tunneling protocol.
	 */
	up = intoudpcb(inp);
	if (up->u_tun_func != NULL) {
		in_pcbref(inp);
		INP_RUNLOCK(inp);
		(*up->u_tun_func)(n, off, inp, (struct sockaddr *)&fromsa[0],
		    up->u_tun_ctx);
		INP_RLOCK(inp);
		return (in_pcbrele_rlocked(inp));
	}
#if defined(IPSEC) || defined(IPSEC_SUPPORT)
	/* Check AH/ESP integrity. */
	if (IPSEC_ENABLED(ipv6)) {
		if (IPSEC_CHECK_POLICY(ipv6, n, inp) != 0) {
			m_freem(n);
			return (0);
		}
	}
#endif /* IPSEC */
#ifdef MAC
	if (mac_inpcb_check_deliver(inp, n) != 0) {
		m_freem(n);
		return (0);
	}
#endif
	opts = NULL;
	if (inp->inp_flags & INP_CONTROLOPTS ||
	    inp->inp_socket->so_options & SO_TIMESTAMP)
		ip6_savecontrol(inp, n, &opts);
	if ((inp->inp_vflag & INP_IPV6) && (inp->inp_flags2 & INP_ORIGDSTADDR)) {
		tmp_opts = sbcreatecontrol((caddr_t)&fromsa[1],
                        sizeof(struct sockaddr_in6), IPV6_ORIGDSTADDR, IPPROTO_IPV6);
                if (tmp_opts) {
                        if (opts) {
                                tmp_opts->m_next = opts;
                                opts = tmp_opts;
                        } else
                                opts = tmp_opts;
                }

	}
	m_adj(n, off + sizeof(struct udphdr));

	so = inp->inp_socket;
	SOCKBUF_LOCK(&so->so_rcv);
	if (sbappendaddr_locked(&so->so_rcv, (struct sockaddr *)&fromsa[0], n,
	    opts) == 0) {
		SOCKBUF_UNLOCK(&so->so_rcv);
		m_freem(n);
		if (opts)
			m_freem(opts);
		UDPSTAT_INC(udps_fullsock);
	} else
		sorwakeup_locked(so);
	return (0);
}