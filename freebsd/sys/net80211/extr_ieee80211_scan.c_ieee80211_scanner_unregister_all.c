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
struct ieee80211_scanner {int dummy; } ;

/* Variables and functions */
 int IEEE80211_OPMODE_MAX ; 
 struct ieee80211_scanner const** scanners ; 

void
ieee80211_scanner_unregister_all(const struct ieee80211_scanner *scan)
{
	int m;

	for (m = 0; m < IEEE80211_OPMODE_MAX; m++)
		if (scanners[m] == scan)
			scanners[m] = NULL;
}