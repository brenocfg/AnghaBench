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
struct wpabuf {int dummy; } ;
struct wpa_supplicant {scalar_t__ wpa_state; int /*<<< orphan*/  bssid; int /*<<< orphan*/  own_addr; int /*<<< orphan*/  assoc_freq; int /*<<< orphan*/  mbo_wnm_token; int /*<<< orphan*/  current_bss; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBO_IE_VENDOR_TYPE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WLAN_ACTION_WNM ; 
 int /*<<< orphan*/  WLAN_EID_VENDOR_SPECIFIC ; 
 int /*<<< orphan*/  WNM_NOTIFICATION_REQ ; 
 scalar_t__ WPA_COMPLETED ; 
 int /*<<< orphan*/  wpa_bss_get_vendor_ie (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wpa_drv_send_action (struct wpa_supplicant*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wpas_mbo_send_wnm_notification(struct wpa_supplicant *wpa_s,
					   const u8 *data, size_t len)
{
	struct wpabuf *buf;
	int res;

	/*
	 * Send WNM-Notification Request frame only in case of a change in
	 * non-preferred channels list during association, if the AP supports
	 * MBO.
	 */
	if (wpa_s->wpa_state != WPA_COMPLETED || !wpa_s->current_bss ||
	    !wpa_bss_get_vendor_ie(wpa_s->current_bss, MBO_IE_VENDOR_TYPE))
		return;

	buf = wpabuf_alloc(4 + len);
	if (!buf)
		return;

	wpabuf_put_u8(buf, WLAN_ACTION_WNM);
	wpabuf_put_u8(buf, WNM_NOTIFICATION_REQ);
	wpa_s->mbo_wnm_token++;
	if (wpa_s->mbo_wnm_token == 0)
		wpa_s->mbo_wnm_token++;
	wpabuf_put_u8(buf, wpa_s->mbo_wnm_token);
	wpabuf_put_u8(buf, WLAN_EID_VENDOR_SPECIFIC); /* Type */

	wpabuf_put_data(buf, data, len);

	res = wpa_drv_send_action(wpa_s, wpa_s->assoc_freq, 0, wpa_s->bssid,
				  wpa_s->own_addr, wpa_s->bssid,
				  wpabuf_head(buf), wpabuf_len(buf), 0);
	if (res < 0)
		wpa_printf(MSG_DEBUG,
			   "Failed to send WNM-Notification Request frame with non-preferred channel list");

	wpabuf_free(buf);
}