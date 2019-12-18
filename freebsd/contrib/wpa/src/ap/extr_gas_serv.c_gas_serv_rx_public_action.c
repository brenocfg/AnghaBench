#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_4__ {scalar_t__ category; } ;
struct TYPE_5__ {TYPE_1__ action; } ;
struct ieee80211_mgmt {int* sa; int /*<<< orphan*/  bssid; TYPE_2__ u; } ;
struct hostapd_data {TYPE_3__* conf; } ;
struct TYPE_6__ {int gas_address3; } ;

/* Variables and functions */
 int IEEE80211_HDRLEN ; 
 scalar_t__ WLAN_ACTION_PROTECTED_DUAL ; 
 scalar_t__ WLAN_ACTION_PUBLIC ; 
#define  WLAN_PA_GAS_COMEBACK_REQ 129 
#define  WLAN_PA_GAS_INITIAL_REQ 128 
 int /*<<< orphan*/  gas_serv_rx_gas_comeback_req (struct hostapd_data*,int const*,int const*,size_t,int,int) ; 
 int /*<<< orphan*/  gas_serv_rx_gas_initial_req (struct hostapd_data*,int const*,int const*,size_t,int,int) ; 
 int is_broadcast_ether_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gas_serv_rx_public_action(void *ctx, const u8 *buf, size_t len,
				      int freq)
{
	struct hostapd_data *hapd = ctx;
	const struct ieee80211_mgmt *mgmt;
	const u8 *sa, *data;
	int prot, std_addr3;

	mgmt = (const struct ieee80211_mgmt *) buf;
	if (len < IEEE80211_HDRLEN + 2)
		return;
	if (mgmt->u.action.category != WLAN_ACTION_PUBLIC &&
	    mgmt->u.action.category != WLAN_ACTION_PROTECTED_DUAL)
		return;
	/*
	 * Note: Public Action and Protected Dual of Public Action frames share
	 * the same payload structure, so it is fine to use definitions of
	 * Public Action frames to process both.
	 */
	prot = mgmt->u.action.category == WLAN_ACTION_PROTECTED_DUAL;
	sa = mgmt->sa;
	if (hapd->conf->gas_address3 == 1)
		std_addr3 = 1;
	else if (hapd->conf->gas_address3 == 2)
		std_addr3 = 0;
	else
		std_addr3 = is_broadcast_ether_addr(mgmt->bssid);
	len -= IEEE80211_HDRLEN + 1;
	data = buf + IEEE80211_HDRLEN + 1;
	switch (data[0]) {
	case WLAN_PA_GAS_INITIAL_REQ:
		gas_serv_rx_gas_initial_req(hapd, sa, data + 1, len - 1, prot,
					    std_addr3);
		break;
	case WLAN_PA_GAS_COMEBACK_REQ:
		gas_serv_rx_gas_comeback_req(hapd, sa, data + 1, len - 1, prot,
					     std_addr3);
		break;
	}
}