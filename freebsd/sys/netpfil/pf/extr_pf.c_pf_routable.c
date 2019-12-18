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
struct radix_node_head {int dummy; } ;
struct pfi_kif {struct ifnet* pfik_ifp; } ;
struct pf_addr {int /*<<< orphan*/  v4; int /*<<< orphan*/  v6; } ;
struct nhop6_basic {struct ifnet* nh_ifp; } ;
struct nhop4_basic {struct ifnet* nh_ifp; } ;
struct ifnet {scalar_t__ if_type; } ;
typedef  int sa_family_t ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 scalar_t__ IFT_ENC ; 
 scalar_t__ IN6_IS_SCOPE_EMBED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fib4_lookup_nh_basic (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nhop4_basic*) ; 
 int /*<<< orphan*/  fib6_lookup_nh_basic (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nhop6_basic*) ; 
 int pf_routable_oldmpath (struct pf_addr*,int,struct pfi_kif*,int) ; 
 scalar_t__ rn_mpath_capable (struct radix_node_head*) ; 
 struct radix_node_head* rt_tables_get_rnh (int /*<<< orphan*/ ,int) ; 

int
pf_routable(struct pf_addr *addr, sa_family_t af, struct pfi_kif *kif,
    int rtableid)
{
#ifdef INET
	struct nhop4_basic	nh4;
#endif
#ifdef INET6
	struct nhop6_basic	nh6;
#endif
	struct ifnet		*ifp;
#ifdef RADIX_MPATH
	struct radix_node_head	*rnh;

	/* XXX: stick to table 0 for now */
	rnh = rt_tables_get_rnh(0, af);
	if (rnh != NULL && rn_mpath_capable(rnh))
		return (pf_routable_oldmpath(addr, af, kif, rtableid));
#endif
	/*
	 * Skip check for addresses with embedded interface scope,
	 * as they would always match anyway.
	 */
	if (af == AF_INET6 && IN6_IS_SCOPE_EMBED(&addr->v6))
		return (1);

	if (af != AF_INET && af != AF_INET6)
		return (0);

	/* Skip checks for ipsec interfaces */
	if (kif != NULL && kif->pfik_ifp->if_type == IFT_ENC)
		return (1);

	ifp = NULL;

	switch (af) {
#ifdef INET6
	case AF_INET6:
		if (fib6_lookup_nh_basic(rtableid, &addr->v6, 0, 0, 0, &nh6)!=0)
			return (0);
		ifp = nh6.nh_ifp;
		break;
#endif
#ifdef INET
	case AF_INET:
		if (fib4_lookup_nh_basic(rtableid, addr->v4, 0, 0, &nh4) != 0)
			return (0);
		ifp = nh4.nh_ifp;
		break;
#endif
	}

	/* No interface given, this is a no-route check */
	if (kif == NULL)
		return (1);

	if (kif->pfik_ifp == NULL)
		return (0);

	/* Perform uRPF check if passed input interface */
	if (kif->pfik_ifp == ifp)
		return (1);
	return (0);
}