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

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_ACTION_CAT_VHT ; 
 int /*<<< orphan*/  WLAN_ACTION_VHT_COMPRESSED_BF ; 
 int /*<<< orphan*/  WLAN_ACTION_VHT_GROUPID_MGMT ; 
 int /*<<< orphan*/  WLAN_ACTION_VHT_OPMODE_NOTIF ; 
 int /*<<< orphan*/  ieee80211_recv_action_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_send_action_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vht_recv_action_placeholder ; 
 int /*<<< orphan*/  vht_send_action_placeholder ; 

__attribute__((used)) static void
ieee80211_vht_init(void)
{

	ieee80211_recv_action_register(IEEE80211_ACTION_CAT_VHT,
	    WLAN_ACTION_VHT_COMPRESSED_BF, vht_recv_action_placeholder);
	ieee80211_recv_action_register(IEEE80211_ACTION_CAT_VHT,
	    WLAN_ACTION_VHT_GROUPID_MGMT, vht_recv_action_placeholder);
	ieee80211_recv_action_register(IEEE80211_ACTION_CAT_VHT,
	    WLAN_ACTION_VHT_OPMODE_NOTIF, vht_recv_action_placeholder);

	ieee80211_send_action_register(IEEE80211_ACTION_CAT_VHT,
	    WLAN_ACTION_VHT_COMPRESSED_BF, vht_send_action_placeholder);
	ieee80211_send_action_register(IEEE80211_ACTION_CAT_VHT,
	    WLAN_ACTION_VHT_GROUPID_MGMT, vht_send_action_placeholder);
	ieee80211_send_action_register(IEEE80211_ACTION_CAT_VHT,
	    WLAN_ACTION_VHT_OPMODE_NOTIF, vht_send_action_placeholder);
}