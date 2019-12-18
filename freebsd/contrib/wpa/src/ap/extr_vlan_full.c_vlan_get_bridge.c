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
struct hostapd_data {TYPE_2__* conf; } ;
struct TYPE_3__ {char* vlan_tagged_interface; int vlan_naming; } ;
struct TYPE_4__ {TYPE_1__ ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DVLAN_CLEAN_BR ; 
 scalar_t__ br_addbr (char const*) ; 
 int /*<<< orphan*/  dyn_iface_get (struct hostapd_data*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifconfig_up (char const*) ; 
 int /*<<< orphan*/  vlan_newlink_tagged (int,char*,char const*,int,struct hostapd_data*) ; 

__attribute__((used)) static void vlan_get_bridge(const char *br_name, struct hostapd_data *hapd,
			    int vid)
{
	char *tagged_interface = hapd->conf->ssid.vlan_tagged_interface;
	int vlan_naming = hapd->conf->ssid.vlan_naming;

	dyn_iface_get(hapd, br_name, br_addbr(br_name) ? 0 : DVLAN_CLEAN_BR);

	ifconfig_up(br_name);

	if (tagged_interface)
		vlan_newlink_tagged(vlan_naming, tagged_interface, br_name,
				    vid, hapd);
}