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
typedef  int u_long ;
struct ifreq {int ifr_mtu; int /*<<< orphan*/  ifr_name; } ;
typedef  int /*<<< orphan*/  ifr ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIOCGIFMTU ; 
 int /*<<< orphan*/  bzero (struct ifreq*,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int get_query_socket () ; 
 int ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

u_long
getifmtu(char *ifname)
{
	int		s;
	struct ifreq	ifr;

	s = get_query_socket();
	bzero(&ifr, sizeof(ifr));
	if (strlcpy(ifr.ifr_name, ifname, sizeof(ifr.ifr_name)) >=
	    sizeof(ifr.ifr_name))
		errx(1, "getifmtu: strlcpy");
	if (ioctl(s, SIOCGIFMTU, (caddr_t)&ifr) == -1)
#ifdef __FreeBSD__
		ifr.ifr_mtu = 1500;
#else
		err(1, "SIOCGIFMTU");
#endif
	if (ifr.ifr_mtu > 0)
		return (ifr.ifr_mtu);
	else {
		warnx("could not get mtu for %s, assuming 1500", ifname);
		return (1500);
	}
}