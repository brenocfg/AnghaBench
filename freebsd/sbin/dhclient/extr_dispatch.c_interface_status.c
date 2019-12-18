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
struct interface_info {char* name; int rfdesc; int noifmedia; } ;
struct ifreq {int ifr_flags; int ifm_status; int ifm_active; int /*<<< orphan*/  ifm_name; int /*<<< orphan*/  ifr_name; } ;
struct ifmediareq {int ifr_flags; int ifm_status; int ifm_active; int /*<<< orphan*/  ifm_name; int /*<<< orphan*/  ifr_name; } ;
typedef  int /*<<< orphan*/  ifr ;
typedef  int /*<<< orphan*/  ifmr ;
typedef  struct ifreq* caddr_t ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int IFF_RUNNING ; 
 int IFF_UP ; 
 int IFM_ACTIVE ; 
 int IFM_AVALID ; 
#define  IFM_ETHER 129 
#define  IFM_IEEE80211 128 
 int IFM_NMASK ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  SIOCGIFFLAGS ; 
 int /*<<< orphan*/  SIOCGIFMEDIA ; 
 int /*<<< orphan*/  cap_syslog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  capsyslog ; 
 scalar_t__ errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  memset (struct ifreq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

int
interface_status(struct interface_info *ifinfo)
{
	char *ifname = ifinfo->name;
	int ifsock = ifinfo->rfdesc;
	struct ifreq ifr;
	struct ifmediareq ifmr;

	/* get interface flags */
	memset(&ifr, 0, sizeof(ifr));
	strlcpy(ifr.ifr_name, ifname, sizeof(ifr.ifr_name));
	if (ioctl(ifsock, SIOCGIFFLAGS, &ifr) < 0) {
		cap_syslog(capsyslog, LOG_ERR, "ioctl(SIOCGIFFLAGS) on %s: %m",
		    ifname);
		goto inactive;
	}

	/*
	 * if one of UP and RUNNING flags is dropped,
	 * the interface is not active.
	 */
	if ((ifr.ifr_flags & (IFF_UP|IFF_RUNNING)) != (IFF_UP|IFF_RUNNING))
		goto inactive;

	/* Next, check carrier on the interface, if possible */
	if (ifinfo->noifmedia)
		goto active;
	memset(&ifmr, 0, sizeof(ifmr));
	strlcpy(ifmr.ifm_name, ifname, sizeof(ifmr.ifm_name));
	if (ioctl(ifsock, SIOCGIFMEDIA, (caddr_t)&ifmr) < 0) {
		if (errno != EINVAL) {
			cap_syslog(capsyslog, LOG_DEBUG,
			    "ioctl(SIOCGIFMEDIA) on %s: %m", ifname);
			ifinfo->noifmedia = 1;
			goto active;
		}
		/*
		 * EINVAL (or ENOTTY) simply means that the interface
		 * does not support the SIOCGIFMEDIA ioctl. We regard it alive.
		 */
		ifinfo->noifmedia = 1;
		goto active;
	}
	if (ifmr.ifm_status & IFM_AVALID) {
		switch (ifmr.ifm_active & IFM_NMASK) {
		case IFM_ETHER:
		case IFM_IEEE80211:
			if (ifmr.ifm_status & IFM_ACTIVE)
				goto active;
			else
				goto inactive;
			break;
		default:
			goto inactive;
		}
	}
inactive:
	return (0);
active:
	return (1);
}