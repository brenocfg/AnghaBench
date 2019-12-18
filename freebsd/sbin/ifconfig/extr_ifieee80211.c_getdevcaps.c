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
struct ieee80211_devcaps_req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_DEVCAPS_SPACE (struct ieee80211_devcaps_req*) ; 
 int /*<<< orphan*/  IEEE80211_IOC_DEVCAPS ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ get80211 (int,int /*<<< orphan*/ ,struct ieee80211_devcaps_req*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
getdevcaps(int s, struct ieee80211_devcaps_req *dc)
{
	if (get80211(s, IEEE80211_IOC_DEVCAPS, dc,
	    IEEE80211_DEVCAPS_SPACE(dc)) < 0)
		err(1, "unable to get device capabilities");
}