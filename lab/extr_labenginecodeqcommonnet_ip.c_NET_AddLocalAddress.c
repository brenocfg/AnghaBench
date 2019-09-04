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
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {scalar_t__ sa_family; } ;
typedef  scalar_t__ sa_family_t ;
struct TYPE_2__ {int /*<<< orphan*/  netmask; int /*<<< orphan*/  addr; scalar_t__ family; int /*<<< orphan*/  ifname; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 size_t MAX_IPS ; 
 int /*<<< orphan*/  NA_IP ; 
 int /*<<< orphan*/  NA_IP6 ; 
 int /*<<< orphan*/  Q_strncpyz (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__* localIP ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr*,int) ; 
 size_t numIP ; 

__attribute__((used)) static void NET_AddLocalAddress(char *ifname, struct sockaddr *addr, struct sockaddr *netmask)
{
	int addrlen;
	sa_family_t family;
	
	// only add addresses that have all required info.
	if(!addr || !netmask || !ifname)
		return;
	
	family = addr->sa_family;

	if(numIP < MAX_IPS)
	{
		if(family == AF_INET)
		{
			addrlen = sizeof(struct sockaddr_in);
			localIP[numIP].type = NA_IP;
		}
		else if(family == AF_INET6)
		{
			addrlen = sizeof(struct sockaddr_in6);
			localIP[numIP].type = NA_IP6;
		}
		else
			return;
		
		Q_strncpyz(localIP[numIP].ifname, ifname, sizeof(localIP[numIP].ifname));
	
		localIP[numIP].family = family;

		memcpy(&localIP[numIP].addr, addr, addrlen);
		memcpy(&localIP[numIP].netmask, netmask, addrlen);
		
		numIP++;
	}
}