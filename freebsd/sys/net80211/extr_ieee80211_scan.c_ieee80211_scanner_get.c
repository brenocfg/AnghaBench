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
typedef  enum ieee80211_opmode { ____Placeholder_ieee80211_opmode } ieee80211_opmode ;

/* Variables and functions */
 int IEEE80211_OPMODE_MAX ; 
 int /*<<< orphan*/  ieee80211_load_module (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * scan_modnames ; 
 struct ieee80211_scanner const** scanners ; 

const struct ieee80211_scanner *
ieee80211_scanner_get(enum ieee80211_opmode mode)
{
	if (mode >= IEEE80211_OPMODE_MAX)
		return NULL;
	if (scanners[mode] == NULL)
		ieee80211_load_module(scan_modnames[mode]);
	return scanners[mode];
}