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
 int /*<<< orphan*/  br_addif (char const*,char*) ; 
 int /*<<< orphan*/  dyn_iface_get (struct hostapd_data*,char*,int) ; 
 int /*<<< orphan*/  ifconfig_up (char const*) ; 
 int os_snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  vlan_add (char const*,int,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void vlan_newlink_tagged(int vlan_naming, const char *tagged_interface,
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

	clean = 0;
	ifconfig_up(tagged_interface);
	if (!vlan_add(tagged_interface, vid, vlan_ifname))
		clean |= DVLAN_CLEAN_VLAN;

	if (!br_addif(br_name, vlan_ifname))
		clean |= DVLAN_CLEAN_VLAN_PORT;

	dyn_iface_get(hapd, vlan_ifname, clean);

	ifconfig_up(vlan_ifname);
}