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
struct ieee80211vap {int /*<<< orphan*/  iv_des_ssid; int /*<<< orphan*/  iv_des_nssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_SCAN_ACTIVE ; 
 int /*<<< orphan*/  IEEE80211_SCAN_FOREVER ; 
 int ieee80211_check_scan (struct ieee80211vap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ieee80211_check_scan_current(struct ieee80211vap *vap)
{
	return ieee80211_check_scan(vap,
	    IEEE80211_SCAN_ACTIVE,
	    IEEE80211_SCAN_FOREVER, 0, 0,
	    vap->iv_des_nssid, vap->iv_des_ssid);
}