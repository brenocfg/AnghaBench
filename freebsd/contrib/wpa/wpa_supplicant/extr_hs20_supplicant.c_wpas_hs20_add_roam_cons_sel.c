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
struct wpabuf {int dummy; } ;
struct wpa_ssid {scalar_t__ roaming_consortium_selection_len; int /*<<< orphan*/  roaming_consortium_selection; } ;

/* Variables and functions */
 scalar_t__ HS20_ROAMING_CONS_SEL_OUI_TYPE ; 
 int /*<<< orphan*/  OUI_WFA ; 
 scalar_t__ WLAN_EID_VENDOR_SPECIFIC ; 
 int /*<<< orphan*/  wpabuf_put_be24 (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,scalar_t__) ; 

void wpas_hs20_add_roam_cons_sel(struct wpabuf *buf,
				 const struct wpa_ssid *ssid)
{
	if (!ssid->roaming_consortium_selection ||
	    !ssid->roaming_consortium_selection_len)
		return;

	wpabuf_put_u8(buf, WLAN_EID_VENDOR_SPECIFIC);
	wpabuf_put_u8(buf, 4 + ssid->roaming_consortium_selection_len);
	wpabuf_put_be24(buf, OUI_WFA);
	wpabuf_put_u8(buf, HS20_ROAMING_CONS_SEL_OUI_TYPE);
	wpabuf_put_data(buf, ssid->roaming_consortium_selection,
			ssid->roaming_consortium_selection_len);
}