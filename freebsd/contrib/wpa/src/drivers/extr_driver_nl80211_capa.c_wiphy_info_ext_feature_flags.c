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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_driver_capa {int /*<<< orphan*/  flags; int /*<<< orphan*/  rrm_flags; } ;
struct wiphy_info_data {struct wpa_driver_capa* capa; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL80211_EXT_FEATURE_4WAY_HANDSHAKE_STA_1X ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_4WAY_HANDSHAKE_STA_PSK ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_ACCEPT_BCAST_PROBE_RESP ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_BEACON_RATE_HT ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_BEACON_RATE_LEGACY ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_BEACON_RATE_VHT ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_BSS_PARENT_TSF ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_DFS_OFFLOAD ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_ENABLE_FTM_RESPONDER ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_FILS_MAX_CHANNEL_TIME ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_FILS_SK_OFFLOAD ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_FILS_STA ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_MFP_OPTIONAL ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_MGMT_TX_RANDOM_TA ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_MGMT_TX_RANDOM_TA_CONNECTED ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_OCE_PROBE_REQ_DEFERRAL_SUPPRESSION ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_OCE_PROBE_REQ_HIGH_TX_RATE ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_RRM ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_SCAN_START_TIME ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_SCHED_SCAN_RELATIVE_RSSI ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_SET_SCAN_DWELL ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_VHT_IBSS ; 
 int /*<<< orphan*/  WPA_DRIVER_FLAGS_4WAY_HANDSHAKE_8021X ; 
 int /*<<< orphan*/  WPA_DRIVER_FLAGS_4WAY_HANDSHAKE_PSK ; 
 int /*<<< orphan*/  WPA_DRIVER_FLAGS_BEACON_RATE_HT ; 
 int /*<<< orphan*/  WPA_DRIVER_FLAGS_BEACON_RATE_LEGACY ; 
 int /*<<< orphan*/  WPA_DRIVER_FLAGS_BEACON_RATE_VHT ; 
 int /*<<< orphan*/  WPA_DRIVER_FLAGS_DFS_OFFLOAD ; 
 int /*<<< orphan*/  WPA_DRIVER_FLAGS_FILS_SK_OFFLOAD ; 
 int /*<<< orphan*/  WPA_DRIVER_FLAGS_FTM_RESPONDER ; 
 int /*<<< orphan*/  WPA_DRIVER_FLAGS_MFP_OPTIONAL ; 
 int /*<<< orphan*/  WPA_DRIVER_FLAGS_MGMT_TX_RANDOM_TA ; 
 int /*<<< orphan*/  WPA_DRIVER_FLAGS_MGMT_TX_RANDOM_TA_CONNECTED ; 
 int /*<<< orphan*/  WPA_DRIVER_FLAGS_OCE_STA ; 
 int /*<<< orphan*/  WPA_DRIVER_FLAGS_SCHED_SCAN_RELATIVE_RSSI ; 
 int /*<<< orphan*/  WPA_DRIVER_FLAGS_SUPPORT_BEACON_REPORT ; 
 int /*<<< orphan*/  WPA_DRIVER_FLAGS_SUPPORT_FILS ; 
 int /*<<< orphan*/  WPA_DRIVER_FLAGS_SUPPORT_RRM ; 
 int /*<<< orphan*/  WPA_DRIVER_FLAGS_SUPPORT_SET_SCAN_DWELL ; 
 int /*<<< orphan*/  WPA_DRIVER_FLAGS_VHT_IBSS ; 
 scalar_t__ ext_feature_isset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nla_data (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 

__attribute__((used)) static void wiphy_info_ext_feature_flags(struct wiphy_info_data *info,
					 struct nlattr *tb)
{
	struct wpa_driver_capa *capa = info->capa;
	u8 *ext_features;
	int len;

	if (tb == NULL)
		return;

	ext_features = nla_data(tb);
	len = nla_len(tb);

	if (ext_feature_isset(ext_features, len, NL80211_EXT_FEATURE_VHT_IBSS))
		capa->flags |= WPA_DRIVER_FLAGS_VHT_IBSS;

	if (ext_feature_isset(ext_features, len, NL80211_EXT_FEATURE_RRM))
		capa->rrm_flags |= WPA_DRIVER_FLAGS_SUPPORT_RRM;

	if (ext_feature_isset(ext_features, len, NL80211_EXT_FEATURE_FILS_STA))
		capa->flags |= WPA_DRIVER_FLAGS_SUPPORT_FILS;

	if (ext_feature_isset(ext_features, len,
			      NL80211_EXT_FEATURE_BEACON_RATE_LEGACY))
		capa->flags |= WPA_DRIVER_FLAGS_BEACON_RATE_LEGACY;

	if (ext_feature_isset(ext_features, len,
			      NL80211_EXT_FEATURE_BEACON_RATE_HT))
		capa->flags |= WPA_DRIVER_FLAGS_BEACON_RATE_HT;

	if (ext_feature_isset(ext_features, len,
			      NL80211_EXT_FEATURE_BEACON_RATE_VHT))
		capa->flags |= WPA_DRIVER_FLAGS_BEACON_RATE_VHT;

	if (ext_feature_isset(ext_features, len,
			      NL80211_EXT_FEATURE_SET_SCAN_DWELL))
		capa->rrm_flags |= WPA_DRIVER_FLAGS_SUPPORT_SET_SCAN_DWELL;

	if (ext_feature_isset(ext_features, len,
			      NL80211_EXT_FEATURE_SCAN_START_TIME) &&
	    ext_feature_isset(ext_features, len,
			      NL80211_EXT_FEATURE_BSS_PARENT_TSF) &&
	    ext_feature_isset(ext_features, len,
			      NL80211_EXT_FEATURE_SET_SCAN_DWELL))
		capa->rrm_flags |= WPA_DRIVER_FLAGS_SUPPORT_BEACON_REPORT;
	if (ext_feature_isset(ext_features, len,
			      NL80211_EXT_FEATURE_MGMT_TX_RANDOM_TA))
		capa->flags |= WPA_DRIVER_FLAGS_MGMT_TX_RANDOM_TA;
	if (ext_feature_isset(ext_features, len,
			      NL80211_EXT_FEATURE_MGMT_TX_RANDOM_TA_CONNECTED))
		capa->flags |= WPA_DRIVER_FLAGS_MGMT_TX_RANDOM_TA_CONNECTED;
	if (ext_feature_isset(ext_features, len,
			      NL80211_EXT_FEATURE_SCHED_SCAN_RELATIVE_RSSI))
		capa->flags |= WPA_DRIVER_FLAGS_SCHED_SCAN_RELATIVE_RSSI;
	if (ext_feature_isset(ext_features, len,
			      NL80211_EXT_FEATURE_FILS_SK_OFFLOAD))
		capa->flags |= WPA_DRIVER_FLAGS_FILS_SK_OFFLOAD;

	if (ext_feature_isset(ext_features, len,
			      NL80211_EXT_FEATURE_4WAY_HANDSHAKE_STA_PSK))
		capa->flags |= WPA_DRIVER_FLAGS_4WAY_HANDSHAKE_PSK;
	if (ext_feature_isset(ext_features, len,
			      NL80211_EXT_FEATURE_4WAY_HANDSHAKE_STA_1X))
		capa->flags |= WPA_DRIVER_FLAGS_4WAY_HANDSHAKE_8021X;

	if (ext_feature_isset(ext_features, len,
			      NL80211_EXT_FEATURE_MFP_OPTIONAL))
		capa->flags |= WPA_DRIVER_FLAGS_MFP_OPTIONAL;

	if (ext_feature_isset(ext_features, len,
			      NL80211_EXT_FEATURE_DFS_OFFLOAD))
		capa->flags |= WPA_DRIVER_FLAGS_DFS_OFFLOAD;

#ifdef CONFIG_MBO
	if (ext_feature_isset(ext_features, len,
			      NL80211_EXT_FEATURE_FILS_MAX_CHANNEL_TIME) &&
	    ext_feature_isset(ext_features, len,
			      NL80211_EXT_FEATURE_ACCEPT_BCAST_PROBE_RESP) &&
	    ext_feature_isset(ext_features, len,
			      NL80211_EXT_FEATURE_OCE_PROBE_REQ_HIGH_TX_RATE) &&
	    ext_feature_isset(
		    ext_features, len,
		    NL80211_EXT_FEATURE_OCE_PROBE_REQ_DEFERRAL_SUPPRESSION))
		capa->flags |= WPA_DRIVER_FLAGS_OCE_STA;
#endif /* CONFIG_MBO */

	if (ext_feature_isset(ext_features, len,
			      NL80211_EXT_FEATURE_ENABLE_FTM_RESPONDER))
		capa->flags |= WPA_DRIVER_FLAGS_FTM_RESPONDER;
}