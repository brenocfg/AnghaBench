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
typedef  int /*<<< orphan*/  u16 ;
struct sta_info {int /*<<< orphan*/  vht_opmode; int /*<<< orphan*/  flags; } ;
struct hostapd_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_STATUS_SUCCESS ; 
 int /*<<< orphan*/  WLAN_STA_VHT_OPMODE_ENABLED ; 

u16 set_sta_vht_opmode(struct hostapd_data *hapd, struct sta_info *sta,
		       const u8 *vht_oper_notif)
{
	if (!vht_oper_notif) {
		sta->flags &= ~WLAN_STA_VHT_OPMODE_ENABLED;
		return WLAN_STATUS_SUCCESS;
	}

	sta->flags |= WLAN_STA_VHT_OPMODE_ENABLED;
	sta->vht_opmode = *vht_oper_notif;
	return WLAN_STATUS_SUCCESS;
}