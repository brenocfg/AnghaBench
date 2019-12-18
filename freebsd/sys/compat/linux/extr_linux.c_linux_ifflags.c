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
struct ifnet {int if_flags; int if_drv_flags; } ;

/* Variables and functions */
 unsigned short IFF_ALLMULTI ; 
 unsigned short IFF_BROADCAST ; 
 unsigned short IFF_DEBUG ; 
 unsigned short IFF_DRV_RUNNING ; 
 unsigned short IFF_LOOPBACK ; 
 unsigned short IFF_MULTICAST ; 
 unsigned short IFF_NOARP ; 
 unsigned short IFF_POINTOPOINT ; 
 unsigned short IFF_PROMISC ; 
 unsigned short IFF_UP ; 
 short LINUX_IFF_ALLMULTI ; 
 short LINUX_IFF_BROADCAST ; 
 short LINUX_IFF_DEBUG ; 
 short LINUX_IFF_LOOPBACK ; 
 short LINUX_IFF_MULTICAST ; 
 short LINUX_IFF_NOARP ; 
 short LINUX_IFF_POINTOPOINT ; 
 short LINUX_IFF_PROMISC ; 
 short LINUX_IFF_RUNNING ; 
 short LINUX_IFF_UP ; 

void
linux_ifflags(struct ifnet *ifp, short *flags)
{
	unsigned short fl;

	fl = (ifp->if_flags | ifp->if_drv_flags) & 0xffff;
	*flags = 0;
	if (fl & IFF_UP)
		*flags |= LINUX_IFF_UP;
	if (fl & IFF_BROADCAST)
		*flags |= LINUX_IFF_BROADCAST;
	if (fl & IFF_DEBUG)
		*flags |= LINUX_IFF_DEBUG;
	if (fl & IFF_LOOPBACK)
		*flags |= LINUX_IFF_LOOPBACK;
	if (fl & IFF_POINTOPOINT)
		*flags |= LINUX_IFF_POINTOPOINT;
	if (fl & IFF_DRV_RUNNING)
		*flags |= LINUX_IFF_RUNNING;
	if (fl & IFF_NOARP)
		*flags |= LINUX_IFF_NOARP;
	if (fl & IFF_PROMISC)
		*flags |= LINUX_IFF_PROMISC;
	if (fl & IFF_ALLMULTI)
		*flags |= LINUX_IFF_ALLMULTI;
	if (fl & IFF_MULTICAST)
		*flags |= LINUX_IFF_MULTICAST;
}