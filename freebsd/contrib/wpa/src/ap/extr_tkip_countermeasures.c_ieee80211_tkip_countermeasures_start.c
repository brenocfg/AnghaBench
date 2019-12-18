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
struct sta_info {int flags; int /*<<< orphan*/  addr; int /*<<< orphan*/  acct_terminate_cause; } ;
struct hostapd_data {int tkip_countermeasures; struct sta_info* sta_list; int /*<<< orphan*/  wpa_auth; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOSTAPD_LEVEL_INFO ; 
 int /*<<< orphan*/  HOSTAPD_MODULE_IEEE80211 ; 
 int /*<<< orphan*/  RADIUS_ACCT_TERMINATE_CAUSE_ADMIN_RESET ; 
 int /*<<< orphan*/  WLAN_REASON_MICHAEL_MIC_FAILURE ; 
 int WLAN_STA_AUTH ; 
 int /*<<< orphan*/  ap_free_sta (struct hostapd_data*,struct sta_info*) ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct hostapd_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_register_timeout (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hostapd_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hostapd_drv_set_countermeasures (struct hostapd_data*,int) ; 
 int /*<<< orphan*/  hostapd_drv_sta_deauth (struct hostapd_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostapd_logger (struct hostapd_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ieee80211_tkip_countermeasures_stop ; 
 int /*<<< orphan*/  mlme_deauthenticate_indication (struct hostapd_data*,struct sta_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_auth_countermeasures_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_gtk_rekey (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ieee80211_tkip_countermeasures_start(struct hostapd_data *hapd)
{
	struct sta_info *sta;

	hostapd_logger(hapd, NULL, HOSTAPD_MODULE_IEEE80211,
		       HOSTAPD_LEVEL_INFO, "TKIP countermeasures initiated");

	wpa_auth_countermeasures_start(hapd->wpa_auth);
	hapd->tkip_countermeasures = 1;
	hostapd_drv_set_countermeasures(hapd, 1);
	wpa_gtk_rekey(hapd->wpa_auth);
	eloop_cancel_timeout(ieee80211_tkip_countermeasures_stop, hapd, NULL);
	eloop_register_timeout(60, 0, ieee80211_tkip_countermeasures_stop,
			       hapd, NULL);
	while ((sta = hapd->sta_list)) {
		sta->acct_terminate_cause =
			RADIUS_ACCT_TERMINATE_CAUSE_ADMIN_RESET;
		if (sta->flags & WLAN_STA_AUTH) {
			mlme_deauthenticate_indication(
				hapd, sta,
				WLAN_REASON_MICHAEL_MIC_FAILURE);
		}
		hostapd_drv_sta_deauth(hapd, sta->addr,
				       WLAN_REASON_MICHAEL_MIC_FAILURE);
		ap_free_sta(hapd, sta);
	}
}