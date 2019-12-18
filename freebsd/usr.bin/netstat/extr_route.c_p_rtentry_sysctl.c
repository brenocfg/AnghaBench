#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct sockaddr {int dummy; } ;
struct TYPE_4__ {scalar_t__ rmx_mtu; scalar_t__ rmx_expire; int /*<<< orphan*/  rmx_pksent; } ;
struct rt_msghdr {int rtm_addrs; size_t rtm_index; TYPE_1__ rtm_rmx; int /*<<< orphan*/  rtm_flags; } ;
typedef  int /*<<< orphan*/  prettyname ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_6__ {char* ifname; } ;
struct TYPE_5__ {scalar_t__ tv_sec; } ;

/* Variables and functions */
 size_t RTAX_DST ; 
 size_t RTAX_GATEWAY ; 
 int RTAX_MAX ; 
 size_t RTAX_NETMASK ; 
 int /*<<< orphan*/  RTF_HOST ; 
 int SA_SIZE (struct sockaddr*) ; 
 scalar_t__ Wflag ; 
 TYPE_3__* ifmap ; 
 size_t ifmap_size ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  p_flags (int /*<<< orphan*/ ,char*) ; 
 int p_sockaddr (char*,struct sockaddr*,struct sockaddr*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 TYPE_2__ uptime ; 
 scalar_t__ wid_dst ; 
 int /*<<< orphan*/  wid_expire ; 
 int wid_flags ; 
 scalar_t__ wid_gw ; 
 int /*<<< orphan*/  wid_if ; 
 int /*<<< orphan*/  wid_mtu ; 
 int /*<<< orphan*/  wid_pksent ; 
 int /*<<< orphan*/  xo_close_instance (char const*) ; 
 int /*<<< orphan*/  xo_emit (char*,...) ; 
 int /*<<< orphan*/  xo_open_instance (char const*) ; 

__attribute__((used)) static void
p_rtentry_sysctl(const char *name, struct rt_msghdr *rtm)
{
	struct sockaddr *sa, *addr[RTAX_MAX];
	char buffer[128];
	char prettyname[128];
	int i, protrusion;

	xo_open_instance(name);
	sa = (struct sockaddr *)(rtm + 1);
	for (i = 0; i < RTAX_MAX; i++) {
		if (rtm->rtm_addrs & (1 << i)) {
			addr[i] = sa;
			sa = (struct sockaddr *)((char *)sa + SA_SIZE(sa));
		}
	}

	protrusion = p_sockaddr("destination", addr[RTAX_DST],
	    addr[RTAX_NETMASK],
	    rtm->rtm_flags, wid_dst);
	protrusion = p_sockaddr("gateway", addr[RTAX_GATEWAY], NULL, RTF_HOST,
	    wid_gw - protrusion);
	snprintf(buffer, sizeof(buffer), "{[:-%d}{:flags/%%s}{]:} ",
	    wid_flags - protrusion);
	p_flags(rtm->rtm_flags, buffer);
	if (Wflag) {
		xo_emit("{t:use/%*lu} ", wid_pksent, rtm->rtm_rmx.rmx_pksent);

		if (rtm->rtm_rmx.rmx_mtu != 0)
			xo_emit("{t:mtu/%*lu} ", wid_mtu, rtm->rtm_rmx.rmx_mtu);
		else
			xo_emit("{P:/%*s} ", wid_mtu, "");
	}

	memset(prettyname, 0, sizeof(prettyname));
	if (rtm->rtm_index < ifmap_size) {
		strlcpy(prettyname, ifmap[rtm->rtm_index].ifname,
		    sizeof(prettyname));
		if (*prettyname == '\0')
			strlcpy(prettyname, "---", sizeof(prettyname));
	}

	if (Wflag)
		xo_emit("{t:interface-name/%*s}", wid_if, prettyname);
	else
		xo_emit("{t:interface-name/%*.*s}", wid_if, wid_if,
		    prettyname);
	if (rtm->rtm_rmx.rmx_expire) {
		time_t expire_time;

		if ((expire_time = rtm->rtm_rmx.rmx_expire - uptime.tv_sec) > 0)
			xo_emit(" {:expire-time/%*d}", wid_expire,
			    (int)expire_time);
	}

	xo_emit("\n");
	xo_close_instance(name);
}