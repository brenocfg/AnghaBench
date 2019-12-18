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
typedef  int /*<<< orphan*/ * caddr_t ;

/* Variables and functions */
#define  IFT_BRIDGE 132 
#define  IFT_ETHER 131 
#define  IFT_IEEE1394 130 
#define  IFT_INFINIBAND 129 
#define  IFT_L2VLAN 128 
 int /*<<< orphan*/ * IF_LLADDR (struct ifnet*) ; 

caddr_t
nd6_ifptomac(struct ifnet *ifp)
{
	switch (ifp->if_type) {
	case IFT_ETHER:
	case IFT_IEEE1394:
	case IFT_L2VLAN:
	case IFT_INFINIBAND:
	case IFT_BRIDGE:
		return IF_LLADDR(ifp);
	default:
		return NULL;
	}
}