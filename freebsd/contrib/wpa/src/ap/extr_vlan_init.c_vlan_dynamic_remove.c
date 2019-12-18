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
struct hostapd_vlan {scalar_t__ vlan_id; int /*<<< orphan*/  ifname; struct hostapd_vlan* next; } ;
struct hostapd_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 scalar_t__ VLAN_ID_WILDCARD ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlan_dellink (int /*<<< orphan*/ ,struct hostapd_data*) ; 
 scalar_t__ vlan_if_remove (struct hostapd_data*,struct hostapd_vlan*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vlan_dynamic_remove(struct hostapd_data *hapd,
				struct hostapd_vlan *vlan)
{
	struct hostapd_vlan *next;

	while (vlan) {
		next = vlan->next;

#ifdef CONFIG_FULL_DYNAMIC_VLAN
		/* vlan_dellink() takes care of cleanup and interface removal */
		if (vlan->vlan_id != VLAN_ID_WILDCARD)
			vlan_dellink(vlan->ifname, hapd);
#else /* CONFIG_FULL_DYNAMIC_VLAN */
		if (vlan->vlan_id != VLAN_ID_WILDCARD &&
		    vlan_if_remove(hapd, vlan)) {
			wpa_printf(MSG_ERROR, "VLAN: Could not remove VLAN "
				   "iface: %s: %s",
				   vlan->ifname, strerror(errno));
		}
#endif /* CONFIG_FULL_DYNAMIC_VLAN */

		vlan = next;
	}
}