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
struct wpabuf {int dummy; } ;
struct sta_info {int flags; int* rrm_enabled_capa; } ;
struct hostapd_data {int lci_req_active; int lci_req_token; TYPE_1__* iface; } ;
struct TYPE_2__ {int /*<<< orphan*/  freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOSTAPD_RRM_REQUEST_TIMEOUT ; 
 int LCI_REQ_SUBELEM_MAX_AGE ; 
 int LOCATION_SUBJECT_REMOTE ; 
 int MEASURE_TYPE_LCI ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int WLAN_ACTION_RADIO_MEASUREMENT ; 
 int WLAN_EID_MEASURE_REQUEST ; 
 int WLAN_RRM_CAPS_LCI_MEASUREMENT ; 
 int WLAN_RRM_RADIO_MEASUREMENT_REQUEST ; 
 int WLAN_STA_AUTHORIZED ; 
 struct sta_info* ap_get_sta (struct hostapd_data*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct hostapd_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_register_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hostapd_data*,int /*<<< orphan*/ *) ; 
 int hostapd_drv_send_action (struct hostapd_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostapd_lci_rep_timeout_handler ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_le16 (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int) ; 

int hostapd_send_lci_req(struct hostapd_data *hapd, const u8 *addr)
{
	struct wpabuf *buf;
	struct sta_info *sta = ap_get_sta(hapd, addr);
	int ret;

	if (!sta || !(sta->flags & WLAN_STA_AUTHORIZED)) {
		wpa_printf(MSG_INFO,
			   "Request LCI: Destination address is not connected");
		return -1;
	}

	if (!(sta->rrm_enabled_capa[1] & WLAN_RRM_CAPS_LCI_MEASUREMENT)) {
		wpa_printf(MSG_INFO,
			   "Request LCI: Station does not support LCI in RRM");
		return -1;
	}

	if (hapd->lci_req_active) {
		wpa_printf(MSG_DEBUG,
			   "Request LCI: LCI request is already in process, overriding");
		hapd->lci_req_active = 0;
		eloop_cancel_timeout(hostapd_lci_rep_timeout_handler, hapd,
				     NULL);
	}

	/* Measurement request (5) + Measurement element with LCI (10) */
	buf = wpabuf_alloc(5 + 10);
	if (!buf)
		return -1;

	hapd->lci_req_token++;
	/* For wraparounds - the token must be nonzero */
	if (!hapd->lci_req_token)
		hapd->lci_req_token++;

	wpabuf_put_u8(buf, WLAN_ACTION_RADIO_MEASUREMENT);
	wpabuf_put_u8(buf, WLAN_RRM_RADIO_MEASUREMENT_REQUEST);
	wpabuf_put_u8(buf, hapd->lci_req_token);
	wpabuf_put_le16(buf, 0); /* Number of repetitions */

	wpabuf_put_u8(buf, WLAN_EID_MEASURE_REQUEST);
	wpabuf_put_u8(buf, 3 + 1 + 4);

	wpabuf_put_u8(buf, 1); /* Measurement Token */
	/*
	 * Parallel and Enable bits are 0, Duration, Request, and Report are
	 * reserved.
	 */
	wpabuf_put_u8(buf, 0);
	wpabuf_put_u8(buf, MEASURE_TYPE_LCI);

	wpabuf_put_u8(buf, LOCATION_SUBJECT_REMOTE);

	wpabuf_put_u8(buf, LCI_REQ_SUBELEM_MAX_AGE);
	wpabuf_put_u8(buf, 2);
	wpabuf_put_le16(buf, 0xffff);

	ret = hostapd_drv_send_action(hapd, hapd->iface->freq, 0, addr,
				      wpabuf_head(buf), wpabuf_len(buf));
	wpabuf_free(buf);
	if (ret)
		return ret;

	hapd->lci_req_active = 1;

	eloop_register_timeout(HOSTAPD_RRM_REQUEST_TIMEOUT, 0,
			       hostapd_lci_rep_timeout_handler, hapd, NULL);

	return 0;
}