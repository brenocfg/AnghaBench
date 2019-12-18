#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sta_info {char const* addr; } ;
struct TYPE_5__ {int dialog_token; int req_mode; int validity_interval; int /*<<< orphan*/ * variable; int /*<<< orphan*/  disassoc_timer; int /*<<< orphan*/  action; } ;
struct TYPE_6__ {TYPE_1__ bss_tm_req; } ;
struct TYPE_7__ {TYPE_2__ u; int /*<<< orphan*/  category; } ;
struct TYPE_8__ {TYPE_3__ action; } ;
struct ieee80211_mgmt {TYPE_4__ u; int /*<<< orphan*/ * bssid; int /*<<< orphan*/ * sa; int /*<<< orphan*/ * da; int /*<<< orphan*/  frame_control; } ;
struct hostapd_data {char const* own_addr; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 size_t ETH_ALEN ; 
 int /*<<< orphan*/  IEEE80211_FC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WLAN_ACTION_WNM ; 
 int /*<<< orphan*/  WLAN_FC_STYPE_ACTION ; 
 int /*<<< orphan*/  WLAN_FC_TYPE_MGMT ; 
 int WNM_BSS_TM_REQ_DISASSOC_IMMINENT ; 
 int WNM_BSS_TM_REQ_ESS_DISASSOC_IMMINENT ; 
 int /*<<< orphan*/  WNM_BSS_TRANS_MGMT_REQ ; 
 int /*<<< orphan*/  host_to_le16 (int) ; 
 scalar_t__ hostapd_drv_send_mlme (struct hostapd_data*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 size_t os_strlen (char const*) ; 
 int /*<<< orphan*/  set_disassoc_timer (struct hostapd_data*,struct sta_info*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

int wnm_send_ess_disassoc_imminent(struct hostapd_data *hapd,
				   struct sta_info *sta, const char *url,
				   int disassoc_timer)
{
	u8 buf[1000], *pos;
	struct ieee80211_mgmt *mgmt;
	size_t url_len;

	os_memset(buf, 0, sizeof(buf));
	mgmt = (struct ieee80211_mgmt *) buf;
	mgmt->frame_control = IEEE80211_FC(WLAN_FC_TYPE_MGMT,
					   WLAN_FC_STYPE_ACTION);
	os_memcpy(mgmt->da, sta->addr, ETH_ALEN);
	os_memcpy(mgmt->sa, hapd->own_addr, ETH_ALEN);
	os_memcpy(mgmt->bssid, hapd->own_addr, ETH_ALEN);
	mgmt->u.action.category = WLAN_ACTION_WNM;
	mgmt->u.action.u.bss_tm_req.action = WNM_BSS_TRANS_MGMT_REQ;
	mgmt->u.action.u.bss_tm_req.dialog_token = 1;
	mgmt->u.action.u.bss_tm_req.req_mode =
		WNM_BSS_TM_REQ_DISASSOC_IMMINENT |
		WNM_BSS_TM_REQ_ESS_DISASSOC_IMMINENT;
	mgmt->u.action.u.bss_tm_req.disassoc_timer =
		host_to_le16(disassoc_timer);
	mgmt->u.action.u.bss_tm_req.validity_interval = 0x01;

	pos = mgmt->u.action.u.bss_tm_req.variable;

	/* Session Information URL */
	url_len = os_strlen(url);
	if (url_len > 255)
		return -1;
	*pos++ = url_len;
	os_memcpy(pos, url, url_len);
	pos += url_len;

	if (hostapd_drv_send_mlme(hapd, buf, pos - buf, 0) < 0) {
		wpa_printf(MSG_DEBUG, "Failed to send BSS Transition "
			   "Management Request frame");
		return -1;
	}

	if (disassoc_timer) {
		/* send disassociation frame after time-out */
		set_disassoc_timer(hapd, sta, disassoc_timer);
	}

	return 0;
}