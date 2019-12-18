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
typedef  unsigned int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sta_info {int flags; int /*<<< orphan*/ * vht_capabilities; } ;
struct ieee80211_vht_capabilities {int dummy; } ;
struct hostapd_data {TYPE_1__* conf; } ;
struct TYPE_2__ {scalar_t__ disable_11ac; } ;

/* Variables and functions */
 unsigned int const WLAN_EID_VHT_CAP ; 
 int /*<<< orphan*/  WLAN_STATUS_SUCCESS ; 
 int /*<<< orphan*/  WLAN_STATUS_UNSPECIFIED_FAILURE ; 
 int WLAN_STA_VENDOR_VHT ; 
 int WLAN_STA_VHT ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,unsigned int const*,int) ; 
 int /*<<< orphan*/ * os_zalloc (int) ; 

u16 copy_sta_vendor_vht(struct hostapd_data *hapd, struct sta_info *sta,
			const u8 *ie, size_t len)
{
	const u8 *vht_capab;
	unsigned int vht_capab_len;

	if (!ie || len < 5 + 2 + sizeof(struct ieee80211_vht_capabilities) ||
	    hapd->conf->disable_11ac)
		goto no_capab;

	/* The VHT Capabilities element embedded in vendor VHT */
	vht_capab = ie + 5;
	if (vht_capab[0] != WLAN_EID_VHT_CAP)
		goto no_capab;
	vht_capab_len = vht_capab[1];
	if (vht_capab_len < sizeof(struct ieee80211_vht_capabilities) ||
	    (int) vht_capab_len > ie + len - vht_capab - 2)
		goto no_capab;
	vht_capab += 2;

	if (sta->vht_capabilities == NULL) {
		sta->vht_capabilities =
			os_zalloc(sizeof(struct ieee80211_vht_capabilities));
		if (sta->vht_capabilities == NULL)
			return WLAN_STATUS_UNSPECIFIED_FAILURE;
	}

	sta->flags |= WLAN_STA_VHT | WLAN_STA_VENDOR_VHT;
	os_memcpy(sta->vht_capabilities, vht_capab,
		  sizeof(struct ieee80211_vht_capabilities));
	return WLAN_STATUS_SUCCESS;

no_capab:
	sta->flags &= ~WLAN_STA_VENDOR_VHT;
	return WLAN_STATUS_SUCCESS;
}