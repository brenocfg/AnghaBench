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
typedef  int u32 ;
struct wpa_driver_capa {int /*<<< orphan*/  flags; int /*<<< orphan*/  rrm_flags; int /*<<< orphan*/  smps_modes; } ;
struct wiphy_info_data {int data_tx_status; int p2p_go_ctwindow_supported; int have_low_prio_scan; int mac_addr_rand_scan_supported; int mac_addr_rand_sched_scan_supported; int wmm_ac_supported; struct wpa_driver_capa* capa; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int NL80211_FEATURE_AP_MODE_CHAN_WIDTH_CHANGE ; 
 int NL80211_FEATURE_DS_PARAM_SET_IE_IN_PROBES ; 
 int NL80211_FEATURE_DYNAMIC_SMPS ; 
 int NL80211_FEATURE_FULL_AP_CLIENT_STATE ; 
 int NL80211_FEATURE_HT_IBSS ; 
 int NL80211_FEATURE_INACTIVITY_TIMER ; 
 int NL80211_FEATURE_LOW_PRIORITY_SCAN ; 
 int NL80211_FEATURE_NEED_OBSS_SCAN ; 
 int NL80211_FEATURE_P2P_GO_CTWIN ; 
 int NL80211_FEATURE_QUIET ; 
 int NL80211_FEATURE_SAE ; 
 int NL80211_FEATURE_SCAN_RANDOM_MAC_ADDR ; 
 int NL80211_FEATURE_SCHED_SCAN_RANDOM_MAC_ADDR ; 
 int NL80211_FEATURE_SK_TX_STATUS ; 
 int NL80211_FEATURE_STATIC_SMPS ; 
 int NL80211_FEATURE_SUPPORTS_WMM_ADMISSION ; 
 int NL80211_FEATURE_TDLS_CHANNEL_SWITCH ; 
 int NL80211_FEATURE_TX_POWER_INSERTION ; 
 int NL80211_FEATURE_WFA_TPC_IE_IN_PROBES ; 
 int /*<<< orphan*/  WPA_DRIVER_FLAGS_DS_PARAM_SET_IE_IN_PROBES ; 
 int /*<<< orphan*/  WPA_DRIVER_FLAGS_FULL_AP_CLIENT_STATE ; 
 int /*<<< orphan*/  WPA_DRIVER_FLAGS_HT_2040_COEX ; 
 int /*<<< orphan*/  WPA_DRIVER_FLAGS_HT_IBSS ; 
 int /*<<< orphan*/  WPA_DRIVER_FLAGS_INACTIVITY_TIMER ; 
 int /*<<< orphan*/  WPA_DRIVER_FLAGS_OBSS_SCAN ; 
 int /*<<< orphan*/  WPA_DRIVER_FLAGS_QUIET ; 
 int /*<<< orphan*/  WPA_DRIVER_FLAGS_SAE ; 
 int /*<<< orphan*/  WPA_DRIVER_FLAGS_TDLS_CHANNEL_SWITCH ; 
 int /*<<< orphan*/  WPA_DRIVER_FLAGS_TX_POWER_INSERTION ; 
 int /*<<< orphan*/  WPA_DRIVER_FLAGS_WFA_TPC_IE_IN_PROBES ; 
 int /*<<< orphan*/  WPA_DRIVER_SMPS_MODE_DYNAMIC ; 
 int /*<<< orphan*/  WPA_DRIVER_SMPS_MODE_STATIC ; 
 int nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void wiphy_info_feature_flags(struct wiphy_info_data *info,
				     struct nlattr *tb)
{
	u32 flags;
	struct wpa_driver_capa *capa = info->capa;

	if (tb == NULL)
		return;

	flags = nla_get_u32(tb);

	if (flags & NL80211_FEATURE_SK_TX_STATUS)
		info->data_tx_status = 1;

	if (flags & NL80211_FEATURE_INACTIVITY_TIMER)
		capa->flags |= WPA_DRIVER_FLAGS_INACTIVITY_TIMER;

	if (flags & NL80211_FEATURE_SAE)
		capa->flags |= WPA_DRIVER_FLAGS_SAE;

	if (flags & NL80211_FEATURE_NEED_OBSS_SCAN)
		capa->flags |= WPA_DRIVER_FLAGS_OBSS_SCAN;

	if (flags & NL80211_FEATURE_AP_MODE_CHAN_WIDTH_CHANGE)
		capa->flags |= WPA_DRIVER_FLAGS_HT_2040_COEX;

	if (flags & NL80211_FEATURE_TDLS_CHANNEL_SWITCH) {
		wpa_printf(MSG_DEBUG, "nl80211: TDLS channel switch");
		capa->flags |= WPA_DRIVER_FLAGS_TDLS_CHANNEL_SWITCH;
	}

	if (flags & NL80211_FEATURE_P2P_GO_CTWIN)
		info->p2p_go_ctwindow_supported = 1;

	if (flags & NL80211_FEATURE_LOW_PRIORITY_SCAN)
		info->have_low_prio_scan = 1;

	if (flags & NL80211_FEATURE_SCAN_RANDOM_MAC_ADDR)
		info->mac_addr_rand_scan_supported = 1;

	if (flags & NL80211_FEATURE_SCHED_SCAN_RANDOM_MAC_ADDR)
		info->mac_addr_rand_sched_scan_supported = 1;

	if (flags & NL80211_FEATURE_STATIC_SMPS)
		capa->smps_modes |= WPA_DRIVER_SMPS_MODE_STATIC;

	if (flags & NL80211_FEATURE_DYNAMIC_SMPS)
		capa->smps_modes |= WPA_DRIVER_SMPS_MODE_DYNAMIC;

	if (flags & NL80211_FEATURE_SUPPORTS_WMM_ADMISSION)
		info->wmm_ac_supported = 1;

	if (flags & NL80211_FEATURE_DS_PARAM_SET_IE_IN_PROBES)
		capa->rrm_flags |= WPA_DRIVER_FLAGS_DS_PARAM_SET_IE_IN_PROBES;

	if (flags & NL80211_FEATURE_WFA_TPC_IE_IN_PROBES)
		capa->rrm_flags |= WPA_DRIVER_FLAGS_WFA_TPC_IE_IN_PROBES;

	if (flags & NL80211_FEATURE_QUIET)
		capa->rrm_flags |= WPA_DRIVER_FLAGS_QUIET;

	if (flags & NL80211_FEATURE_TX_POWER_INSERTION)
		capa->rrm_flags |= WPA_DRIVER_FLAGS_TX_POWER_INSERTION;

	if (flags & NL80211_FEATURE_HT_IBSS)
		capa->flags |= WPA_DRIVER_FLAGS_HT_IBSS;

	if (flags & NL80211_FEATURE_FULL_AP_CLIENT_STATE)
		capa->flags |= WPA_DRIVER_FLAGS_FULL_AP_CLIENT_STATE;
}