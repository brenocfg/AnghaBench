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
struct vlan_description {int untagged; scalar_t__* tagged; scalar_t__ notempty; } ;
struct sta_info {int vlan_id; struct vlan_description* vlan_desc; int /*<<< orphan*/  addr; } ;
struct hostapd_vlan {int vlan_id; scalar_t__ dynamic_vlan; struct vlan_description vlan_desc; int /*<<< orphan*/  ifname; struct hostapd_vlan* next; } ;
struct hostapd_data {TYPE_2__* conf; } ;
struct TYPE_3__ {scalar_t__ dynamic_vlan; scalar_t__ per_sta_vif; } ;
struct TYPE_4__ {struct hostapd_vlan* vlan; TYPE_1__ ssid; } ;

/* Variables and functions */
 scalar_t__ DYNAMIC_VLAN_DISABLED ; 
 int /*<<< orphan*/  HOSTAPD_LEVEL_DEBUG ; 
 int /*<<< orphan*/  HOSTAPD_MODULE_IEEE80211 ; 
 int VLAN_ID_WILDCARD ; 
 int ap_sta_get_free_vlan_id (struct hostapd_data*) ; 
 int /*<<< orphan*/  hostapd_logger (struct hostapd_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 struct hostapd_vlan* vlan_add_dynamic (struct hostapd_data*,struct hostapd_vlan*,int,struct vlan_description*) ; 
 int /*<<< orphan*/  vlan_compare (struct vlan_description*,struct vlan_description*) ; 
 int /*<<< orphan*/  vlan_remove_dynamic (struct hostapd_data*,int) ; 

int ap_sta_set_vlan(struct hostapd_data *hapd, struct sta_info *sta,
		    struct vlan_description *vlan_desc)
{
	struct hostapd_vlan *vlan = NULL, *wildcard_vlan = NULL;
	int old_vlan_id, vlan_id = 0, ret = 0;

	/* Check if there is something to do */
	if (hapd->conf->ssid.per_sta_vif && !sta->vlan_id) {
		/* This sta is lacking its own vif */
	} else if (hapd->conf->ssid.dynamic_vlan == DYNAMIC_VLAN_DISABLED &&
		   !hapd->conf->ssid.per_sta_vif && sta->vlan_id) {
		/* sta->vlan_id needs to be reset */
	} else if (!vlan_compare(vlan_desc, sta->vlan_desc)) {
		return 0; /* nothing to change */
	}

	/* Now the real VLAN changed or the STA just needs its own vif */
	if (hapd->conf->ssid.per_sta_vif) {
		/* Assign a new vif, always */
		/* find a free vlan_id sufficiently big */
		vlan_id = ap_sta_get_free_vlan_id(hapd);
		/* Get wildcard VLAN */
		for (vlan = hapd->conf->vlan; vlan; vlan = vlan->next) {
			if (vlan->vlan_id == VLAN_ID_WILDCARD)
				break;
		}
		if (!vlan) {
			hostapd_logger(hapd, sta->addr,
				       HOSTAPD_MODULE_IEEE80211,
				       HOSTAPD_LEVEL_DEBUG,
				       "per_sta_vif missing wildcard");
			vlan_id = 0;
			ret = -1;
			goto done;
		}
	} else if (vlan_desc && vlan_desc->notempty) {
		for (vlan = hapd->conf->vlan; vlan; vlan = vlan->next) {
			if (!vlan_compare(&vlan->vlan_desc, vlan_desc))
				break;
			if (vlan->vlan_id == VLAN_ID_WILDCARD)
				wildcard_vlan = vlan;
		}
		if (vlan) {
			vlan_id = vlan->vlan_id;
		} else if (wildcard_vlan) {
			vlan = wildcard_vlan;
			vlan_id = vlan_desc->untagged;
			if (vlan_desc->tagged[0]) {
				/* Tagged VLAN configuration */
				vlan_id = ap_sta_get_free_vlan_id(hapd);
			}
		} else {
			hostapd_logger(hapd, sta->addr,
				       HOSTAPD_MODULE_IEEE80211,
				       HOSTAPD_LEVEL_DEBUG,
				       "missing vlan and wildcard for vlan=%d%s",
				       vlan_desc->untagged,
				       vlan_desc->tagged[0] ? "+" : "");
			vlan_id = 0;
			ret = -1;
			goto done;
		}
	}

	if (vlan && vlan->vlan_id == VLAN_ID_WILDCARD) {
		vlan = vlan_add_dynamic(hapd, vlan, vlan_id, vlan_desc);
		if (vlan == NULL) {
			hostapd_logger(hapd, sta->addr,
				       HOSTAPD_MODULE_IEEE80211,
				       HOSTAPD_LEVEL_DEBUG,
				       "could not add dynamic VLAN interface for vlan=%d%s",
				       vlan_desc ? vlan_desc->untagged : -1,
				       (vlan_desc && vlan_desc->tagged[0]) ?
				       "+" : "");
			vlan_id = 0;
			ret = -1;
			goto done;
		}

		hostapd_logger(hapd, sta->addr, HOSTAPD_MODULE_IEEE80211,
			       HOSTAPD_LEVEL_DEBUG,
			       "added new dynamic VLAN interface '%s'",
			       vlan->ifname);
	} else if (vlan && vlan->dynamic_vlan > 0) {
		vlan->dynamic_vlan++;
		hostapd_logger(hapd, sta->addr,
			       HOSTAPD_MODULE_IEEE80211,
			       HOSTAPD_LEVEL_DEBUG,
			       "updated existing dynamic VLAN interface '%s'",
			       vlan->ifname);
	}
done:
	old_vlan_id = sta->vlan_id;
	sta->vlan_id = vlan_id;
	sta->vlan_desc = vlan ? &vlan->vlan_desc : NULL;

	if (vlan_id != old_vlan_id && old_vlan_id)
		vlan_remove_dynamic(hapd, old_vlan_id);

	return ret;
}