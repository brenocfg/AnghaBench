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
struct wpa_bss {int caps; } ;

/* Variables and functions */
 int IEEE80211_CAP_DMG_AP ; 
 int IEEE80211_CAP_DMG_MASK ; 
 int IEEE80211_CAP_ESS ; 
 int IEEE80211_CAP_IBSS ; 
 scalar_t__ bss_is_dmg (struct wpa_bss*) ; 

__attribute__((used)) static int bss_is_ess(struct wpa_bss *bss)
{
	if (bss_is_dmg(bss)) {
		return (bss->caps & IEEE80211_CAP_DMG_MASK) ==
			IEEE80211_CAP_DMG_AP;
	}

	return ((bss->caps & (IEEE80211_CAP_ESS | IEEE80211_CAP_IBSS)) ==
		IEEE80211_CAP_ESS);
}