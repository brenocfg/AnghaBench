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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct wmm_information_element {scalar_t__ qos_info; } ;
struct sta_info {scalar_t__ qosinfo; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct hostapd_data {TYPE_1__* conf; } ;
struct TYPE_2__ {scalar_t__ wmm_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOSTAPD_LEVEL_DEBUG ; 
 int /*<<< orphan*/  HOSTAPD_MODULE_WPA ; 
 int /*<<< orphan*/  WLAN_STATUS_SUCCESS ; 
 int /*<<< orphan*/  WLAN_STATUS_UNSPECIFIED_FAILURE ; 
 int /*<<< orphan*/  WLAN_STA_WMM ; 
 int /*<<< orphan*/  hostapd_eid_wmm_valid (struct hostapd_data*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  hostapd_logger (struct hostapd_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static u16 check_wmm(struct hostapd_data *hapd, struct sta_info *sta,
		     const u8 *wmm_ie, size_t wmm_ie_len)
{
	sta->flags &= ~WLAN_STA_WMM;
	sta->qosinfo = 0;
	if (wmm_ie && hapd->conf->wmm_enabled) {
		struct wmm_information_element *wmm;

		if (!hostapd_eid_wmm_valid(hapd, wmm_ie, wmm_ie_len)) {
			hostapd_logger(hapd, sta->addr,
				       HOSTAPD_MODULE_WPA,
				       HOSTAPD_LEVEL_DEBUG,
				       "invalid WMM element in association "
				       "request");
			return WLAN_STATUS_UNSPECIFIED_FAILURE;
		}

		sta->flags |= WLAN_STA_WMM;
		wmm = (struct wmm_information_element *) wmm_ie;
		sta->qosinfo = wmm->qos_info;
	}
	return WLAN_STATUS_SUCCESS;
}