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
struct nhop4_basic {int nh_flags; } ;
struct mbuf {int dummy; } ;
struct in_addr {int dummy; } ;

/* Variables and functions */
 int EHOSTUNREACH ; 
 int /*<<< orphan*/  ICMP_UNREACH ; 
 int /*<<< orphan*/  ICMP_UNREACH_HOST ; 
 int /*<<< orphan*/  IPSTAT_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_GETFIB (struct mbuf*) ; 
 int NHF_BLACKHOLE ; 
 int NHF_BROADCAST ; 
 int NHF_REJECT ; 
 int /*<<< orphan*/  bzero (struct nhop4_basic*,int) ; 
 scalar_t__ fib4_lookup_nh_basic (int /*<<< orphan*/ ,struct in_addr,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nhop4_basic*) ; 
 int /*<<< orphan*/  icmp_error (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ips_cantforward ; 
 int /*<<< orphan*/  ips_noroute ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static int
ip_findroute(struct nhop4_basic *pnh, struct in_addr dest, struct mbuf *m)
{

	bzero(pnh, sizeof(*pnh));
	if (fib4_lookup_nh_basic(M_GETFIB(m), dest, 0, 0, pnh) != 0) {
		IPSTAT_INC(ips_noroute);
		IPSTAT_INC(ips_cantforward);
		icmp_error(m, ICMP_UNREACH, ICMP_UNREACH_HOST, 0, 0);
		return (EHOSTUNREACH);
	}
	/*
	 * Drop blackholed traffic and directed broadcasts.
	 */
	if ((pnh->nh_flags & (NHF_BLACKHOLE | NHF_BROADCAST)) != 0) {
		IPSTAT_INC(ips_cantforward);
		m_freem(m);
		return (EHOSTUNREACH);
	}

	if (pnh->nh_flags & NHF_REJECT) {
		IPSTAT_INC(ips_cantforward);
		icmp_error(m, ICMP_UNREACH, ICMP_UNREACH_HOST, 0, 0);
		return (EHOSTUNREACH);
	}

	return (0);
}