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
struct hostapd_vlan {int /*<<< orphan*/  ifname; int /*<<< orphan*/  vlan_id; } ;
struct hostapd_data {int /*<<< orphan*/  wpa_auth; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int hostapd_vlan_if_remove (struct hostapd_data*,int /*<<< orphan*/ ) ; 
 int wpa_auth_release_group (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

int vlan_if_remove(struct hostapd_data *hapd, struct hostapd_vlan *vlan)
{
	int ret;

	ret = wpa_auth_release_group(hapd->wpa_auth, vlan->vlan_id);
	if (ret)
		wpa_printf(MSG_ERROR,
			   "WPA deinitialization for VLAN %d failed (%d)",
			   vlan->vlan_id, ret);

	return hostapd_vlan_if_remove(hapd, vlan->ifname);
}