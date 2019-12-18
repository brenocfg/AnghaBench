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
struct sta_info {int flags; } ;
struct hostapd_data {int /*<<< orphan*/  own_addr; int /*<<< orphan*/  msg_ctx; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int WLAN_STA_WMM ; 
 struct sta_info* ap_get_sta (struct hostapd_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hostapd_drv_poll_client (struct hostapd_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ hwaddr_aton (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*) ; 

int hostapd_ctrl_iface_poll_sta(struct hostapd_data *hapd,
				const char *txtaddr)
{
	u8 addr[ETH_ALEN];
	struct sta_info *sta;

	wpa_dbg(hapd->msg_ctx, MSG_DEBUG, "CTRL_IFACE POLL_STA %s", txtaddr);

	if (hwaddr_aton(txtaddr, addr))
		return -1;

	sta = ap_get_sta(hapd, addr);
	if (!sta)
		return -1;

	hostapd_drv_poll_client(hapd, hapd->own_addr, addr,
				sta->flags & WLAN_STA_WMM);
	return 0;
}