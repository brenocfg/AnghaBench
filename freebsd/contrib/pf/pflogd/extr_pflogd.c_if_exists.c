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
struct ifreq {scalar_t__ ifr_data; int /*<<< orphan*/  ifr_name; } ;
struct ifaddrs {char* ifa_name; struct ifaddrs* ifa_next; } ;
struct if_data {int dummy; } ;
typedef  int /*<<< orphan*/  ifr ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  SIOCGIFDATA ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  bzero (struct ifreq*,int) ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  freeifaddrs (struct ifaddrs*) ; 
 int /*<<< orphan*/  getifaddrs (struct ifaddrs**) ; 
 int ioctl (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,scalar_t__) ; 

int
if_exists(char *ifname)
{
#ifdef __FreeBSD__
	struct ifaddrs *ifdata, *mb;
	int exists = 0;

	getifaddrs(&ifdata);
        if (ifdata == NULL)
		return (0);

	for (mb = ifdata; mb != NULL; mb = mb->ifa_next) {
		if (mb == NULL)
			continue;
		if (strlen(ifname) != strlen(mb->ifa_name))
			continue;
		if (strncmp(ifname, mb->ifa_name, strlen(ifname)) != 0)
			continue;
		exists = 1;
		break;
	}
	freeifaddrs(ifdata);

	return (exists);
#else
	int s;
	struct ifreq ifr;
	struct if_data ifrdat;

	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		err(1, "socket");
	bzero(&ifr, sizeof(ifr));
	if (strlcpy(ifr.ifr_name, ifname, sizeof(ifr.ifr_name)) >=
		sizeof(ifr.ifr_name))
			errx(1, "main ifr_name: strlcpy");
	ifr.ifr_data = (caddr_t)&ifrdat;
	if (ioctl(s, SIOCGIFDATA, (caddr_t)&ifr) == -1)
		return (0);
	if (close(s))
		err(1, "close");

	return (1);
#endif
}