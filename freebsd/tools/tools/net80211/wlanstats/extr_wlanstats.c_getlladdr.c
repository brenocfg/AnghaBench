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
struct TYPE_3__ {int /*<<< orphan*/  ifr_name; } ;
struct wlanstatfoo_p {int /*<<< orphan*/  mac; TYPE_1__ ifr; } ;
struct sockaddr_dl {int dummy; } ;
struct ifaddrs {TYPE_2__* ifa_addr; int /*<<< orphan*/  ifa_name; struct ifaddrs* ifa_next; } ;
struct TYPE_4__ {scalar_t__ sa_family; } ;

/* Variables and functions */
 scalar_t__ AF_LINK ; 
 int /*<<< orphan*/  IEEE80211_ADDR_COPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLADDR (struct sockaddr_dl const*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeifaddrs (struct ifaddrs*) ; 
 scalar_t__ getifaddrs (struct ifaddrs**) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
getlladdr(struct wlanstatfoo_p *wf)
{
	const struct sockaddr_dl *sdl;
	struct ifaddrs *ifp, *p;

	if (getifaddrs(&ifp) != 0)
		err(1, "getifaddrs");
	for (p = ifp; p != NULL; p = p->ifa_next)
		if (strcmp(p->ifa_name, wf->ifr.ifr_name) == 0 &&
		    p->ifa_addr->sa_family == AF_LINK)
			break;
	if (p == NULL)
		errx(1, "did not find link layer address for interface %s",
			wf->ifr.ifr_name);
	sdl = (const struct sockaddr_dl *) p->ifa_addr;
	IEEE80211_ADDR_COPY(wf->mac, LLADDR(sdl));
	freeifaddrs(ifp);
}