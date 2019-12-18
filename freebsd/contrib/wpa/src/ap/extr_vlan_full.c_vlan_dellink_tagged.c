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
typedef  int /*<<< orphan*/  vlan_ifname ;
struct hostapd_data {int dummy; } ;

/* Variables and functions */
 int DVLAN_CLEAN_VLAN ; 
 int DVLAN_CLEAN_VLAN_PORT ; 
 int DYNAMIC_VLAN_NAMING_WITH_DEVICE ; 
 int IFNAMSIZ ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/  br_delif (char const*,char*) ; 
 int dyn_iface_put (struct hostapd_data*,char*) ; 
 int /*<<< orphan*/  ifconfig_down (char*) ; 
 int os_snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  vlan_rem (char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void vlan_dellink_tagged(int vlan_naming, const char *tagged_interface,
				const char *br_name, int vid,
				struct hostapd_data *hapd)
{
	char vlan_ifname[IFNAMSIZ];
	int clean;
	int ret;

	if (vlan_naming == DYNAMIC_VLAN_NAMING_WITH_DEVICE)
		ret = os_snprintf(vlan_ifname, sizeof(vlan_ifname), "%s.%d",
				  tagged_interface, vid);
	else
		ret = os_snprintf(vlan_ifname, sizeof(vlan_ifname), "vlan%d",
				  vid);
	if (ret >= (int) sizeof(vlan_ifname))
		wpa_printf(MSG_WARNING,
			   "VLAN: Interface name was truncated to %s",
			   vlan_ifname);


	clean = dyn_iface_put(hapd, vlan_ifname);

	if (clean & DVLAN_CLEAN_VLAN_PORT)
		br_delif(br_name, vlan_ifname);

	if (clean & DVLAN_CLEAN_VLAN) {
		ifconfig_down(vlan_ifname);
		vlan_rem(vlan_ifname);
	}
}