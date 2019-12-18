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
typedef  int u_int ;
struct TYPE_2__ {int /*<<< orphan*/  rcvif; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct ip6ctlparam {struct mbuf* ip6c_m; struct icmp6_hdr* ip6c_icmp6; struct in6_addr* ip6c_finaldst; } ;
struct ip6_hdr {int dummy; } ;
struct ip6_frag {int dummy; } ;
struct in6_addr {int dummy; } ;
struct in_conninfo {struct in6_addr inc6_faddr; int /*<<< orphan*/  inc_flags; int /*<<< orphan*/  inc_fibnum; } ;
struct icmp6_hdr {int /*<<< orphan*/  icmp6_mtu; } ;
typedef  int /*<<< orphan*/  inc ;

/* Variables and functions */
 int /*<<< orphan*/  ICMP6STAT_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INC_ISIPV6 ; 
 int IPV6_MMTU ; 
 int /*<<< orphan*/  M_GETFIB (struct mbuf*) ; 
 int /*<<< orphan*/  bzero (struct in_conninfo*,int) ; 
 int /*<<< orphan*/  icp6s_pmtuchg ; 
 scalar_t__ in6_setscope (struct in6_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_hc_updatemtu (struct in_conninfo*,int) ; 
 int tcp_maxmtu6 (struct in_conninfo*,int /*<<< orphan*/ *) ; 

void
icmp6_mtudisc_update(struct ip6ctlparam *ip6cp, int validated)
{
	struct in6_addr *dst = ip6cp->ip6c_finaldst;
	struct icmp6_hdr *icmp6 = ip6cp->ip6c_icmp6;
	struct mbuf *m = ip6cp->ip6c_m;	/* will be necessary for scope issue */
	u_int mtu = ntohl(icmp6->icmp6_mtu);
	struct in_conninfo inc;

#if 0
	/*
	 * RFC2460 section 5, last paragraph.
	 * even though minimum link MTU for IPv6 is IPV6_MMTU,
	 * we may see ICMPv6 too big with mtu < IPV6_MMTU
	 * due to packet translator in the middle.
	 * see ip6_output() and ip6_getpmtu() "alwaysfrag" case for
	 * special handling.
	 */
	if (mtu < IPV6_MMTU)
		return;
#endif

	/*
	 * we reject ICMPv6 too big with abnormally small value.
	 * XXX what is the good definition of "abnormally small"?
	 */
	if (mtu < sizeof(struct ip6_hdr) + sizeof(struct ip6_frag) + 8)
		return;

	if (!validated)
		return;

	/*
	 * In case the suggested mtu is less than IPV6_MMTU, we
	 * only need to remember that it was for above mentioned
	 * "alwaysfrag" case.
	 * Try to be as close to the spec as possible.
	 */
	if (mtu < IPV6_MMTU)
		mtu = IPV6_MMTU - 8;

	bzero(&inc, sizeof(inc));
	inc.inc_fibnum = M_GETFIB(m);
	inc.inc_flags |= INC_ISIPV6;
	inc.inc6_faddr = *dst;
	if (in6_setscope(&inc.inc6_faddr, m->m_pkthdr.rcvif, NULL))
		return;

	if (mtu < tcp_maxmtu6(&inc, NULL)) {
		tcp_hc_updatemtu(&inc, mtu);
		ICMP6STAT_INC(icp6s_pmtuchg);
	}
}