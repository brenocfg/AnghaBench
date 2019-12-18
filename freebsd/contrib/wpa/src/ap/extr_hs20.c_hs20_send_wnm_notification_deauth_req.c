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
typedef  struct wpabuf const wpabuf ;
struct hostapd_data {TYPE_1__* iface; } ;
struct TYPE_2__ {int /*<<< orphan*/  freq; } ;

/* Variables and functions */
 int HS20_WNM_DEAUTH_IMMINENT_NOTICE ; 
 int /*<<< orphan*/  OUI_WFA ; 
 int WLAN_ACTION_WNM ; 
 int WLAN_EID_VENDOR_SPECIFIC ; 
 int WNM_NOTIFICATION_REQ ; 
 int hostapd_drv_send_action (struct hostapd_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wpabuf const* wpabuf_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_put_be24 (struct wpabuf const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_buf (struct wpabuf const*,struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf const*,int) ; 

int hs20_send_wnm_notification_deauth_req(struct hostapd_data *hapd,
					  const u8 *addr,
					  const struct wpabuf *payload)
{
	struct wpabuf *buf;
	int ret;

	/* TODO: should refuse to send notification if the STA is not associated
	 * or if the STA did not indicate support for WNM-Notification */

	buf = wpabuf_alloc(4 + 6 + wpabuf_len(payload));
	if (buf == NULL)
		return -1;

	wpabuf_put_u8(buf, WLAN_ACTION_WNM);
	wpabuf_put_u8(buf, WNM_NOTIFICATION_REQ);
	wpabuf_put_u8(buf, 1); /* Dialog token */
	wpabuf_put_u8(buf, 1); /* Type - 1 reserved for WFA */

	/* Deauthentication Imminent Notice subelement */
	wpabuf_put_u8(buf, WLAN_EID_VENDOR_SPECIFIC);
	wpabuf_put_u8(buf, 4 + wpabuf_len(payload));
	wpabuf_put_be24(buf, OUI_WFA);
	wpabuf_put_u8(buf, HS20_WNM_DEAUTH_IMMINENT_NOTICE);
	wpabuf_put_buf(buf, payload);

	ret = hostapd_drv_send_action(hapd, hapd->iface->freq, 0, addr,
				      wpabuf_head(buf), wpabuf_len(buf));

	wpabuf_free(buf);

	return ret;
}