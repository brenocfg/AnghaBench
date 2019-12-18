#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sta_info {int flags; int /*<<< orphan*/ * ht_capabilities; } ;
struct ieee80211_ht_capabilities {int dummy; } ;
struct hostapd_data {TYPE_2__* conf; TYPE_1__* iconf; } ;
struct TYPE_4__ {scalar_t__ disable_11n; } ;
struct TYPE_3__ {int /*<<< orphan*/  ieee80211n; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_STATUS_SUCCESS ; 
 int /*<<< orphan*/  WLAN_STATUS_UNSPECIFIED_FAILURE ; 
 int WLAN_STA_HT ; 
 int WLAN_STA_WMM ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * os_zalloc (int) ; 

u16 copy_sta_ht_capab(struct hostapd_data *hapd, struct sta_info *sta,
		      const u8 *ht_capab)
{
	/*
	 * Disable HT caps for STAs associated to no-HT BSSes, or for stations
	 * that did not specify a valid WMM IE in the (Re)Association Request
	 * frame.
	 */
	if (!ht_capab || !(sta->flags & WLAN_STA_WMM) ||
	    !hapd->iconf->ieee80211n || hapd->conf->disable_11n) {
		sta->flags &= ~WLAN_STA_HT;
		os_free(sta->ht_capabilities);
		sta->ht_capabilities = NULL;
		return WLAN_STATUS_SUCCESS;
	}

	if (sta->ht_capabilities == NULL) {
		sta->ht_capabilities =
			os_zalloc(sizeof(struct ieee80211_ht_capabilities));
		if (sta->ht_capabilities == NULL)
			return WLAN_STATUS_UNSPECIFIED_FAILURE;
	}

	sta->flags |= WLAN_STA_HT;
	os_memcpy(sta->ht_capabilities, ht_capab,
		  sizeof(struct ieee80211_ht_capabilities));

	return WLAN_STATUS_SUCCESS;
}