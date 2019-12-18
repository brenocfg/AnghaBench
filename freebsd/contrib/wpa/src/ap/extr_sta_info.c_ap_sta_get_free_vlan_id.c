#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hostapd_vlan {int vlan_id; struct hostapd_vlan* next; } ;
struct hostapd_data {TYPE_1__* conf; } ;
struct TYPE_2__ {struct hostapd_vlan* vlan; } ;

/* Variables and functions */
 int MAX_VLAN_ID ; 

__attribute__((used)) static int ap_sta_get_free_vlan_id(struct hostapd_data *hapd)
{
	struct hostapd_vlan *vlan;
	int vlan_id = MAX_VLAN_ID + 2;

retry:
	for (vlan = hapd->conf->vlan; vlan; vlan = vlan->next) {
		if (vlan->vlan_id == vlan_id) {
			vlan_id++;
			goto retry;
		}
	}
	return vlan_id;
}