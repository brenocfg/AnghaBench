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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_flowinfo; int /*<<< orphan*/  sin6_scope_id; int /*<<< orphan*/  sin6_addr; } ;
struct nhop6_basic {int nh_flags; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int EHOSTUNREACH ; 
 int /*<<< orphan*/  ICMP6_DST_UNREACH ; 
 int /*<<< orphan*/  ICMP6_DST_UNREACH_NOROUTE ; 
 int /*<<< orphan*/  ICMP6_DST_UNREACH_REJECT ; 
 int /*<<< orphan*/  IP6STAT_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_GETFIB (struct mbuf*) ; 
 int NHF_BLACKHOLE ; 
 int NHF_REJECT ; 
 scalar_t__ fib6_lookup_nh_basic (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nhop6_basic*) ; 
 int /*<<< orphan*/  icmp6_error (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6s_cantforward ; 
 int /*<<< orphan*/  ip6s_noroute ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static int
ip6_findroute(struct nhop6_basic *pnh, const struct sockaddr_in6 *dst,
    struct mbuf *m)
{

	if (fib6_lookup_nh_basic(M_GETFIB(m), &dst->sin6_addr,
	    dst->sin6_scope_id, 0, dst->sin6_flowinfo, pnh) != 0) {
		IP6STAT_INC(ip6s_noroute);
		IP6STAT_INC(ip6s_cantforward);
		icmp6_error(m, ICMP6_DST_UNREACH,
		    ICMP6_DST_UNREACH_NOROUTE, 0);
		return (EHOSTUNREACH);
	}
	if (pnh->nh_flags & NHF_BLACKHOLE) {
		IP6STAT_INC(ip6s_cantforward);
		m_freem(m);
		return (EHOSTUNREACH);
	}

	if (pnh->nh_flags & NHF_REJECT) {
		IP6STAT_INC(ip6s_cantforward);
		icmp6_error(m, ICMP6_DST_UNREACH,
		    ICMP6_DST_UNREACH_REJECT, 0);
		return (EHOSTUNREACH);
	}
	return (0);
}