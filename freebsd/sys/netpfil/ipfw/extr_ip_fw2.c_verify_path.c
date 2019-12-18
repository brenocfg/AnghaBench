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
typedef  int /*<<< orphan*/  u_int ;
struct nhop4_basic {int nh_flags; struct ifnet* nh_ifp; } ;
struct in_addr {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int NHF_BLACKHOLE ; 
 int NHF_DEFAULT ; 
 int NHF_REJECT ; 
 int /*<<< orphan*/  NHR_IFAIF ; 
 scalar_t__ fib4_lookup_nh_basic (int /*<<< orphan*/ ,struct in_addr,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nhop4_basic*) ; 

__attribute__((used)) static int
verify_path(struct in_addr src, struct ifnet *ifp, u_int fib)
{
#if defined(USERSPACE) || !defined(__FreeBSD__)
	return 0;
#else
	struct nhop4_basic nh4;

	if (fib4_lookup_nh_basic(fib, src, NHR_IFAIF, 0, &nh4) != 0)
		return (0);

	/*
	 * If ifp is provided, check for equality with rtentry.
	 * We should use rt->rt_ifa->ifa_ifp, instead of rt->rt_ifp,
	 * in order to pass packets injected back by if_simloop():
	 * routing entry (via lo0) for our own address
	 * may exist, so we need to handle routing assymetry.
	 */
	if (ifp != NULL && ifp != nh4.nh_ifp)
		return (0);

	/* if no ifp provided, check if rtentry is not default route */
	if (ifp == NULL && (nh4.nh_flags & NHF_DEFAULT) != 0)
		return (0);

	/* or if this is a blackhole/reject route */
	if (ifp == NULL && (nh4.nh_flags & (NHF_REJECT|NHF_BLACKHOLE)) != 0)
		return (0);

	/* found valid route */
	return 1;
#endif /* __FreeBSD__ */
}