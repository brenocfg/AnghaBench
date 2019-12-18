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
struct sta_info {int /*<<< orphan*/  addr; } ;
struct hostapd_data {TYPE_2__* conf; } ;
struct TYPE_3__ {size_t ssid_len; int /*<<< orphan*/  ssid; } ;
struct TYPE_4__ {TYPE_1__ ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOSTAPD_LEVEL_INFO ; 
 int /*<<< orphan*/  HOSTAPD_MODULE_IEEE80211 ; 
 int /*<<< orphan*/  WLAN_STATUS_SUCCESS ; 
 int /*<<< orphan*/  WLAN_STATUS_UNSPECIFIED_FAILURE ; 
 int /*<<< orphan*/  hostapd_logger (struct hostapd_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  wpa_ssid_txt (int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static u16 check_ssid(struct hostapd_data *hapd, struct sta_info *sta,
		      const u8 *ssid_ie, size_t ssid_ie_len)
{
	if (ssid_ie == NULL)
		return WLAN_STATUS_UNSPECIFIED_FAILURE;

	if (ssid_ie_len != hapd->conf->ssid.ssid_len ||
	    os_memcmp(ssid_ie, hapd->conf->ssid.ssid, ssid_ie_len) != 0) {
		hostapd_logger(hapd, sta->addr, HOSTAPD_MODULE_IEEE80211,
			       HOSTAPD_LEVEL_INFO,
			       "Station tried to associate with unknown SSID "
			       "'%s'", wpa_ssid_txt(ssid_ie, ssid_ie_len));
		return WLAN_STATUS_UNSPECIFIED_FAILURE;
	}

	return WLAN_STATUS_SUCCESS;
}