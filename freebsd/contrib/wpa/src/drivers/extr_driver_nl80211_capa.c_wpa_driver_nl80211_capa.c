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
struct TYPE_4__ {int key_mgmt; int flags; int auth; } ;
struct wpa_driver_nl80211_data {int has_capability; int use_monitor; TYPE_2__ capa; int /*<<< orphan*/  have_low_prio_scan; int /*<<< orphan*/  p2p_go_ctwindow_supported; int /*<<< orphan*/  data_tx_status; int /*<<< orphan*/  poll_command_supported; scalar_t__ device_ap_sme; } ;
struct wiphy_info_data {TYPE_1__* capa; int /*<<< orphan*/  data_tx_status; int /*<<< orphan*/  poll_command_supported; scalar_t__ device_ap_sme; int /*<<< orphan*/  have_low_prio_scan; scalar_t__ set_qos_map_supported; int /*<<< orphan*/  p2p_go_ctwindow_supported; scalar_t__ error; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int WPA_DRIVER_AUTH_LEAP ; 
 int WPA_DRIVER_AUTH_OPEN ; 
 int WPA_DRIVER_AUTH_SHARED ; 
 int WPA_DRIVER_CAPA_KEY_MGMT_DPP ; 
 int WPA_DRIVER_CAPA_KEY_MGMT_FILS_SHA256 ; 
 int WPA_DRIVER_CAPA_KEY_MGMT_FILS_SHA384 ; 
 int WPA_DRIVER_CAPA_KEY_MGMT_FT_FILS_SHA256 ; 
 int WPA_DRIVER_CAPA_KEY_MGMT_FT_FILS_SHA384 ; 
 int WPA_DRIVER_CAPA_KEY_MGMT_OWE ; 
 int WPA_DRIVER_CAPA_KEY_MGMT_SAE ; 
 int WPA_DRIVER_CAPA_KEY_MGMT_SUITE_B ; 
 int WPA_DRIVER_CAPA_KEY_MGMT_SUITE_B_192 ; 
 int WPA_DRIVER_CAPA_KEY_MGMT_WPA ; 
 int WPA_DRIVER_CAPA_KEY_MGMT_WPA2 ; 
 int WPA_DRIVER_CAPA_KEY_MGMT_WPA2_PSK ; 
 int WPA_DRIVER_CAPA_KEY_MGMT_WPA_PSK ; 
 int WPA_DRIVER_FLAGS_AP_MLME ; 
 int WPA_DRIVER_FLAGS_AP_TEARDOWN_SUPPORT ; 
 int WPA_DRIVER_FLAGS_DEAUTH_TX_STATUS ; 
 int WPA_DRIVER_FLAGS_DFS_OFFLOAD ; 
 int WPA_DRIVER_FLAGS_EAPOL_TX_STATUS ; 
 int WPA_DRIVER_FLAGS_FILS_SK_OFFLOAD ; 
 int WPA_DRIVER_FLAGS_OFFCHANNEL_SIMULTANEOUS ; 
 int WPA_DRIVER_FLAGS_OFFCHANNEL_TX ; 
 int WPA_DRIVER_FLAGS_QOS_MAPPING ; 
 int WPA_DRIVER_FLAGS_SANE_ERROR_CODES ; 
 int WPA_DRIVER_FLAGS_SET_KEYS_AFTER_ASSOC_DONE ; 
 int WPA_DRIVER_FLAGS_SME ; 
 int /*<<< orphan*/  qca_nl80211_check_dfs_capa (struct wpa_driver_nl80211_data*) ; 
 int /*<<< orphan*/  qca_nl80211_get_akm_suites (struct wpa_driver_nl80211_data*) ; 
 int /*<<< orphan*/  qca_nl80211_get_features (struct wpa_driver_nl80211_data*) ; 
 scalar_t__ wpa_driver_nl80211_get_info (struct wpa_driver_nl80211_data*,struct wiphy_info_data*) ; 

int wpa_driver_nl80211_capa(struct wpa_driver_nl80211_data *drv)
{
	struct wiphy_info_data info;
	if (wpa_driver_nl80211_get_info(drv, &info))
		return -1;

	if (info.error)
		return -1;

	drv->has_capability = 1;
	drv->capa.key_mgmt = WPA_DRIVER_CAPA_KEY_MGMT_WPA |
		WPA_DRIVER_CAPA_KEY_MGMT_WPA_PSK |
		WPA_DRIVER_CAPA_KEY_MGMT_WPA2 |
		WPA_DRIVER_CAPA_KEY_MGMT_WPA2_PSK |
		WPA_DRIVER_CAPA_KEY_MGMT_SUITE_B |
		WPA_DRIVER_CAPA_KEY_MGMT_SUITE_B_192 |
		WPA_DRIVER_CAPA_KEY_MGMT_OWE |
		WPA_DRIVER_CAPA_KEY_MGMT_DPP;

	if (drv->capa.flags & WPA_DRIVER_FLAGS_SME)
		drv->capa.key_mgmt |= WPA_DRIVER_CAPA_KEY_MGMT_FILS_SHA256 |
			WPA_DRIVER_CAPA_KEY_MGMT_FILS_SHA384 |
			WPA_DRIVER_CAPA_KEY_MGMT_FT_FILS_SHA256 |
			WPA_DRIVER_CAPA_KEY_MGMT_FT_FILS_SHA384 |
			WPA_DRIVER_CAPA_KEY_MGMT_SAE;
	else if (drv->capa.flags & WPA_DRIVER_FLAGS_FILS_SK_OFFLOAD)
		drv->capa.key_mgmt |= WPA_DRIVER_CAPA_KEY_MGMT_FILS_SHA256 |
			WPA_DRIVER_CAPA_KEY_MGMT_FILS_SHA384;

#ifdef CONFIG_DRIVER_NL80211_QCA
	/* Override drv->capa.key_mgmt based on driver advertised capability
	 * constraints, if available. */
	qca_nl80211_get_akm_suites(drv);
#endif /* CONFIG_DRIVER_NL80211_QCA */

	drv->capa.auth = WPA_DRIVER_AUTH_OPEN |
		WPA_DRIVER_AUTH_SHARED |
		WPA_DRIVER_AUTH_LEAP;

	drv->capa.flags |= WPA_DRIVER_FLAGS_SANE_ERROR_CODES;
	drv->capa.flags |= WPA_DRIVER_FLAGS_SET_KEYS_AFTER_ASSOC_DONE;
	drv->capa.flags |= WPA_DRIVER_FLAGS_EAPOL_TX_STATUS;

	/*
	 * As all cfg80211 drivers must support cases where the AP interface is
	 * removed without the knowledge of wpa_supplicant/hostapd, e.g., in
	 * case that the user space daemon has crashed, they must be able to
	 * cleanup all stations and key entries in the AP tear down flow. Thus,
	 * this flag can/should always be set for cfg80211 drivers.
	 */
	drv->capa.flags |= WPA_DRIVER_FLAGS_AP_TEARDOWN_SUPPORT;

	if (!info.device_ap_sme) {
		drv->capa.flags |= WPA_DRIVER_FLAGS_DEAUTH_TX_STATUS;

		/*
		 * No AP SME is currently assumed to also indicate no AP MLME
		 * in the driver/firmware.
		 */
		drv->capa.flags |= WPA_DRIVER_FLAGS_AP_MLME;
	}

	drv->device_ap_sme = info.device_ap_sme;
	drv->poll_command_supported = info.poll_command_supported;
	drv->data_tx_status = info.data_tx_status;
	drv->p2p_go_ctwindow_supported = info.p2p_go_ctwindow_supported;
	if (info.set_qos_map_supported)
		drv->capa.flags |= WPA_DRIVER_FLAGS_QOS_MAPPING;
	drv->have_low_prio_scan = info.have_low_prio_scan;

	/*
	 * If poll command and tx status are supported, mac80211 is new enough
	 * to have everything we need to not need monitor interfaces.
	 */
	drv->use_monitor = !info.device_ap_sme &&
		(!info.poll_command_supported || !info.data_tx_status);

	/*
	 * If we aren't going to use monitor interfaces, but the
	 * driver doesn't support data TX status, we won't get TX
	 * status for EAPOL frames.
	 */
	if (!drv->use_monitor && !info.data_tx_status)
		drv->capa.flags &= ~WPA_DRIVER_FLAGS_EAPOL_TX_STATUS;

#ifdef CONFIG_DRIVER_NL80211_QCA
	if (!(info.capa->flags & WPA_DRIVER_FLAGS_DFS_OFFLOAD))
		qca_nl80211_check_dfs_capa(drv);
	qca_nl80211_get_features(drv);

	/*
	 * To enable offchannel simultaneous support in wpa_supplicant, the
	 * underlying driver needs to support the same along with offchannel TX.
	 * Offchannel TX support is needed since remain_on_channel and
	 * action_tx use some common data structures and hence cannot be
	 * scheduled simultaneously.
	 */
	if (!(drv->capa.flags & WPA_DRIVER_FLAGS_OFFCHANNEL_TX))
		drv->capa.flags &= ~WPA_DRIVER_FLAGS_OFFCHANNEL_SIMULTANEOUS;
#endif /* CONFIG_DRIVER_NL80211_QCA */

	return 0;
}