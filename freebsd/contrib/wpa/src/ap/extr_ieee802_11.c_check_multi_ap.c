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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sta_info {int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct hostapd_data {TYPE_1__* conf; } ;
struct TYPE_2__ {int multi_ap; } ;

/* Variables and functions */
 int BACKHAUL_BSS ; 
 int FRONTHAUL_BSS ; 
 int /*<<< orphan*/  HOSTAPD_LEVEL_DEBUG ; 
 int /*<<< orphan*/  HOSTAPD_LEVEL_INFO ; 
 int /*<<< orphan*/  HOSTAPD_MODULE_IEEE80211 ; 
 int MULTI_AP_BACKHAUL_STA ; 
 int /*<<< orphan*/  MULTI_AP_SUB_ELEM_TYPE ; 
 int /*<<< orphan*/  WLAN_STATUS_ASSOC_DENIED_UNSPEC ; 
 int /*<<< orphan*/  WLAN_STATUS_INVALID_IE ; 
 int /*<<< orphan*/  WLAN_STATUS_SUCCESS ; 
 int /*<<< orphan*/  WLAN_STA_MULTI_AP ; 
 int* get_ie (int const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostapd_logger (struct hostapd_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static u16 check_multi_ap(struct hostapd_data *hapd, struct sta_info *sta,
			  const u8 *multi_ap_ie, size_t multi_ap_len)
{
	u8 multi_ap_value = 0;

	sta->flags &= ~WLAN_STA_MULTI_AP;

	if (!hapd->conf->multi_ap)
		return WLAN_STATUS_SUCCESS;

	if (multi_ap_ie) {
		const u8 *multi_ap_subelem;

		multi_ap_subelem = get_ie(multi_ap_ie + 4,
					  multi_ap_len - 4,
					  MULTI_AP_SUB_ELEM_TYPE);
		if (multi_ap_subelem && multi_ap_subelem[1] == 1) {
			multi_ap_value = multi_ap_subelem[2];
		} else {
			hostapd_logger(hapd, sta->addr,
				       HOSTAPD_MODULE_IEEE80211,
				       HOSTAPD_LEVEL_INFO,
				       "Multi-AP IE has missing or invalid Multi-AP subelement");
			return WLAN_STATUS_INVALID_IE;
		}
	}

	if (multi_ap_value && multi_ap_value != MULTI_AP_BACKHAUL_STA)
		hostapd_logger(hapd, sta->addr, HOSTAPD_MODULE_IEEE80211,
			       HOSTAPD_LEVEL_INFO,
			       "Multi-AP IE with unexpected value 0x%02x",
			       multi_ap_value);

	if (!(multi_ap_value & MULTI_AP_BACKHAUL_STA)) {
		if (hapd->conf->multi_ap & FRONTHAUL_BSS)
			return WLAN_STATUS_SUCCESS;

		hostapd_logger(hapd, sta->addr,
			       HOSTAPD_MODULE_IEEE80211,
			       HOSTAPD_LEVEL_INFO,
			       "Non-Multi-AP STA tries to associate with backhaul-only BSS");
		return WLAN_STATUS_ASSOC_DENIED_UNSPEC;
	}

	if (!(hapd->conf->multi_ap & BACKHAUL_BSS))
		hostapd_logger(hapd, sta->addr, HOSTAPD_MODULE_IEEE80211,
			       HOSTAPD_LEVEL_DEBUG,
			       "Backhaul STA tries to associate with fronthaul-only BSS");

	sta->flags |= WLAN_STA_MULTI_AP;
	return WLAN_STATUS_SUCCESS;
}