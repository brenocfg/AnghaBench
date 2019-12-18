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
struct TYPE_4__ {scalar_t__ s_addr; } ;
struct sockaddr_in {TYPE_2__ sin_addr; } ;
struct sockaddr_dl {int sdl_index; } ;
struct sockaddr {int dummy; } ;
struct rt_msghdr {scalar_t__ rtm_version; int rtm_flags; int rtm_index; int rtm_addrs; int /*<<< orphan*/  rtm_msglen; } ;
struct ifaddrs {TYPE_1__* ifa_addr; int /*<<< orphan*/  ifa_name; struct ifaddrs* ifa_next; } ;
struct TYPE_3__ {scalar_t__ sa_family; } ;

/* Variables and functions */
 int AF_INET ; 
 scalar_t__ AF_LINK ; 
 int CTL_NET ; 
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  EX_OSERR ; 
 scalar_t__ INADDR_ANY ; 
 int NET_RT_DUMP ; 
 int PF_ROUTE ; 
#define  RTAX_DST 130 
#define  RTAX_GATEWAY 129 
 int RTAX_MAX ; 
#define  RTAX_NETMASK 128 
 int RTF_GATEWAY ; 
 scalar_t__ RTM_VERSION ; 
 int SA_SIZE (struct sockaddr*) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  freeifaddrs (struct ifaddrs*) ; 
 scalar_t__ getifaddrs (struct ifaddrs**) ; 
 char* inet_ntoa (TYPE_2__) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  nitems (int*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int sysctl (int*,int /*<<< orphan*/ ,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
find_gateway(const char *ifname)
{
	struct ifaddrs *ifa, *ifap;
	struct rt_msghdr *rtm;
	struct sockaddr *sa;
	struct sockaddr_dl *sdl;
	struct sockaddr_in *dst, *mask, *gw;
	char *buf, *next, *ret;
	size_t sz;
	int error, i, ifindex, mib[7];

	/* First look up the interface index. */
	if (getifaddrs(&ifap) != 0)
		err(EX_OSERR, "getifaddrs");
	for (ifa = ifap; ifa != NULL; ifa = ifa->ifa_next) {
		if (ifa->ifa_addr->sa_family != AF_LINK)
			continue;
		if (strcmp(ifa->ifa_name, ifname) == 0) {
			sdl = (struct sockaddr_dl *)(void *)ifa->ifa_addr;
			ifindex = sdl->sdl_index;
			break;
		}
	}
	if (ifa == NULL)
		errx(1, "couldn't find interface index for '%s'", ifname);
	freeifaddrs(ifap);

	/* Now get the IPv4 routing table. */
	mib[0] = CTL_NET;
	mib[1] = PF_ROUTE;
	mib[2] = 0;
	mib[3] = AF_INET;
	mib[4] = NET_RT_DUMP;
	mib[5] = 0;
	mib[6] = -1; /* FIB */

	for (;;) {
		if (sysctl(mib, nitems(mib), NULL, &sz, NULL, 0) != 0)
			err(EX_OSERR, "sysctl(NET_RT_DUMP)");
		buf = malloc(sz);
		error = sysctl(mib, nitems(mib), buf, &sz, NULL, 0);
		if (error == 0)
			break;
		if (errno != ENOMEM)
			err(EX_OSERR, "sysctl(NET_RT_DUMP)");
		free(buf);
	}

	ret = NULL;
	for (next = buf; next < buf + sz; next += rtm->rtm_msglen) {
		rtm = (struct rt_msghdr *)(void *)next;
		if (rtm->rtm_version != RTM_VERSION)
			continue;
		if ((rtm->rtm_flags & RTF_GATEWAY) == 0 ||
		    rtm->rtm_index != ifindex)
			continue;

		dst = gw = mask = NULL;
		sa = (struct sockaddr *)(rtm + 1);
		for (i = 0; i < RTAX_MAX; i++) {
			if ((rtm->rtm_addrs & (1 << i)) != 0) {
				switch (i) {
				case RTAX_DST:
					dst = (void *)sa;
					break;
				case RTAX_GATEWAY:
					gw = (void *)sa;
					break;
				case RTAX_NETMASK:
					mask = (void *)sa;
					break;
				}
			}
			sa = (struct sockaddr *)((char *)sa + SA_SIZE(sa));
		}

		if (dst->sin_addr.s_addr == INADDR_ANY &&
		    mask->sin_addr.s_addr == 0) {
			ret = inet_ntoa(gw->sin_addr);
			break;
		}
	}
	free(buf);
	return (ret);
}