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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int /*<<< orphan*/  reason_code; } ;
struct TYPE_4__ {TYPE_1__ deauth; } ;
struct ieee80211_mgmt {TYPE_2__ u; int /*<<< orphan*/  bssid; int /*<<< orphan*/  sa; int /*<<< orphan*/  da; int /*<<< orphan*/  frame_control; } ;
struct hostapd_data {int /*<<< orphan*/  const* own_addr; } ;
typedef  int /*<<< orphan*/  reply ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  IEEE80211_FC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IEEE80211_HDRLEN ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  WLAN_FC_STYPE_DEAUTH ; 
 int /*<<< orphan*/  WLAN_FC_TYPE_MGMT ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  host_to_le16 (int /*<<< orphan*/ ) ; 
 scalar_t__ hostapd_drv_send_mlme (struct hostapd_data*,struct ieee80211_mgmt*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (struct ieee80211_mgmt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void send_deauth(struct hostapd_data *hapd, const u8 *addr,
			u16 reason_code)
{
	int send_len;
	struct ieee80211_mgmt reply;

	os_memset(&reply, 0, sizeof(reply));
	reply.frame_control =
		IEEE80211_FC(WLAN_FC_TYPE_MGMT, WLAN_FC_STYPE_DEAUTH);
	os_memcpy(reply.da, addr, ETH_ALEN);
	os_memcpy(reply.sa, hapd->own_addr, ETH_ALEN);
	os_memcpy(reply.bssid, hapd->own_addr, ETH_ALEN);

	send_len = IEEE80211_HDRLEN + sizeof(reply.u.deauth);
	reply.u.deauth.reason_code = host_to_le16(reason_code);

	if (hostapd_drv_send_mlme(hapd, &reply, send_len, 0) < 0)
		wpa_printf(MSG_INFO, "Failed to send deauth: %s",
			   strerror(errno));
}