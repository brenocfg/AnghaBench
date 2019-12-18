#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct in6_addr {int dummy; } ;
struct TYPE_3__ {struct in6_addr sin6_addr; } ;
struct in6_ifaddr {TYPE_1__ ia_addr; int /*<<< orphan*/  ia6_flags; } ;
struct ifnet {int if_type; } ;
struct ifaddr {struct ifnet* ifa_ifp; } ;
struct dadq {int /*<<< orphan*/  dad_na_icount; int /*<<< orphan*/  dad_ns_lcount; int /*<<< orphan*/  dad_ns_ocount; int /*<<< orphan*/  dad_ns_icount; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
#define  IFT_ATM 131 
#define  IFT_ETHER 130 
#define  IFT_IEEE1394 129 
#define  IFT_INFINIBAND 128 
 int /*<<< orphan*/  IN6_ARE_ADDR_EQUAL (struct in6_addr*,struct in6_addr*) ; 
 int /*<<< orphan*/  IN6_IFF_DUPLICATED ; 
 int /*<<< orphan*/  IN6_IFF_TENTATIVE ; 
 scalar_t__ IN6_IS_ADDR_LINKLOCAL (struct in6_addr*) ; 
 int INET6_ADDRSTRLEN ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  ND6_IFF_IFDISABLED ; 
 TYPE_2__* ND_IFINFO (struct ifnet*) ; 
 int /*<<< orphan*/  if_name (struct ifnet*) ; 
 int /*<<< orphan*/  in6_get_hw_ifid (struct ifnet*,struct in6_addr*) ; 
 int /*<<< orphan*/  ip6_sprintf (char*,struct in6_addr*) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
nd6_dad_duplicated(struct ifaddr *ifa, struct dadq *dp)
{
	struct in6_ifaddr *ia = (struct in6_ifaddr *)ifa;
	struct ifnet *ifp;
	char ip6buf[INET6_ADDRSTRLEN];

	log(LOG_ERR, "%s: DAD detected duplicate IPv6 address %s: "
	    "NS in/out/loopback=%d/%d/%d, NA in=%d\n",
	    if_name(ifa->ifa_ifp), ip6_sprintf(ip6buf, &ia->ia_addr.sin6_addr),
	    dp->dad_ns_icount, dp->dad_ns_ocount, dp->dad_ns_lcount,
	    dp->dad_na_icount);

	ia->ia6_flags &= ~IN6_IFF_TENTATIVE;
	ia->ia6_flags |= IN6_IFF_DUPLICATED;

	ifp = ifa->ifa_ifp;
	log(LOG_ERR, "%s: DAD complete for %s - duplicate found\n",
	    if_name(ifp), ip6_sprintf(ip6buf, &ia->ia_addr.sin6_addr));
	log(LOG_ERR, "%s: manual intervention required\n",
	    if_name(ifp));

	/*
	 * If the address is a link-local address formed from an interface
	 * identifier based on the hardware address which is supposed to be
	 * uniquely assigned (e.g., EUI-64 for an Ethernet interface), IP
	 * operation on the interface SHOULD be disabled.
	 * [RFC 4862, Section 5.4.5]
	 */
	if (IN6_IS_ADDR_LINKLOCAL(&ia->ia_addr.sin6_addr)) {
		struct in6_addr in6;

		/*
		 * To avoid over-reaction, we only apply this logic when we are
		 * very sure that hardware addresses are supposed to be unique.
		 */
		switch (ifp->if_type) {
		case IFT_ETHER:
		case IFT_ATM:
		case IFT_IEEE1394:
		case IFT_INFINIBAND:
			in6 = ia->ia_addr.sin6_addr;
			if (in6_get_hw_ifid(ifp, &in6) == 0 &&
			    IN6_ARE_ADDR_EQUAL(&ia->ia_addr.sin6_addr, &in6)) {
				ND_IFINFO(ifp)->flags |= ND6_IFF_IFDISABLED;
				log(LOG_ERR, "%s: possible hardware address "
				    "duplication detected, disable IPv6\n",
				    if_name(ifp));
			}
			break;
		}
	}
}