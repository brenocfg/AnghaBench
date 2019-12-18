#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stf_softc {int dummy; } ;
struct mbuf {int dummy; } ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct ip {int ip_v; struct in_addr ip_src; int /*<<< orphan*/  ip_dst; } ;
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  mask ;
typedef  int /*<<< orphan*/  ip ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  a ;
struct TYPE_3__ {int if_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_V4 (struct in6_addr*) ; 
 int IFF_LINK0 ; 
 int IFF_UP ; 
 int IPPROTO_IPV6 ; 
 TYPE_1__* STF2IFP (struct stf_softc*) ; 
 scalar_t__ bcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,struct in_addr*,int) ; 
 int /*<<< orphan*/  bzero (struct in_addr*,int) ; 
 int /*<<< orphan*/  m_copydata (struct mbuf const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ stf_getsrcifa6 (TYPE_1__*,struct in6_addr*,struct in6_addr*) ; 

__attribute__((used)) static int
stf_encapcheck(const struct mbuf *m, int off, int proto, void *arg)
{
	struct ip ip;
	struct stf_softc *sc;
	struct in_addr a, b, mask;
	struct in6_addr addr6, mask6;

	sc = (struct stf_softc *)arg;
	if (sc == NULL)
		return 0;

	if ((STF2IFP(sc)->if_flags & IFF_UP) == 0)
		return 0;

	/* IFF_LINK0 means "no decapsulation" */
	if ((STF2IFP(sc)->if_flags & IFF_LINK0) != 0)
		return 0;

	if (proto != IPPROTO_IPV6)
		return 0;

	m_copydata(m, 0, sizeof(ip), (caddr_t)&ip);

	if (ip.ip_v != 4)
		return 0;

	if (stf_getsrcifa6(STF2IFP(sc), &addr6, &mask6) != 0)
		return (0);

	/*
	 * check if IPv4 dst matches the IPv4 address derived from the
	 * local 6to4 address.
	 * success on: dst = 10.1.1.1, ia6->ia_addr = 2002:0a01:0101:...
	 */
	if (bcmp(GET_V4(&addr6), &ip.ip_dst, sizeof(ip.ip_dst)) != 0)
		return 0;

	/*
	 * check if IPv4 src matches the IPv4 address derived from the
	 * local 6to4 address masked by prefixmask.
	 * success on: src = 10.1.1.1, ia6->ia_addr = 2002:0a00:.../24
	 * fail on: src = 10.1.1.1, ia6->ia_addr = 2002:0b00:.../24
	 */
	bzero(&a, sizeof(a));
	bcopy(GET_V4(&addr6), &a, sizeof(a));
	bcopy(GET_V4(&mask6), &mask, sizeof(mask));
	a.s_addr &= mask.s_addr;
	b = ip.ip_src;
	b.s_addr &= mask.s_addr;
	if (a.s_addr != b.s_addr)
		return 0;

	/* stf interface makes single side match only */
	return 32;
}