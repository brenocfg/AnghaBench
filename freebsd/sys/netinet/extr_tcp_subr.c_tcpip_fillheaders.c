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
struct tcphdr {int th_off; scalar_t__ th_sum; scalar_t__ th_urp; scalar_t__ th_win; scalar_t__ th_flags; scalar_t__ th_x2; scalar_t__ th_ack; scalar_t__ th_seq; int /*<<< orphan*/  th_dport; int /*<<< orphan*/  th_sport; } ;
struct ip6_hdr {int ip6_flow; int ip6_vfc; int /*<<< orphan*/  ip6_dst; int /*<<< orphan*/  ip6_src; int /*<<< orphan*/  ip6_plen; void* ip6_nxt; } ;
struct ip {int ip_hl; int /*<<< orphan*/  ip_dst; int /*<<< orphan*/  ip_src; void* ip_p; scalar_t__ ip_sum; int /*<<< orphan*/  ip_ttl; scalar_t__ ip_off; scalar_t__ ip_id; scalar_t__ ip_len; int /*<<< orphan*/  ip_tos; int /*<<< orphan*/  ip_v; } ;
struct inpcb {int inp_vflag; int inp_flow; int /*<<< orphan*/  inp_fport; int /*<<< orphan*/  inp_lport; int /*<<< orphan*/  inp_faddr; int /*<<< orphan*/  inp_laddr; int /*<<< orphan*/  inp_ip_ttl; int /*<<< orphan*/  inp_ip_tos; int /*<<< orphan*/  in6p_faddr; int /*<<< orphan*/  in6p_laddr; } ;

/* Variables and functions */
 int INP_IPV6 ; 
 int /*<<< orphan*/  INP_WLOCK_ASSERT (struct inpcb*) ; 
 void* IPPROTO_TCP ; 
 int IPV6_FLOWINFO_MASK ; 
 int IPV6_VERSION ; 
 int IPV6_VERSION_MASK ; 
 int /*<<< orphan*/  IPVERSION ; 
 int /*<<< orphan*/  htons (int) ; 

void
tcpip_fillheaders(struct inpcb *inp, void *ip_ptr, void *tcp_ptr)
{
	struct tcphdr *th = (struct tcphdr *)tcp_ptr;

	INP_WLOCK_ASSERT(inp);

#ifdef INET6
	if ((inp->inp_vflag & INP_IPV6) != 0) {
		struct ip6_hdr *ip6;

		ip6 = (struct ip6_hdr *)ip_ptr;
		ip6->ip6_flow = (ip6->ip6_flow & ~IPV6_FLOWINFO_MASK) |
			(inp->inp_flow & IPV6_FLOWINFO_MASK);
		ip6->ip6_vfc = (ip6->ip6_vfc & ~IPV6_VERSION_MASK) |
			(IPV6_VERSION & IPV6_VERSION_MASK);
		ip6->ip6_nxt = IPPROTO_TCP;
		ip6->ip6_plen = htons(sizeof(struct tcphdr));
		ip6->ip6_src = inp->in6p_laddr;
		ip6->ip6_dst = inp->in6p_faddr;
	}
#endif /* INET6 */
#if defined(INET6) && defined(INET)
	else
#endif
#ifdef INET
	{
		struct ip *ip;

		ip = (struct ip *)ip_ptr;
		ip->ip_v = IPVERSION;
		ip->ip_hl = 5;
		ip->ip_tos = inp->inp_ip_tos;
		ip->ip_len = 0;
		ip->ip_id = 0;
		ip->ip_off = 0;
		ip->ip_ttl = inp->inp_ip_ttl;
		ip->ip_sum = 0;
		ip->ip_p = IPPROTO_TCP;
		ip->ip_src = inp->inp_laddr;
		ip->ip_dst = inp->inp_faddr;
	}
#endif /* INET */
	th->th_sport = inp->inp_lport;
	th->th_dport = inp->inp_fport;
	th->th_seq = 0;
	th->th_ack = 0;
	th->th_x2 = 0;
	th->th_off = 5;
	th->th_flags = 0;
	th->th_win = 0;
	th->th_urp = 0;
	th->th_sum = 0;		/* in_pseudo() is called later for ipv4 */
}