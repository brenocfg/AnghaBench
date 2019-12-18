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
struct sockaddr_dl {int dummy; } ;
struct ifreq {unsigned int ifr_index; int /*<<< orphan*/  ifr_name; } ;
struct ifaddrs {TYPE_1__* ifa_addr; int /*<<< orphan*/  ifa_name; struct ifaddrs* ifa_next; } ;
typedef  int /*<<< orphan*/  ifr ;
struct TYPE_2__ {scalar_t__ sa_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ AF_LINK ; 
 int /*<<< orphan*/  ENXIO ; 
 unsigned int LLINDEX (struct sockaddr_dl*) ; 
 int /*<<< orphan*/  SIOCGIFINDEX ; 
 int SOCK_CLOEXEC ; 
 int SOCK_DGRAM ; 
 int /*<<< orphan*/  _close (int) ; 
 int _ioctl (int,int /*<<< orphan*/ ,struct ifreq*) ; 
 int _socket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  freeifaddrs (struct ifaddrs*) ; 
 scalar_t__ getifaddrs (struct ifaddrs**) ; 
 int /*<<< orphan*/  memset (struct ifreq*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

unsigned int
if_nametoindex(const char *ifname)
{
	int s;
	struct ifreq ifr;
	struct ifaddrs *ifaddrs, *ifa;
	unsigned int ni;

	s = _socket(AF_INET, SOCK_DGRAM | SOCK_CLOEXEC, 0);
	if (s != -1) {
		memset(&ifr, 0, sizeof(ifr));
		strlcpy(ifr.ifr_name, ifname, sizeof(ifr.ifr_name));
		if (_ioctl(s, SIOCGIFINDEX, &ifr) != -1) {
			_close(s);
			return (ifr.ifr_index);
		}
		_close(s);
	}

	if (getifaddrs(&ifaddrs) < 0)
		return(0);

	ni = 0;

	for (ifa = ifaddrs; ifa != NULL; ifa = ifa->ifa_next) {
		if (ifa->ifa_addr &&
		    ifa->ifa_addr->sa_family == AF_LINK &&
		    strcmp(ifa->ifa_name, ifname) == 0) {
			ni = LLINDEX((struct sockaddr_dl*)ifa->ifa_addr);
			break;
		}
	}

	freeifaddrs(ifaddrs);
	if (!ni)
		errno = ENXIO;
	return(ni);
}