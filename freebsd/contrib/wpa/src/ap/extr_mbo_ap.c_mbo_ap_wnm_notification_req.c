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
typedef  int u8 ;
struct sta_info {int dummy; } ;
struct hostapd_data {TYPE_1__* conf; } ;
struct TYPE_2__ {int /*<<< orphan*/  mbo_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ OUI_WFA ; 
 int const WLAN_EID_VENDOR_SPECIFIC ; 
 scalar_t__ WPA_GET_BE24 (int const*) ; 
 struct sta_info* ap_get_sta (struct hostapd_data*,int const*) ; 
 int /*<<< orphan*/  mbo_ap_wnm_notif_req_elem (struct sta_info*,int const,int const*,int,int*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int const,int const) ; 

void mbo_ap_wnm_notification_req(struct hostapd_data *hapd, const u8 *addr,
				 const u8 *buf, size_t len)
{
	const u8 *pos, *end;
	u8 ie_len;
	struct sta_info *sta;
	int first_non_pref_chan = 1;

	if (!hapd->conf->mbo_enabled)
		return;

	sta = ap_get_sta(hapd, addr);
	if (!sta)
		return;

	pos = buf;
	end = buf + len;

	while (end - pos > 1) {
		ie_len = pos[1];

		if (2 + ie_len > end - pos)
			break;

		if (pos[0] == WLAN_EID_VENDOR_SPECIFIC &&
		    ie_len >= 4 && WPA_GET_BE24(pos + 2) == OUI_WFA)
			mbo_ap_wnm_notif_req_elem(sta, pos[5],
						  pos + 6, ie_len - 4,
						  &first_non_pref_chan);
		else
			wpa_printf(MSG_DEBUG,
				   "MBO: Ignore unknown WNM Notification element %u (len=%u)",
				   pos[0], pos[1]);

		pos += 2 + pos[1];
	}
}