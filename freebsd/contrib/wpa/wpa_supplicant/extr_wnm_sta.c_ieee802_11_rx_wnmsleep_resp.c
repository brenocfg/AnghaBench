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
typedef  int u8 ;
typedef  size_t u16 ;
struct wpa_supplicant {int /*<<< orphan*/  bssid; scalar_t__ wnmsleep_used; int /*<<< orphan*/  wpa; } ;
struct wpa_channel_info {int /*<<< orphan*/  seg1_idx; int /*<<< orphan*/  chanwidth; } ;
struct wnm_sleep_element {int const action_type; scalar_t__ status; size_t intval; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int const WLAN_EID_EXTENSION ; 
 int const WLAN_EID_EXT_OCV_OCI ; 
 int const WLAN_EID_TFS_RESP ; 
 int const WLAN_EID_WNMSLEEP ; 
 int /*<<< orphan*/  WNM_SLEEP_ENTER_FAIL ; 
 int /*<<< orphan*/  WNM_SLEEP_EXIT_FAIL ; 
 int const WNM_SLEEP_MODE_ENTER ; 
 int const WNM_SLEEP_MODE_EXIT ; 
 scalar_t__ WNM_STATUS_SLEEP_ACCEPT ; 
 scalar_t__ WNM_STATUS_SLEEP_EXIT_ACCEPT_GTK_UPDATE ; 
 size_t WPA_GET_LE16 (int const*) ; 
 int /*<<< orphan*/  channel_width_to_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocv_errorstr ; 
 scalar_t__ ocv_verify_tx_params (int const*,int,struct wpa_channel_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wnm_sleep_mode_enter_success (struct wpa_supplicant*,int const*,int const*) ; 
 int /*<<< orphan*/  wnm_sleep_mode_exit_success (struct wpa_supplicant*,int const*,size_t) ; 
 scalar_t__ wpa_drv_channel_info (struct wpa_supplicant*,struct wpa_channel_info*) ; 
 int /*<<< orphan*/  wpa_drv_wnm_oper (struct wpa_supplicant*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int const*,int) ; 
 int /*<<< orphan*/  wpa_msg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ wpa_sm_ocv_enabled (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ieee802_11_rx_wnmsleep_resp(struct wpa_supplicant *wpa_s,
					const u8 *frm, int len)
{
	/*
	 * Action [1] | Dialog Token [1] | Key Data Len [2] | Key Data |
	 * WNM-Sleep Mode IE | TFS Response IE
	 */
	const u8 *pos = frm; /* point to payload after the action field */
	u16 key_len_total;
	struct wnm_sleep_element *wnmsleep_ie = NULL;
	/* multiple TFS Resp IE (assuming consecutive) */
	const u8 *tfsresp_ie_start = NULL;
	const u8 *tfsresp_ie_end = NULL;
#ifdef CONFIG_OCV
	const u8 *oci_ie = NULL;
	u8 oci_ie_len = 0;
#endif /* CONFIG_OCV */
	size_t left;

	if (!wpa_s->wnmsleep_used) {
		wpa_printf(MSG_DEBUG,
			   "WNM: Ignore WNM-Sleep Mode Response frame since WNM-Sleep Mode operation has not been requested");
		return;
	}

	if (len < 3)
		return;
	key_len_total = WPA_GET_LE16(frm + 1);

	wpa_printf(MSG_DEBUG, "WNM-Sleep Mode Response token=%u key_len_total=%d",
		   frm[0], key_len_total);
	left = len - 3;
	if (key_len_total > left) {
		wpa_printf(MSG_INFO, "WNM: Too short frame for Key Data field");
		return;
	}
	pos += 3 + key_len_total;
	while (pos - frm + 1 < len) {
		u8 ie_len = *(pos + 1);
		if (2 + ie_len > frm + len - pos) {
			wpa_printf(MSG_INFO, "WNM: Invalid IE len %u", ie_len);
			break;
		}
		wpa_hexdump(MSG_DEBUG, "WNM: Element", pos, 2 + ie_len);
		if (*pos == WLAN_EID_WNMSLEEP && ie_len >= 4)
			wnmsleep_ie = (struct wnm_sleep_element *) pos;
		else if (*pos == WLAN_EID_TFS_RESP) {
			if (!tfsresp_ie_start)
				tfsresp_ie_start = pos;
			tfsresp_ie_end = pos;
#ifdef CONFIG_OCV
		} else if (*pos == WLAN_EID_EXTENSION && ie_len >= 1 &&
			   pos[2] == WLAN_EID_EXT_OCV_OCI) {
			oci_ie = pos + 3;
			oci_ie_len = ie_len - 1;
#endif /* CONFIG_OCV */
		} else
			wpa_printf(MSG_DEBUG, "EID %d not recognized", *pos);
		pos += ie_len + 2;
	}

	if (!wnmsleep_ie) {
		wpa_printf(MSG_DEBUG, "No WNM-Sleep IE found");
		return;
	}

#ifdef CONFIG_OCV
	if (wnmsleep_ie->action_type == WNM_SLEEP_MODE_EXIT &&
	    wpa_sm_ocv_enabled(wpa_s->wpa)) {
		struct wpa_channel_info ci;

		if (wpa_drv_channel_info(wpa_s, &ci) != 0) {
			wpa_msg(wpa_s, MSG_WARNING,
				"Failed to get channel info to validate received OCI in WNM-Sleep Mode frame");
			return;
		}

		if (ocv_verify_tx_params(oci_ie, oci_ie_len, &ci,
					 channel_width_to_int(ci.chanwidth),
					 ci.seg1_idx) != 0) {
			wpa_msg(wpa_s, MSG_WARNING, "WNM: %s", ocv_errorstr);
			return;
		}
	}
#endif /* CONFIG_OCV */

	wpa_s->wnmsleep_used = 0;

	if (wnmsleep_ie->status == WNM_STATUS_SLEEP_ACCEPT ||
	    wnmsleep_ie->status == WNM_STATUS_SLEEP_EXIT_ACCEPT_GTK_UPDATE) {
		wpa_printf(MSG_DEBUG, "Successfully recv WNM-Sleep Response "
			   "frame (action=%d, intval=%d)",
			   wnmsleep_ie->action_type, wnmsleep_ie->intval);
		if (wnmsleep_ie->action_type == WNM_SLEEP_MODE_ENTER) {
			wnm_sleep_mode_enter_success(wpa_s, tfsresp_ie_start,
						     tfsresp_ie_end);
		} else if (wnmsleep_ie->action_type == WNM_SLEEP_MODE_EXIT) {
			wnm_sleep_mode_exit_success(wpa_s, frm, key_len_total);
		}
	} else {
		wpa_printf(MSG_DEBUG, "Reject recv WNM-Sleep Response frame "
			   "(action=%d, intval=%d)",
			   wnmsleep_ie->action_type, wnmsleep_ie->intval);
		if (wnmsleep_ie->action_type == WNM_SLEEP_MODE_ENTER)
			wpa_drv_wnm_oper(wpa_s, WNM_SLEEP_ENTER_FAIL,
					 wpa_s->bssid, NULL, NULL);
		else if (wnmsleep_ie->action_type == WNM_SLEEP_MODE_EXIT)
			wpa_drv_wnm_oper(wpa_s, WNM_SLEEP_EXIT_FAIL,
					 wpa_s->bssid, NULL, NULL);
	}
}