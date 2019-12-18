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
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr_dl {scalar_t__ sdl_nlen; int /*<<< orphan*/  sdl_data; } ;
struct sockaddr {int sa_family; } ;
struct ifa_msghdr {scalar_t__ ifam_version; scalar_t__ ifam_type; int ifam_addrs; int /*<<< orphan*/  ifam_msglen; } ;
struct TYPE_3__ {int /*<<< orphan*/  ifi_mtu; } ;
struct if_msghdr {scalar_t__ ifm_version; scalar_t__ ifm_type; TYPE_1__ ifm_data; scalar_t__ ifm_index; int /*<<< orphan*/  ifm_msglen; } ;
struct TYPE_4__ {int /*<<< orphan*/  ifMTU; scalar_t__ ifIndex; } ;

/* Variables and functions */
 int AF_INET ; 
 int CTL_NET ; 
 int EAGAIN ; 
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  LibAliasSetAddress (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NET_RT_IFLIST ; 
 int PF_ROUTE ; 
 int RTA_IFA ; 
 scalar_t__ RTM_IFINFO ; 
 scalar_t__ RTM_NEWADDR ; 
 scalar_t__ RTM_VERSION ; 
 int /*<<< orphan*/  SA_SIZE (struct sockaddr*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  inet_ntoa (int /*<<< orphan*/ ) ; 
 char* malloc (size_t) ; 
 TYPE_2__* mip ; 
 int /*<<< orphan*/  mla ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,scalar_t__) ; 
 int sysctl (int*,int,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ verbose ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

__attribute__((used)) static int
SetAliasAddressFromIfName(const char *ifn)
{
	size_t needed;
	int mib[6];
	char *buf, *lim, *next;
	struct if_msghdr *ifm;
	struct ifa_msghdr *ifam;
	struct sockaddr_dl *sdl;
	struct sockaddr_in *sin;

	mib[0] = CTL_NET;
	mib[1] = PF_ROUTE;
	mib[2] = 0;
	mib[3] = AF_INET;	/* Only IP addresses please */
	mib[4] = NET_RT_IFLIST;
	mib[5] = 0;		/* ifIndex??? */
/*
 * Get interface data.
 */
	if (sysctl(mib, 6, NULL, &needed, NULL, 0) == -1)
		err(1, "iflist-sysctl-estimate");
	if ((buf = malloc(needed)) == NULL)
		errx(1, "malloc failed");
	if (sysctl(mib, 6, buf, &needed, NULL, 0) == -1 && errno != ENOMEM)
		err(1, "iflist-sysctl-get");
	lim = buf + needed;
/*
 * Loop through interfaces until one with
 * given name is found. This is done to
 * find correct interface index for routing
 * message processing.
 */
	mip->ifIndex	= 0;
	next = buf;
	while (next < lim) {
		ifm = (struct if_msghdr *)next;
		next += ifm->ifm_msglen;
		if (ifm->ifm_version != RTM_VERSION) {
			if (verbose)
				warnx("routing message version %d "
				      "not understood", ifm->ifm_version);
			continue;
		}
		if (ifm->ifm_type == RTM_IFINFO) {
			sdl = (struct sockaddr_dl *)(ifm + 1);
			if (strlen(ifn) == sdl->sdl_nlen &&
			    strncmp(ifn, sdl->sdl_data, sdl->sdl_nlen) == 0) {
				mip->ifIndex = ifm->ifm_index;
				mip->ifMTU = ifm->ifm_data.ifi_mtu;
				break;
			}
		}
	}
	if (!mip->ifIndex)
		errx(1, "unknown interface name %s", ifn);
/*
 * Get interface address.
 */
	sin = NULL;
	while (next < lim) {
		ifam = (struct ifa_msghdr *)next;
		next += ifam->ifam_msglen;
		if (ifam->ifam_version != RTM_VERSION) {
			if (verbose)
				warnx("routing message version %d "
				      "not understood", ifam->ifam_version);
			continue;
		}
		if (ifam->ifam_type != RTM_NEWADDR)
			break;
		if (ifam->ifam_addrs & RTA_IFA) {
			int i;
			char *cp = (char *)(ifam + 1);

			for (i = 1; i < RTA_IFA; i <<= 1)
				if (ifam->ifam_addrs & i)
					cp += SA_SIZE((struct sockaddr *)cp);
			if (((struct sockaddr *)cp)->sa_family == AF_INET) {
				sin = (struct sockaddr_in *)cp;
				break;
			}
		}
	}
	if (sin == NULL) {
		warnx("%s: cannot get interface address", ifn);
		free(buf);
		return EAGAIN;
	}

	LibAliasSetAddress(mla, sin->sin_addr);
	syslog(LOG_INFO, "Aliasing to %s, mtu %d bytes",
	       inet_ntoa(sin->sin_addr), mip->ifMTU);

	free(buf);

	return 0;
}