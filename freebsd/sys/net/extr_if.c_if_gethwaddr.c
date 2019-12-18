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
struct TYPE_2__ {int /*<<< orphan*/  sa_data; } ;
struct ifreq {TYPE_1__ ifr_addr; } ;
struct ifnet {int if_type; int /*<<< orphan*/  if_addrlen; int /*<<< orphan*/ * if_hw_addr; } ;

/* Variables and functions */
 int ENODEV ; 
#define  IFT_ETHER 129 
#define  IFT_IEEE8023ADLAG 128 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
if_gethwaddr(struct ifnet *ifp, struct ifreq *ifr)
{

	if (ifp->if_hw_addr == NULL)
		return (ENODEV);

	switch (ifp->if_type) {
	case IFT_ETHER:
	case IFT_IEEE8023ADLAG:
		bcopy(ifp->if_hw_addr, ifr->ifr_addr.sa_data, ifp->if_addrlen);
		return (0);
	default:
		return (ENODEV);
	}
}