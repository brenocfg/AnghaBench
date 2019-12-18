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
struct ifreq {char* ifr_name; int ifr_mtu; } ;
struct glob_arg {char* ifname; } ;
typedef  int /*<<< orphan*/  ifreq ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  D (char*,int /*<<< orphan*/ ) ; 
 int IFNAMSIZ ; 
 int /*<<< orphan*/  SIOCGIFMTU ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  errno ; 
 int ioctl (int,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  memset (struct ifreq*,int /*<<< orphan*/ ,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strchr (char*,char) ; 
 size_t strcspn (char*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static int
get_if_mtu(const struct glob_arg *g)
{
	char ifname[IFNAMSIZ];
	struct ifreq ifreq;
	int s, ret;

	if (!strncmp(g->ifname, "netmap:", 7) && !strchr(g->ifname, '{')
			&& !strchr(g->ifname, '}')) {
		/* Parse the interface name and ask the kernel for the
		 * MTU value. */
		strncpy(ifname, g->ifname+7, IFNAMSIZ-1);
		ifname[strcspn(ifname, "-*^{}/@")] = '\0';

		s = socket(AF_INET, SOCK_DGRAM, 0);
		if (s < 0) {
			D("socket() failed: %s", strerror(errno));
			return s;
		}

		memset(&ifreq, 0, sizeof(ifreq));
		strncpy(ifreq.ifr_name, ifname, IFNAMSIZ);

		ret = ioctl(s, SIOCGIFMTU, &ifreq);
		if (ret) {
			D("ioctl(SIOCGIFMTU) failed: %s", strerror(errno));
		}

		return ifreq.ifr_mtu;
	}

	/* This is a pipe or a VALE port, where the MTU is very large,
	 * so we use some practical limit. */
	return 65536;
}