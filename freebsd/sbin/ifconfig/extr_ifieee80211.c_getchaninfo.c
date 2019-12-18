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

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_CHANINFO_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_IOC_CHANINFO ; 
 int /*<<< orphan*/  MAXCHAN ; 
 int /*<<< orphan*/ * chaninfo ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ get80211 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gethtconf (int) ; 
 int /*<<< orphan*/  getvhtconf (int) ; 
 int /*<<< orphan*/  ifmedia_getstate (int) ; 
 int /*<<< orphan*/  ifmr ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
getchaninfo(int s)
{
	if (chaninfo != NULL)
		return;
	chaninfo = malloc(IEEE80211_CHANINFO_SIZE(MAXCHAN));
	if (chaninfo == NULL)
		errx(1, "no space for channel list");
	if (get80211(s, IEEE80211_IOC_CHANINFO, chaninfo,
	    IEEE80211_CHANINFO_SIZE(MAXCHAN)) < 0)
		err(1, "unable to get channel information");
	ifmr = ifmedia_getstate(s);
	gethtconf(s);
	getvhtconf(s);
}