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
struct ifaddrs {int ifa_flags; int /*<<< orphan*/  ifa_netmask; int /*<<< orphan*/  ifa_addr; int /*<<< orphan*/  ifa_name; struct ifaddrs* ifa_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Printf (char*,int /*<<< orphan*/ ) ; 
 int IFF_UP ; 
 int /*<<< orphan*/  NET_AddLocalAddress (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NET_ErrorString () ; 
 int /*<<< orphan*/  Sys_ShowIP () ; 
 int /*<<< orphan*/  freeifaddrs (struct ifaddrs*) ; 
 scalar_t__ getifaddrs (struct ifaddrs**) ; 
 scalar_t__ numIP ; 

__attribute__((used)) static void NET_GetLocalAddress(void)
{
	struct ifaddrs *ifap, *search;

	numIP = 0;

	if(getifaddrs(&ifap))
		Com_Printf("NET_GetLocalAddress: Unable to get list of network interfaces: %s\n", NET_ErrorString());
	else
	{
		for(search = ifap; search; search = search->ifa_next)
		{
			// Only add interfaces that are up.
			if(ifap->ifa_flags & IFF_UP)
				NET_AddLocalAddress(search->ifa_name, search->ifa_addr, search->ifa_netmask);
		}
	
		freeifaddrs(ifap);
		
		Sys_ShowIP();
	}
}