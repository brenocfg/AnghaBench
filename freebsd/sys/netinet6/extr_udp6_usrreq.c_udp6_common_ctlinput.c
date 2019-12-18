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
typedef  int /*<<< orphan*/  uh ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct udphdr {int /*<<< orphan*/  uh_sport; int /*<<< orphan*/  uh_dport; } ;
struct udpcb {int /*<<< orphan*/  u_tun_ctx; int /*<<< orphan*/  (* u_icmp_func ) (int,struct sockaddr const*,void*,int /*<<< orphan*/ ) ;} ;
struct sockaddr_in6 {int dummy; } ;
typedef  struct sockaddr {scalar_t__ sa_family; int sa_len; } const sockaddr ;
struct TYPE_2__ {int len; int /*<<< orphan*/  rcvif; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct ip6ctlparam {int ip6c_off; struct sockaddr_in6* ip6c_src; void* ip6c_cmdarg; struct ip6_hdr* ip6c_ip6; struct mbuf* ip6c_m; } ;
struct ip6_hdr {int /*<<< orphan*/  ip6_src; int /*<<< orphan*/  ip6_dst; } ;
struct inpcbinfo {int dummy; } ;
struct inpcb {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int INPLOOKUP_RLOCKPCB ; 
 int INPLOOKUP_WILDCARD ; 
 int /*<<< orphan*/  INP_RUNLOCK (struct inpcb*) ; 
 int PRC_HOSTDEAD ; 
 scalar_t__ PRC_IS_REDIRECT (int) ; 
 unsigned int PRC_NCMDS ; 
 int /*<<< orphan*/  bzero (struct udphdr*,int) ; 
 struct inpcb* in6_pcblookup_mbuf (struct inpcbinfo*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  in6_pcbnotify (struct inpcbinfo*,struct sockaddr const*,int /*<<< orphan*/ ,struct sockaddr const*,int /*<<< orphan*/ ,int,void*,struct inpcb* (*) (struct inpcb*,int)) ; 
 struct inpcb* in6_rtchange (struct inpcb*,int) ; 
 scalar_t__* inet6ctlerrmap ; 
 struct udpcb* intoudpcb (struct inpcb*) ; 
 int /*<<< orphan*/  m_copydata (struct mbuf*,int,int,int /*<<< orphan*/ ) ; 
 struct sockaddr_in6 sa6_any ; 
 int /*<<< orphan*/  stub1 (int,struct sockaddr const*,void*,int /*<<< orphan*/ ) ; 
 struct inpcb* udp_notify (struct inpcb*,int) ; 

__attribute__((used)) static void
udp6_common_ctlinput(int cmd, struct sockaddr *sa, void *d,
    struct inpcbinfo *pcbinfo)
{
	struct udphdr uh;
	struct ip6_hdr *ip6;
	struct mbuf *m;
	int off = 0;
	struct ip6ctlparam *ip6cp = NULL;
	const struct sockaddr_in6 *sa6_src = NULL;
	void *cmdarg;
	struct inpcb *(*notify)(struct inpcb *, int) = udp_notify;
	struct udp_portonly {
		u_int16_t uh_sport;
		u_int16_t uh_dport;
	} *uhp;

	if (sa->sa_family != AF_INET6 ||
	    sa->sa_len != sizeof(struct sockaddr_in6))
		return;

	if ((unsigned)cmd >= PRC_NCMDS)
		return;
	if (PRC_IS_REDIRECT(cmd))
		notify = in6_rtchange, d = NULL;
	else if (cmd == PRC_HOSTDEAD)
		d = NULL;
	else if (inet6ctlerrmap[cmd] == 0)
		return;

	/* if the parameter is from icmp6, decode it. */
	if (d != NULL) {
		ip6cp = (struct ip6ctlparam *)d;
		m = ip6cp->ip6c_m;
		ip6 = ip6cp->ip6c_ip6;
		off = ip6cp->ip6c_off;
		cmdarg = ip6cp->ip6c_cmdarg;
		sa6_src = ip6cp->ip6c_src;
	} else {
		m = NULL;
		ip6 = NULL;
		cmdarg = NULL;
		sa6_src = &sa6_any;
	}

	if (ip6) {
		/*
		 * XXX: We assume that when IPV6 is non NULL,
		 * M and OFF are valid.
		 */

		/* Check if we can safely examine src and dst ports. */
		if (m->m_pkthdr.len < off + sizeof(*uhp))
			return;

		bzero(&uh, sizeof(uh));
		m_copydata(m, off, sizeof(*uhp), (caddr_t)&uh);

		if (!PRC_IS_REDIRECT(cmd)) {
			/* Check to see if its tunneled */
			struct inpcb *inp;
			inp = in6_pcblookup_mbuf(pcbinfo, &ip6->ip6_dst,
			    uh.uh_dport, &ip6->ip6_src, uh.uh_sport,
			    INPLOOKUP_WILDCARD | INPLOOKUP_RLOCKPCB,
			    m->m_pkthdr.rcvif, m);
			if (inp != NULL) {
				struct udpcb *up;
				
				up = intoudpcb(inp);
				if (up->u_icmp_func) {
					/* Yes it is. */
					INP_RUNLOCK(inp);
					(*up->u_icmp_func)(cmd, (struct sockaddr *)ip6cp->ip6c_src,
					      d, up->u_tun_ctx);
					return;
				} else {
					/* Can't find it. */
					INP_RUNLOCK(inp);
				}
			}
		}
		(void)in6_pcbnotify(pcbinfo, sa, uh.uh_dport,
		    (struct sockaddr *)ip6cp->ip6c_src, uh.uh_sport, cmd,
		    cmdarg, notify);
	} else
		(void)in6_pcbnotify(pcbinfo, sa, 0,
		    (const struct sockaddr *)sa6_src, 0, cmd, cmdarg, notify);
}