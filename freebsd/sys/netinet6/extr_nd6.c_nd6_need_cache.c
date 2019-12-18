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
struct ifnet {int if_type; } ;

/* Variables and functions */
#define  IFT_BRIDGE 133 
#define  IFT_ETHER 132 
#define  IFT_IEEE1394 131 
#define  IFT_INFINIBAND 130 
#define  IFT_L2VLAN 129 
#define  IFT_PROPVIRTUAL 128 

__attribute__((used)) static int
nd6_need_cache(struct ifnet *ifp)
{
	/*
	 * XXX: we currently do not make neighbor cache on any interface
	 * other than Ethernet and GIF.
	 *
	 * RFC2893 says:
	 * - unidirectional tunnels needs no ND
	 */
	switch (ifp->if_type) {
	case IFT_ETHER:
	case IFT_IEEE1394:
	case IFT_L2VLAN:
	case IFT_INFINIBAND:
	case IFT_BRIDGE:
	case IFT_PROPVIRTUAL:
		return (1);
	default:
		return (0);
	}
}