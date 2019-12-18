#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct ifaddrs {char* ifa_name; scalar_t__ ifa_addr; struct ifaddrs* ifa_next; } ;
struct TYPE_7__ {scalar_t__ ss_family; } ;
struct TYPE_5__ {scalar_t__ s_addr; } ;
struct TYPE_6__ {TYPE_1__ sin_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  sdl; TYPE_3__ ss; TYPE_2__ sin; } ;
typedef  TYPE_4__ sockunion_t ;
typedef  scalar_t__ in_addr_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_LINK ; 
 int LLINDEX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  freeifaddrs (struct ifaddrs*) ; 
 scalar_t__ getifaddrs (struct ifaddrs**) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static uint32_t
__inaddr_to_index(in_addr_t ifaddr)
{
	struct ifaddrs	*ifa;
	struct ifaddrs	*ifaddrs;
	char		*ifname;
	int		 ifindex;
	sockunion_t	*psu;

	if (getifaddrs(&ifaddrs) < 0)
		return (0);

	ifindex = 0;
	ifname = NULL;

	/*
	 * Pass #1: Find the ifaddr entry corresponding to the
	 * supplied IPv4 address. We should really use the ifindex
	 * consistently for matches, however it is not available to
	 * us on this pass.
	 */
	for (ifa = ifaddrs; ifa != NULL; ifa = ifa->ifa_next) {
		psu = (sockunion_t *)ifa->ifa_addr;
		if (psu && psu->ss.ss_family == AF_INET &&
		    psu->sin.sin_addr.s_addr == ifaddr) {
			ifname = ifa->ifa_name;
			break;
		}
	}
	if (ifname == NULL)
		goto out;

	/*
	 * Pass #2: Find the index of the interface matching the name
	 * we obtained from looking up the IPv4 ifaddr in pass #1.
	 * There must be a better way of doing this.
	 */
	for (ifa = ifaddrs; ifa != NULL; ifa = ifa->ifa_next) {
		psu = (sockunion_t *)ifa->ifa_addr;
		if (psu && psu->ss.ss_family == AF_LINK &&
		    strcmp(ifa->ifa_name, ifname) == 0) {
			ifindex = LLINDEX(&psu->sdl);
			break;
		}
	}
	assert(ifindex != 0);

out:
	freeifaddrs(ifaddrs);
	return (ifindex);
}