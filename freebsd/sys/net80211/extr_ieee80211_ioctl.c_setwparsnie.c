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
typedef  int uint8_t ;
struct ieee80211vap {int* iv_wpa_ie; int* iv_rsn_ie; } ;

/* Variables and functions */
 int IEEE80211_ELEMID_RSN ; 
 int IEEE80211_ELEMID_VENDOR ; 

__attribute__((used)) static void
setwparsnie(struct ieee80211vap *vap, uint8_t *ie, int space)
{
	/* validate data is present as best we can */
	if (space == 0 || 2+ie[1] > space)
		return;
	if (ie[0] == IEEE80211_ELEMID_VENDOR)
		vap->iv_wpa_ie = ie;
	else if (ie[0] == IEEE80211_ELEMID_RSN)
		vap->iv_rsn_ie = ie;
}