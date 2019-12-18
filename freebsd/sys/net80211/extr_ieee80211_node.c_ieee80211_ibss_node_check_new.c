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
struct ieee80211vap {int iv_des_nssid; TYPE_1__* iv_des_ssid; } ;
struct ieee80211_scanparams {scalar_t__* ssid; } ;
struct ieee80211_node {struct ieee80211vap* ni_vap; } ;
struct TYPE_2__ {scalar_t__ len; int /*<<< orphan*/  ssid; } ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 

int
ieee80211_ibss_node_check_new(struct ieee80211_node *ni,
    const struct ieee80211_scanparams *scan)
{
	struct ieee80211vap *vap = ni->ni_vap;
	int i;

	/*
	 * If we have no SSID and no scan SSID, return OK.
	 */
	if (vap->iv_des_nssid == 0 && scan->ssid == NULL)
		goto ok;

	/*
	 * If we have one of (SSID, scan SSID) then return error.
	 */
	if (!! (vap->iv_des_nssid == 0) != !! (scan->ssid == NULL))
		goto mismatch;

	/*
	 * Double-check - we need scan SSID.
	 */
	if (scan->ssid == NULL)
		goto mismatch;

	/*
	 * Check if the scan SSID matches the SSID list for the VAP.
	 */
	for (i = 0; i < vap->iv_des_nssid; i++) {

		/* Sanity length check */
		if (vap->iv_des_ssid[i].len != scan->ssid[1])
			continue;

		/* Note: SSID in the scan entry is the IE format */
		if (memcmp(vap->iv_des_ssid[i].ssid, scan->ssid + 2,
		    vap->iv_des_ssid[i].len) == 0)
			goto ok;
	}

mismatch:
	return (0);
ok:
	return (1);
}