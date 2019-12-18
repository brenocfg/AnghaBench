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
struct TYPE_2__ {int /*<<< orphan*/  ifr_name; } ;
struct wlanstatfoo_p {int opmode; TYPE_1__ ifr; int /*<<< orphan*/  s; } ;
struct wlanstatfoo {int dummy; } ;
struct ifmediareq {int ifm_current; int /*<<< orphan*/  ifm_name; } ;
typedef  int /*<<< orphan*/  ifmr ;

/* Variables and functions */
 int IEEE80211_M_AHDEMO ; 
 int IEEE80211_M_HOSTAP ; 
 int IEEE80211_M_IBSS ; 
 int IEEE80211_M_MONITOR ; 
 int IEEE80211_M_STA ; 
 int IFM_FLAG0 ; 
 int IFM_IEEE80211_ADHOC ; 
 int IFM_IEEE80211_HOSTAP ; 
 int IFM_IEEE80211_MONITOR ; 
 int /*<<< orphan*/  SIOCGIFMEDIA ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifmediareq*) ; 
 int /*<<< orphan*/  memset (struct ifmediareq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
wlan_getopmode(struct wlanstatfoo *wf0)
{
	struct wlanstatfoo_p *wf = (struct wlanstatfoo_p *) wf0;

	if (wf->opmode == -1) {
		struct ifmediareq ifmr;

		memset(&ifmr, 0, sizeof(ifmr));
		strlcpy(ifmr.ifm_name, wf->ifr.ifr_name, sizeof(ifmr.ifm_name));
		if (ioctl(wf->s, SIOCGIFMEDIA, &ifmr) < 0)
			err(1, "%s (SIOCGIFMEDIA)", wf->ifr.ifr_name);
		if (ifmr.ifm_current & IFM_IEEE80211_ADHOC) {
			if (ifmr.ifm_current & IFM_FLAG0)
				wf->opmode = IEEE80211_M_AHDEMO;
			else
				wf->opmode = IEEE80211_M_IBSS;
		} else if (ifmr.ifm_current & IFM_IEEE80211_HOSTAP)
			wf->opmode = IEEE80211_M_HOSTAP;
		else if (ifmr.ifm_current & IFM_IEEE80211_MONITOR)
			wf->opmode = IEEE80211_M_MONITOR;
		else
			wf->opmode = IEEE80211_M_STA;
	}
	return wf->opmode;
}