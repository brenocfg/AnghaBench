#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sta_info {int /*<<< orphan*/ * vht_capabilities; int /*<<< orphan*/  flags; } ;
struct ieee80211_vht_capabilities {int dummy; } ;
struct hostapd_data {TYPE_2__* iface; TYPE_1__* conf; TYPE_3__* iconf; } ;
struct TYPE_6__ {int /*<<< orphan*/  ieee80211ac; } ;
struct TYPE_5__ {int /*<<< orphan*/  current_mode; } ;
struct TYPE_4__ {scalar_t__ disable_11ac; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_STATUS_SUCCESS ; 
 int /*<<< orphan*/  WLAN_STATUS_UNSPECIFIED_FAILURE ; 
 int /*<<< orphan*/  WLAN_STA_VHT ; 
 int /*<<< orphan*/  check_valid_vht_mcs (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * os_zalloc (int) ; 

u16 copy_sta_vht_capab(struct hostapd_data *hapd, struct sta_info *sta,
		       const u8 *vht_capab)
{
	/* Disable VHT caps for STAs associated to no-VHT BSSes. */
	if (!vht_capab ||
	    !hapd->iconf->ieee80211ac || hapd->conf->disable_11ac ||
	    !check_valid_vht_mcs(hapd->iface->current_mode, vht_capab)) {
		sta->flags &= ~WLAN_STA_VHT;
		os_free(sta->vht_capabilities);
		sta->vht_capabilities = NULL;
		return WLAN_STATUS_SUCCESS;
	}

	if (sta->vht_capabilities == NULL) {
		sta->vht_capabilities =
			os_zalloc(sizeof(struct ieee80211_vht_capabilities));
		if (sta->vht_capabilities == NULL)
			return WLAN_STATUS_UNSPECIFIED_FAILURE;
	}

	sta->flags |= WLAN_STA_VHT;
	os_memcpy(sta->vht_capabilities, vht_capab,
		  sizeof(struct ieee80211_vht_capabilities));

	return WLAN_STATUS_SUCCESS;
}