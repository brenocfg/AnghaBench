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
typedef  int uint64_t ;
struct tuntap_softc {int dummy; } ;
struct ifnet {int if_capenable; int if_hwassist; scalar_t__ if_softc; } ;

/* Variables and functions */
 int CSUM_IP6_TSO ; 
 int CSUM_IP_TSO ; 
 int CSUM_TCP ; 
 int CSUM_TCP_IPV6 ; 
 int CSUM_UDP ; 
 int CSUM_UDP_IPV6 ; 
 int IFCAP_TSO4 ; 
 int IFCAP_TSO6 ; 
 int IFCAP_TXCSUM ; 
 int IFCAP_TXCSUM_IPV6 ; 
 int /*<<< orphan*/  TUN_LOCK_ASSERT (struct tuntap_softc*) ; 

__attribute__((used)) static void
tun_caps_changed(struct ifnet *ifp)
{
	uint64_t hwassist = 0;

	TUN_LOCK_ASSERT((struct tuntap_softc *)ifp->if_softc);
	if (ifp->if_capenable & IFCAP_TXCSUM)
		hwassist |= CSUM_TCP | CSUM_UDP;
	if (ifp->if_capenable & IFCAP_TXCSUM_IPV6)
		hwassist |= CSUM_TCP_IPV6
		    | CSUM_UDP_IPV6;
	if (ifp->if_capenable & IFCAP_TSO4)
		hwassist |= CSUM_IP_TSO;
	if (ifp->if_capenable & IFCAP_TSO6)
		hwassist |= CSUM_IP6_TSO;
	ifp->if_hwassist = hwassist;
}