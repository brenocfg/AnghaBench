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
struct hostap_driver_data {int dummy; } ;
typedef  int /*<<< orphan*/  mgmt ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  IEEE80211_FC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IEEE80211_HDRLEN ; 
 int /*<<< orphan*/  WLAN_FC_STYPE_DEAUTH ; 
 int /*<<< orphan*/  WLAN_FC_TYPE_MGMT ; 
 int /*<<< orphan*/  host_to_le16 (int /*<<< orphan*/ ) ; 
 int hostap_send_mlme (struct hostap_driver_data*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ is_broadcast_ether_addr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ieee80211_mgmt*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hostap_sta_deauth(void *priv, const u8 *own_addr, const u8 *addr,
			     u16 reason)
{
	struct hostap_driver_data *drv = priv;
	struct ieee80211_mgmt mgmt;

	if (is_broadcast_ether_addr(addr)) {
		/*
		 * New Prism2.5/3 STA firmware versions seem to have issues
		 * with this broadcast deauth frame. This gets the firmware in
		 * odd state where nothing works correctly, so let's skip
		 * sending this for the hostap driver.
		 */
		return 0;
	}

	memset(&mgmt, 0, sizeof(mgmt));
	mgmt.frame_control = IEEE80211_FC(WLAN_FC_TYPE_MGMT,
					  WLAN_FC_STYPE_DEAUTH);
	memcpy(mgmt.da, addr, ETH_ALEN);
	memcpy(mgmt.sa, own_addr, ETH_ALEN);
	memcpy(mgmt.bssid, own_addr, ETH_ALEN);
	mgmt.u.deauth.reason_code = host_to_le16(reason);
	return hostap_send_mlme(drv, (u8 *) &mgmt, IEEE80211_HDRLEN +
				sizeof(mgmt.u.deauth), 0, 0, NULL, 0);
}