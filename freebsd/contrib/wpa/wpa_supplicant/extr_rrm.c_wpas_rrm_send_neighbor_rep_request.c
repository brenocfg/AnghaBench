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
typedef  int u8 ;
struct wpabuf {int dummy; } ;
struct TYPE_4__ {void (* notify_neighbor_rep ) (void*,struct wpabuf*) ;int next_neighbor_rep_token; void* neighbor_rep_cb_ctx; int /*<<< orphan*/  rrm_used; } ;
struct wpa_supplicant {scalar_t__ wpa_state; TYPE_2__ rrm; int /*<<< orphan*/  bssid; int /*<<< orphan*/  own_addr; int /*<<< orphan*/  assoc_freq; TYPE_1__* current_bss; int /*<<< orphan*/ * current_ssid; } ;
struct wpa_ssid_value {int ssid_len; int /*<<< orphan*/  ssid; } ;
struct TYPE_3__ {int caps; } ;

/* Variables and functions */
 int EBUSY ; 
 int ECANCELED ; 
 int ENOMEM ; 
 int ENOTCONN ; 
 int EOPNOTSUPP ; 
 int IEEE80211_CAP_RRM ; 
 int LCI_REQ_SUBELEM_MAX_AGE ; 
 int LOCATION_SUBJECT_REMOTE ; 
 int MEASURE_REQUEST_CIVIC_LEN ; 
 int MEASURE_REQUEST_LCI_LEN ; 
 int MEASURE_TYPE_LCI ; 
 int MEASURE_TYPE_LOCATION_CIVIC ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  RRM_NEIGHBOR_REPORT_TIMEOUT ; 
 int WLAN_ACTION_RADIO_MEASUREMENT ; 
 int WLAN_EID_MEASURE_REQUEST ; 
 int /*<<< orphan*/  WLAN_EID_RRM_ENABLED_CAPABILITIES ; 
 int WLAN_EID_SSID ; 
 int const WLAN_RRM_CAPS_NEIGHBOR_REPORT ; 
 int WLAN_RRM_NEIGHBOR_REPORT_REQUEST ; 
 scalar_t__ WPA_COMPLETED ; 
 int /*<<< orphan*/  eloop_register_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int* wpa_bss_get_ie (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_drv_send_action (struct wpa_supplicant*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 char* wpa_ssid_txt (int /*<<< orphan*/ ,int) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpabuf_put_le16 (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpas_rrm_neighbor_rep_timeout_handler ; 

int wpas_rrm_send_neighbor_rep_request(struct wpa_supplicant *wpa_s,
				       const struct wpa_ssid_value *ssid,
				       int lci, int civic,
				       void (*cb)(void *ctx,
						  struct wpabuf *neighbor_rep),
				       void *cb_ctx)
{
	struct wpabuf *buf;
	const u8 *rrm_ie;

	if (wpa_s->wpa_state != WPA_COMPLETED || wpa_s->current_ssid == NULL) {
		wpa_printf(MSG_DEBUG, "RRM: No connection, no RRM.");
		return -ENOTCONN;
	}

	if (!wpa_s->rrm.rrm_used) {
		wpa_printf(MSG_DEBUG, "RRM: No RRM in current connection.");
		return -EOPNOTSUPP;
	}

	rrm_ie = wpa_bss_get_ie(wpa_s->current_bss,
				WLAN_EID_RRM_ENABLED_CAPABILITIES);
	if (!rrm_ie || !(wpa_s->current_bss->caps & IEEE80211_CAP_RRM) ||
	    !(rrm_ie[2] & WLAN_RRM_CAPS_NEIGHBOR_REPORT)) {
		wpa_printf(MSG_DEBUG,
			   "RRM: No network support for Neighbor Report.");
		return -EOPNOTSUPP;
	}

	/* Refuse if there's a live request */
	if (wpa_s->rrm.notify_neighbor_rep) {
		wpa_printf(MSG_DEBUG,
			   "RRM: Currently handling previous Neighbor Report.");
		return -EBUSY;
	}

	/* 3 = action category + action code + dialog token */
	buf = wpabuf_alloc(3 + (ssid ? 2 + ssid->ssid_len : 0) +
			   (lci ? 2 + MEASURE_REQUEST_LCI_LEN : 0) +
			   (civic ? 2 + MEASURE_REQUEST_CIVIC_LEN : 0));
	if (buf == NULL) {
		wpa_printf(MSG_DEBUG,
			   "RRM: Failed to allocate Neighbor Report Request");
		return -ENOMEM;
	}

	wpa_printf(MSG_DEBUG, "RRM: Neighbor report request (for %s), token=%d",
		   (ssid ? wpa_ssid_txt(ssid->ssid, ssid->ssid_len) : ""),
		   wpa_s->rrm.next_neighbor_rep_token);

	wpabuf_put_u8(buf, WLAN_ACTION_RADIO_MEASUREMENT);
	wpabuf_put_u8(buf, WLAN_RRM_NEIGHBOR_REPORT_REQUEST);
	wpabuf_put_u8(buf, wpa_s->rrm.next_neighbor_rep_token);
	if (ssid) {
		wpabuf_put_u8(buf, WLAN_EID_SSID);
		wpabuf_put_u8(buf, ssid->ssid_len);
		wpabuf_put_data(buf, ssid->ssid, ssid->ssid_len);
	}

	if (lci) {
		/* IEEE P802.11-REVmc/D5.0 9.4.2.21 */
		wpabuf_put_u8(buf, WLAN_EID_MEASURE_REQUEST);
		wpabuf_put_u8(buf, MEASURE_REQUEST_LCI_LEN);

		/*
		 * Measurement token; nonzero number that is unique among the
		 * Measurement Request elements in a particular frame.
		 */
		wpabuf_put_u8(buf, 1); /* Measurement Token */

		/*
		 * Parallel, Enable, Request, and Report bits are 0, Duration is
		 * reserved.
		 */
		wpabuf_put_u8(buf, 0); /* Measurement Request Mode */
		wpabuf_put_u8(buf, MEASURE_TYPE_LCI); /* Measurement Type */

		/* IEEE P802.11-REVmc/D5.0 9.4.2.21.10 - LCI request */
		/* Location Subject */
		wpabuf_put_u8(buf, LOCATION_SUBJECT_REMOTE);

		/* Optional Subelements */
		/*
		 * IEEE P802.11-REVmc/D5.0 Figure 9-170
		 * The Maximum Age subelement is required, otherwise the AP can
		 * send only data that was determined after receiving the
		 * request. Setting it here to unlimited age.
		 */
		wpabuf_put_u8(buf, LCI_REQ_SUBELEM_MAX_AGE);
		wpabuf_put_u8(buf, 2);
		wpabuf_put_le16(buf, 0xffff);
	}

	if (civic) {
		/* IEEE P802.11-REVmc/D5.0 9.4.2.21 */
		wpabuf_put_u8(buf, WLAN_EID_MEASURE_REQUEST);
		wpabuf_put_u8(buf, MEASURE_REQUEST_CIVIC_LEN);

		/*
		 * Measurement token; nonzero number that is unique among the
		 * Measurement Request elements in a particular frame.
		 */
		wpabuf_put_u8(buf, 2); /* Measurement Token */

		/*
		 * Parallel, Enable, Request, and Report bits are 0, Duration is
		 * reserved.
		 */
		wpabuf_put_u8(buf, 0); /* Measurement Request Mode */
		/* Measurement Type */
		wpabuf_put_u8(buf, MEASURE_TYPE_LOCATION_CIVIC);

		/* IEEE P802.11-REVmc/D5.0 9.4.2.21.14:
		 * Location Civic request */
		/* Location Subject */
		wpabuf_put_u8(buf, LOCATION_SUBJECT_REMOTE);
		wpabuf_put_u8(buf, 0); /* Civic Location Type: IETF RFC 4776 */
		/* Location Service Interval Units: Seconds */
		wpabuf_put_u8(buf, 0);
		/* Location Service Interval: 0 - Only one report is requested
		 */
		wpabuf_put_le16(buf, 0);
		/* No optional subelements */
	}

	wpa_s->rrm.next_neighbor_rep_token++;

	if (wpa_drv_send_action(wpa_s, wpa_s->assoc_freq, 0, wpa_s->bssid,
				wpa_s->own_addr, wpa_s->bssid,
				wpabuf_head(buf), wpabuf_len(buf), 0) < 0) {
		wpa_printf(MSG_DEBUG,
			   "RRM: Failed to send Neighbor Report Request");
		wpabuf_free(buf);
		return -ECANCELED;
	}

	wpa_s->rrm.neighbor_rep_cb_ctx = cb_ctx;
	wpa_s->rrm.notify_neighbor_rep = cb;
	eloop_register_timeout(RRM_NEIGHBOR_REPORT_TIMEOUT, 0,
			       wpas_rrm_neighbor_rep_timeout_handler,
			       &wpa_s->rrm, NULL);

	wpabuf_free(buf);
	return 0;
}