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
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct sockaddr_dl {scalar_t__ sdl_nlen; int /*<<< orphan*/  sdl_data; } ;
struct sockaddr {int sa_family; } ;
struct nat44_cfg_nat {int /*<<< orphan*/  if_name; TYPE_1__ ip; } ;
struct ifa_msghdr {scalar_t__ ifam_version; scalar_t__ ifam_type; int ifam_addrs; int /*<<< orphan*/  ifam_msglen; } ;
struct if_msghdr {scalar_t__ ifm_version; scalar_t__ ifm_type; int ifm_index; int /*<<< orphan*/  ifm_msglen; } ;
struct TYPE_4__ {scalar_t__ verbose; } ;

/* Variables and functions */
 int AF_INET ; 
 int CTL_NET ; 
 int /*<<< orphan*/  IF_NAMESIZE ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int NET_RT_IFLIST ; 
 int PF_ROUTE ; 
 int RTA_IFA ; 
 scalar_t__ RTM_IFINFO ; 
 scalar_t__ RTM_NEWADDR ; 
 scalar_t__ RTM_VERSION ; 
 int /*<<< orphan*/  SA_SIZE (struct sockaddr*) ; 
 TYPE_2__ co ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 char* safe_calloc (int,size_t) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int sysctl (int*,int,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,scalar_t__) ; 

__attribute__((used)) static void
set_addr_dynamic(const char *ifn, struct nat44_cfg_nat *n)
{
	size_t needed;
	int mib[6];
	char *buf, *lim, *next;
	struct if_msghdr *ifm;
	struct ifa_msghdr *ifam;
	struct sockaddr_dl *sdl;
	struct sockaddr_in *sin;
	int ifIndex;

	mib[0] = CTL_NET;
	mib[1] = PF_ROUTE;
	mib[2] = 0;
	mib[3] = AF_INET;
	mib[4] = NET_RT_IFLIST;
	mib[5] = 0;
/*
 * Get interface data.
 */
	if (sysctl(mib, 6, NULL, &needed, NULL, 0) == -1)
		err(1, "iflist-sysctl-estimate");
	buf = safe_calloc(1, needed);
	if (sysctl(mib, 6, buf, &needed, NULL, 0) == -1)
		err(1, "iflist-sysctl-get");
	lim = buf + needed;
/*
 * Loop through interfaces until one with
 * given name is found. This is done to
 * find correct interface index for routing
 * message processing.
 */
	ifIndex	= 0;
	next = buf;
	while (next < lim) {
		ifm = (struct if_msghdr *)next;
		next += ifm->ifm_msglen;
		if (ifm->ifm_version != RTM_VERSION) {
			if (co.verbose)
				warnx("routing message version %d "
				    "not understood", ifm->ifm_version);
			continue;
		}
		if (ifm->ifm_type == RTM_IFINFO) {
			sdl = (struct sockaddr_dl *)(ifm + 1);
			if (strlen(ifn) == sdl->sdl_nlen &&
			    strncmp(ifn, sdl->sdl_data, sdl->sdl_nlen) == 0) {
				ifIndex = ifm->ifm_index;
				break;
			}
		}
	}
	if (!ifIndex)
		errx(1, "unknown interface name %s", ifn);
/*
 * Get interface address.
 */
	sin = NULL;
	while (next < lim) {
		ifam = (struct ifa_msghdr *)next;
		next += ifam->ifam_msglen;
		if (ifam->ifam_version != RTM_VERSION) {
			if (co.verbose)
				warnx("routing message version %d "
				    "not understood", ifam->ifam_version);
			continue;
		}
		if (ifam->ifam_type != RTM_NEWADDR)
			break;
		if (ifam->ifam_addrs & RTA_IFA) {
			int i;
			char *cp = (char *)(ifam + 1);

			for (i = 1; i < RTA_IFA; i <<= 1) {
				if (ifam->ifam_addrs & i)
					cp += SA_SIZE((struct sockaddr *)cp);
			}
			if (((struct sockaddr *)cp)->sa_family == AF_INET) {
				sin = (struct sockaddr_in *)cp;
				break;
			}
		}
	}
	if (sin == NULL)
		n->ip.s_addr = htonl(INADDR_ANY);
	else
		n->ip = sin->sin_addr;
	strncpy(n->if_name, ifn, IF_NAMESIZE);

	free(buf);
}