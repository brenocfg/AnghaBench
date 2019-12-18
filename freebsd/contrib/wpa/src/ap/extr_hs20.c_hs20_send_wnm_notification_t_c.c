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
struct hostapd_data {TYPE_1__* iface; } ;
struct TYPE_2__ {int /*<<< orphan*/  freq; } ;

/* Variables and functions */
 size_t HS20_WNM_T_C_ACCEPTANCE ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  OUI_WFA ; 
 size_t WLAN_ACTION_WNM ; 
 size_t WLAN_EID_VENDOR_SPECIFIC ; 
 size_t WNM_NOTIFICATION_REQ ; 
 int hostapd_drv_send_action (struct hostapd_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t os_strlen (char const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_be24 (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_str (struct wpabuf*,char const*) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,size_t) ; 

int hs20_send_wnm_notification_t_c(struct hostapd_data *hapd,
				   const u8 *addr, const char *url)
{
	struct wpabuf *buf;
	int ret;
	size_t url_len;

	if (!url) {
		wpa_printf(MSG_INFO, "HS 2.0: No T&C Server URL available");
		return -1;
	}

	url_len = os_strlen(url);
	if (5 + url_len > 255) {
		wpa_printf(MSG_INFO,
			   "HS 2.0: Too long T&C Server URL for WNM-Notification: '%s'",
			   url);
		return -1;
	}

	buf = wpabuf_alloc(4 + 7 + url_len);
	if (!buf)
		return -1;

	wpabuf_put_u8(buf, WLAN_ACTION_WNM);
	wpabuf_put_u8(buf, WNM_NOTIFICATION_REQ);
	wpabuf_put_u8(buf, 1); /* Dialog token */
	wpabuf_put_u8(buf, 1); /* Type - 1 reserved for WFA */

	/* Terms and Conditions Acceptance subelement */
	wpabuf_put_u8(buf, WLAN_EID_VENDOR_SPECIFIC);
	wpabuf_put_u8(buf, 4 + 1 + url_len);
	wpabuf_put_be24(buf, OUI_WFA);
	wpabuf_put_u8(buf, HS20_WNM_T_C_ACCEPTANCE);
	wpabuf_put_u8(buf, url_len);
	wpabuf_put_str(buf, url);

	ret = hostapd_drv_send_action(hapd, hapd->iface->freq, 0, addr,
				      wpabuf_head(buf), wpabuf_len(buf));

	wpabuf_free(buf);

	return ret;
}