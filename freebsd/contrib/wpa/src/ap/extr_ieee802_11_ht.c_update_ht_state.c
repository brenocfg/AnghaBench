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
struct sta_info {int flags; scalar_t__ ht_capabilities; } ;
struct hostapd_data {int /*<<< orphan*/  iface; } ;

/* Variables and functions */
 int WLAN_STA_HT ; 
 scalar_t__ hostapd_ht_operation_update (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee802_11_set_beacons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_sta_ht (struct hostapd_data*,struct sta_info*) ; 
 int /*<<< orphan*/  update_sta_no_ht (struct hostapd_data*,struct sta_info*) ; 

void update_ht_state(struct hostapd_data *hapd, struct sta_info *sta)
{
	if ((sta->flags & WLAN_STA_HT) && sta->ht_capabilities)
		update_sta_ht(hapd, sta);
	else
		update_sta_no_ht(hapd, sta);

	if (hostapd_ht_operation_update(hapd->iface) > 0)
		ieee802_11_set_beacons(hapd->iface);
}