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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_len; int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_4__ {int ifru_flags6; int /*<<< orphan*/  ifru_addr; } ;
struct in6_ifreq {TYPE_2__ ifr_ifru; int /*<<< orphan*/  ifr_name; } ;
struct ifaddrs {TYPE_1__* ifa_addr; int /*<<< orphan*/  ifa_name; struct ifaddrs* ifa_next; } ;
typedef  int /*<<< orphan*/  ifr6 ;
struct TYPE_3__ {scalar_t__ sa_family; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  IN6_IS_ADDR_LINKLOCAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int /*<<< orphan*/  SIOCGIFAFLAG_IN6 ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  freeifaddrs (struct ifaddrs*) ; 
 scalar_t__ getifaddrs (struct ifaddrs**) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct in6_ifreq*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr_in6*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct in6_ifreq*,int /*<<< orphan*/ ,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static int
llflags_get(const char *ifname, int *flagsp)
{
	struct in6_ifreq ifr6;
	struct ifaddrs *ifap, *ifa;
	struct sockaddr_in6 *sin6;
	int error, s;

	s = socket(PF_INET6, SOCK_DGRAM, 0);
	if (s < 0)
		return (-1);

	if (getifaddrs(&ifap) != 0)
		return (-1);
	error = -1;
	for (ifa = ifap; ifa != NULL; ifa = ifa->ifa_next) {
		if (strcmp(ifa->ifa_name, ifname) != 0)
			continue;
		if (ifa->ifa_addr->sa_family != AF_INET6)
			continue;

		sin6 = (struct sockaddr_in6 *)(void *)ifa->ifa_addr;
		if (!IN6_IS_ADDR_LINKLOCAL(&sin6->sin6_addr))
			continue;

		memset(&ifr6, 0, sizeof(ifr6));
		if (strlcpy(ifr6.ifr_name, ifname, sizeof(ifr6.ifr_name)) >=
		    sizeof(ifr6.ifr_name)) {
			freeifaddrs(ifap);
			errno = EINVAL;
			return (-1);
		}
		memcpy(&ifr6.ifr_ifru.ifru_addr, sin6, sin6->sin6_len);
		if (ioctl(s, SIOCGIFAFLAG_IN6, &ifr6) < 0) {
			error = errno;
			freeifaddrs(ifap);
			errno = error;
			return (-1);
		}

		*flagsp = ifr6.ifr_ifru.ifru_flags6;
		error = 0;
		break;
	}
	(void)close(s);
	freeifaddrs(ifap);
	if (error == -1)
		errno = ENOENT;
	return (error);
}