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
struct ieee80211_scan_ssid {scalar_t__ len; int /*<<< orphan*/  ssid; } ;
struct ieee80211_node {scalar_t__ ni_esslen; int /*<<< orphan*/  ni_essid; } ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
match_ssid(const struct ieee80211_node *ni,
	int nssid, const struct ieee80211_scan_ssid ssids[])
{
	int i;

	for (i = 0; i < nssid; i++) {
		if (ni->ni_esslen == ssids[i].len &&
		     memcmp(ni->ni_essid, ssids[i].ssid, ni->ni_esslen) == 0)
			return 1;
	}
	return 0;
}