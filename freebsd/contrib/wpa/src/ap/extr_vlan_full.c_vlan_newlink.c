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
struct TYPE_3__ {int notempty; int untagged; int* tagged; } ;
struct hostapd_vlan {int configured; int /*<<< orphan*/  clean; TYPE_1__ vlan_desc; int /*<<< orphan*/  ifname; struct hostapd_vlan* next; } ;
struct hostapd_data {TYPE_2__* conf; } ;
struct TYPE_4__ {char* bridge; struct hostapd_vlan* vlan; } ;

/* Variables and functions */
 int /*<<< orphan*/  DVLAN_CLEAN_WLAN_PORT ; 
 int /*<<< orphan*/  DYNAMIC_VLAN_NAMING_WITH_DEVICE ; 
 int IFNAMSIZ ; 
 int MAX_NUM_TAGGED_VLAN ; 
 int MAX_VLAN_ID ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  br_addif (char*,char const*) ; 
 int /*<<< orphan*/  ifconfig_up (char const*) ; 
 scalar_t__ os_strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlan_bridge_name (char*,struct hostapd_data*,struct hostapd_vlan*,int) ; 
 int /*<<< orphan*/  vlan_get_bridge (char*,struct hostapd_data*,int) ; 
 int /*<<< orphan*/  vlan_newlink_tagged (int /*<<< orphan*/ ,char const*,char*,int,struct hostapd_data*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*) ; 

void vlan_newlink(const char *ifname, struct hostapd_data *hapd)
{
	char br_name[IFNAMSIZ];
	struct hostapd_vlan *vlan;
	int untagged, *tagged, i, notempty;

	wpa_printf(MSG_DEBUG, "VLAN: vlan_newlink(%s)", ifname);

	for (vlan = hapd->conf->vlan; vlan; vlan = vlan->next) {
		if (vlan->configured ||
		    os_strcmp(ifname, vlan->ifname) != 0)
			continue;
		break;
	}
	if (!vlan)
		return;

	vlan->configured = 1;

	notempty = vlan->vlan_desc.notempty;
	untagged = vlan->vlan_desc.untagged;
	tagged = vlan->vlan_desc.tagged;

	if (!notempty) {
		/* Non-VLAN STA */
		if (hapd->conf->bridge[0] &&
		    !br_addif(hapd->conf->bridge, ifname))
			vlan->clean |= DVLAN_CLEAN_WLAN_PORT;
	} else if (untagged > 0 && untagged <= MAX_VLAN_ID) {
		vlan_bridge_name(br_name, hapd, vlan, untagged);

		vlan_get_bridge(br_name, hapd, untagged);

		if (!br_addif(br_name, ifname))
			vlan->clean |= DVLAN_CLEAN_WLAN_PORT;
	}

	for (i = 0; i < MAX_NUM_TAGGED_VLAN && tagged[i]; i++) {
		if (tagged[i] == untagged ||
		    tagged[i] <= 0 || tagged[i] > MAX_VLAN_ID ||
		    (i > 0 && tagged[i] == tagged[i - 1]))
			continue;
		vlan_bridge_name(br_name, hapd, vlan, tagged[i]);
		vlan_get_bridge(br_name, hapd, tagged[i]);
		vlan_newlink_tagged(DYNAMIC_VLAN_NAMING_WITH_DEVICE,
				    ifname, br_name, tagged[i], hapd);
	}

	ifconfig_up(ifname);
}