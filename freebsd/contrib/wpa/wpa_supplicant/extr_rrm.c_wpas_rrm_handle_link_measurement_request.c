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
struct wpabuf {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  rrm_used; } ;
struct wpa_supplicant {scalar_t__ wpa_state; int drv_rrm_flags; int /*<<< orphan*/  bssid; int /*<<< orphan*/  own_addr; int /*<<< orphan*/  assoc_freq; TYPE_1__ rrm; } ;
struct rrm_link_measurement_request {int /*<<< orphan*/  dialog_token; } ;
struct TYPE_4__ {int len; int /*<<< orphan*/  eid; } ;
struct rrm_link_measurement_report {int rsni; int /*<<< orphan*/  rcpi; TYPE_2__ tpc; int /*<<< orphan*/  dialog_token; } ;
typedef  int /*<<< orphan*/  report ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  WLAN_ACTION_RADIO_MEASUREMENT ; 
 int /*<<< orphan*/  WLAN_EID_TPC_REPORT ; 
 int /*<<< orphan*/  WLAN_RRM_LINK_MEASUREMENT_REPORT ; 
 scalar_t__ WPA_COMPLETED ; 
 int WPA_DRIVER_FLAGS_TX_POWER_INSERTION ; 
 int /*<<< orphan*/  os_memset (struct rrm_link_measurement_report*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rssi_to_rcpi (int) ; 
 scalar_t__ wpa_drv_send_action (struct wpa_supplicant*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_buf (int /*<<< orphan*/ ,char*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,struct rrm_link_measurement_report*,int) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int /*<<< orphan*/ ) ; 

void wpas_rrm_handle_link_measurement_request(struct wpa_supplicant *wpa_s,
					      const u8 *src,
					      const u8 *frame, size_t len,
					      int rssi)
{
	struct wpabuf *buf;
	const struct rrm_link_measurement_request *req;
	struct rrm_link_measurement_report report;

	if (wpa_s->wpa_state != WPA_COMPLETED) {
		wpa_printf(MSG_INFO,
			   "RRM: Ignoring link measurement request. Not associated");
		return;
	}

	if (!wpa_s->rrm.rrm_used) {
		wpa_printf(MSG_INFO,
			   "RRM: Ignoring link measurement request. Not RRM network");
		return;
	}

	if (!(wpa_s->drv_rrm_flags & WPA_DRIVER_FLAGS_TX_POWER_INSERTION)) {
		wpa_printf(MSG_INFO,
			   "RRM: Measurement report failed. TX power insertion not supported");
		return;
	}

	req = (const struct rrm_link_measurement_request *) frame;
	if (len < sizeof(*req)) {
		wpa_printf(MSG_INFO,
			   "RRM: Link measurement report failed. Request too short");
		return;
	}

	os_memset(&report, 0, sizeof(report));
	report.dialog_token = req->dialog_token;
	report.tpc.eid = WLAN_EID_TPC_REPORT;
	report.tpc.len = 2;
	/* Note: The driver is expected to update report.tpc.tx_power and
	 * report.tpc.link_margin subfields when sending out this frame.
	 * Similarly, the driver would need to update report.rx_ant_id and
	 * report.tx_ant_id subfields. */
	report.rsni = 255; /* 255 indicates that RSNI is not available */
	report.rcpi = rssi_to_rcpi(rssi);

	/* action_category + action_code */
	buf = wpabuf_alloc(2 + sizeof(report));
	if (buf == NULL) {
		wpa_printf(MSG_ERROR,
			   "RRM: Link measurement report failed. Buffer allocation failed");
		return;
	}

	wpabuf_put_u8(buf, WLAN_ACTION_RADIO_MEASUREMENT);
	wpabuf_put_u8(buf, WLAN_RRM_LINK_MEASUREMENT_REPORT);
	wpabuf_put_data(buf, &report, sizeof(report));
	wpa_hexdump_buf(MSG_DEBUG, "RRM: Link measurement report", buf);

	if (wpa_drv_send_action(wpa_s, wpa_s->assoc_freq, 0, src,
				wpa_s->own_addr, wpa_s->bssid,
				wpabuf_head(buf), wpabuf_len(buf), 0)) {
		wpa_printf(MSG_ERROR,
			   "RRM: Link measurement report failed. Send action failed");
	}
	wpabuf_free(buf);
}