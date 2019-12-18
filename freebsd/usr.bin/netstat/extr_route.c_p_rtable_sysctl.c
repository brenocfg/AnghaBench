#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_dl {int sdl_index; } ;
struct sockaddr {int sa_family; } ;
struct rt_msghdr {scalar_t__ rtm_version; int /*<<< orphan*/  rtm_msglen; } ;
struct ifmap_entry {int dummy; } ;
struct ifaddrs {int /*<<< orphan*/  ifa_name; TYPE_1__* ifa_addr; struct ifaddrs* ifa_next; } ;
struct TYPE_7__ {char* ifname; } ;
struct TYPE_6__ {scalar_t__ sa_family; } ;

/* Variables and functions */
 scalar_t__ AF_LINK ; 
 int AF_UNSPEC ; 
 int CTL_NET ; 
 int EX_OSERR ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int NET_RT_DUMP ; 
 int PF_ROUTE ; 
 scalar_t__ RTM_VERSION ; 
 int /*<<< orphan*/  WID_DST_DEFAULT (int) ; 
 int /*<<< orphan*/  WID_GW_DEFAULT (int) ; 
 int /*<<< orphan*/  WID_IF_DEFAULT (int) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*,unsigned long) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  freeifaddrs (struct ifaddrs*) ; 
 scalar_t__ getifaddrs (struct ifaddrs**) ; 
 TYPE_2__* ifmap ; 
 int ifmap_size ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nitems (int*) ; 
 int /*<<< orphan*/  p_rtentry_sysctl (char*,struct rt_msghdr*) ; 
 int /*<<< orphan*/  pr_family (int) ; 
 int /*<<< orphan*/  pr_rthdr (int) ; 
 TYPE_2__* realloc (TYPE_2__*,int) ; 
 int roundup (int,int) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sysctl (int*,int /*<<< orphan*/ ,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wid_dst ; 
 int wid_expire ; 
 int wid_flags ; 
 int /*<<< orphan*/  wid_gw ; 
 int /*<<< orphan*/  wid_if ; 
 int wid_mtu ; 
 int wid_pksent ; 
 int /*<<< orphan*/  xo_close_container (char*) ; 
 int /*<<< orphan*/  xo_close_instance (char*) ; 
 int /*<<< orphan*/  xo_close_list (char*) ; 
 int /*<<< orphan*/  xo_open_container (char*) ; 
 int /*<<< orphan*/  xo_open_instance (char*) ; 
 int /*<<< orphan*/  xo_open_list (char*) ; 

__attribute__((used)) static void
p_rtable_sysctl(int fibnum, int af)
{
	size_t needed;
	int mib[7];
	char *buf, *next, *lim;
	struct rt_msghdr *rtm;
	struct sockaddr *sa;
	int fam = AF_UNSPEC, ifindex = 0, size;
	int need_table_close = false;

	struct ifaddrs *ifap, *ifa;
	struct sockaddr_dl *sdl;

	/*
	 * Retrieve interface list at first
	 * since we need #ifindex -> if_xname match
	 */
	if (getifaddrs(&ifap) != 0)
		err(EX_OSERR, "getifaddrs");

	for (ifa = ifap; ifa; ifa = ifa->ifa_next) {
		
		if (ifa->ifa_addr->sa_family != AF_LINK)
			continue;

		sdl = (struct sockaddr_dl *)ifa->ifa_addr;
		ifindex = sdl->sdl_index;

		if (ifindex >= ifmap_size) {
			size = roundup(ifindex + 1, 32) *
			    sizeof(struct ifmap_entry);
			if ((ifmap = realloc(ifmap, size)) == NULL)
				errx(2, "realloc(%d) failed", size);
			memset(&ifmap[ifmap_size], 0,
			    size - ifmap_size *
			    sizeof(struct ifmap_entry));

			ifmap_size = roundup(ifindex + 1, 32);
		}

		if (*ifmap[ifindex].ifname != '\0')
			continue;

		strlcpy(ifmap[ifindex].ifname, ifa->ifa_name, IFNAMSIZ);
	}

	freeifaddrs(ifap);

	mib[0] = CTL_NET;
	mib[1] = PF_ROUTE;
	mib[2] = 0;
	mib[3] = af;
	mib[4] = NET_RT_DUMP;
	mib[5] = 0;
	mib[6] = fibnum;
	if (sysctl(mib, nitems(mib), NULL, &needed, NULL, 0) < 0)
		err(EX_OSERR, "sysctl: net.route.0.%d.dump.%d estimate", af,
		    fibnum);
	if ((buf = malloc(needed)) == NULL)
		errx(2, "malloc(%lu)", (unsigned long)needed);
	if (sysctl(mib, nitems(mib), buf, &needed, NULL, 0) < 0)
		err(1, "sysctl: net.route.0.%d.dump.%d", af, fibnum);
	lim  = buf + needed;
	xo_open_container("route-table");
	xo_open_list("rt-family");
	for (next = buf; next < lim; next += rtm->rtm_msglen) {
		rtm = (struct rt_msghdr *)next;
		if (rtm->rtm_version != RTM_VERSION)
			continue;
		/*
		 * Peek inside header to determine AF
		 */
		sa = (struct sockaddr *)(rtm + 1);
		/* Only print family first time. */
		if (fam != sa->sa_family) {
			if (need_table_close) {
				xo_close_list("rt-entry");
				xo_close_instance("rt-family");
			}
			need_table_close = true;

			fam = sa->sa_family;
			wid_dst = WID_DST_DEFAULT(fam);
			wid_gw = WID_GW_DEFAULT(fam);
			wid_flags = 6;
			wid_pksent = 8;
			wid_mtu = 6;
			wid_if = WID_IF_DEFAULT(fam);
			wid_expire = 6;
			xo_open_instance("rt-family");
			pr_family(fam);
			xo_open_list("rt-entry");

			pr_rthdr(fam);
		}
		p_rtentry_sysctl("rt-entry", rtm);
	}
	if (need_table_close) {
		xo_close_list("rt-entry");
		xo_close_instance("rt-family");
	}
	xo_close_list("rt-family");
	xo_close_container("route-table");
	free(buf);
}