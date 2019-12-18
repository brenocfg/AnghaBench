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
typedef  int u32 ;
struct wpa_driver_nl80211_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
#define  QCA_NL80211_VENDOR_SUBCMD_AVOID_FREQUENCY 139 
#define  QCA_NL80211_VENDOR_SUBCMD_DFS_OFFLOAD_CAC_ABORTED 138 
#define  QCA_NL80211_VENDOR_SUBCMD_DFS_OFFLOAD_CAC_FINISHED 137 
#define  QCA_NL80211_VENDOR_SUBCMD_DFS_OFFLOAD_CAC_NOP_FINISHED 136 
#define  QCA_NL80211_VENDOR_SUBCMD_DFS_OFFLOAD_CAC_STARTED 135 
#define  QCA_NL80211_VENDOR_SUBCMD_DFS_OFFLOAD_RADAR_DETECTED 134 
#define  QCA_NL80211_VENDOR_SUBCMD_DO_ACS 133 
#define  QCA_NL80211_VENDOR_SUBCMD_KEY_MGMT_ROAM_AUTH 132 
#define  QCA_NL80211_VENDOR_SUBCMD_P2P_LISTEN_OFFLOAD_STOP 131 
#define  QCA_NL80211_VENDOR_SUBCMD_SCAN_DONE 130 
#define  QCA_NL80211_VENDOR_SUBCMD_TEST 129 
#define  QCA_NL80211_VENDOR_SUBCMD_TRIGGER_SCAN 128 
 int /*<<< orphan*/  qca_nl80211_acs_select_ch (struct wpa_driver_nl80211_data*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  qca_nl80211_avoid_freq (struct wpa_driver_nl80211_data*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  qca_nl80211_dfs_offload_radar_event (struct wpa_driver_nl80211_data*,int,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  qca_nl80211_key_mgmt_auth (struct wpa_driver_nl80211_data*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  qca_nl80211_p2p_lo_stop_event (struct wpa_driver_nl80211_data*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  qca_nl80211_scan_done_event (struct wpa_driver_nl80211_data*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  qca_nl80211_scan_trigger_event (struct wpa_driver_nl80211_data*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void nl80211_vendor_event_qca(struct wpa_driver_nl80211_data *drv,
				     u32 subcmd, u8 *data, size_t len)
{
	switch (subcmd) {
	case QCA_NL80211_VENDOR_SUBCMD_TEST:
		wpa_hexdump(MSG_DEBUG, "nl80211: QCA test event", data, len);
		break;
#ifdef CONFIG_DRIVER_NL80211_QCA
	case QCA_NL80211_VENDOR_SUBCMD_AVOID_FREQUENCY:
		qca_nl80211_avoid_freq(drv, data, len);
		break;
	case QCA_NL80211_VENDOR_SUBCMD_KEY_MGMT_ROAM_AUTH:
		qca_nl80211_key_mgmt_auth(drv, data, len);
		break;
	case QCA_NL80211_VENDOR_SUBCMD_DO_ACS:
		qca_nl80211_acs_select_ch(drv, data, len);
		break;
	case QCA_NL80211_VENDOR_SUBCMD_DFS_OFFLOAD_CAC_STARTED:
	case QCA_NL80211_VENDOR_SUBCMD_DFS_OFFLOAD_CAC_FINISHED:
	case QCA_NL80211_VENDOR_SUBCMD_DFS_OFFLOAD_CAC_ABORTED:
	case QCA_NL80211_VENDOR_SUBCMD_DFS_OFFLOAD_CAC_NOP_FINISHED:
	case QCA_NL80211_VENDOR_SUBCMD_DFS_OFFLOAD_RADAR_DETECTED:
		qca_nl80211_dfs_offload_radar_event(drv, subcmd, data, len);
		break;
	case QCA_NL80211_VENDOR_SUBCMD_TRIGGER_SCAN:
		qca_nl80211_scan_trigger_event(drv, data, len);
		break;
	case QCA_NL80211_VENDOR_SUBCMD_SCAN_DONE:
		qca_nl80211_scan_done_event(drv, data, len);
		break;
	case QCA_NL80211_VENDOR_SUBCMD_P2P_LISTEN_OFFLOAD_STOP:
		qca_nl80211_p2p_lo_stop_event(drv, data, len);
		break;
#endif /* CONFIG_DRIVER_NL80211_QCA */
	default:
		wpa_printf(MSG_DEBUG,
			   "nl80211: Ignore unsupported QCA vendor event %u",
			   subcmd);
		break;
	}
}