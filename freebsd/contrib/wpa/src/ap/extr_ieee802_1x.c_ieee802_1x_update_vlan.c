#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlan_desc ;
struct vlan_description {int notempty; scalar_t__* tagged; int /*<<< orphan*/  untagged; } ;
struct sta_info {int /*<<< orphan*/  addr; TYPE_3__* eapol_sm; } ;
struct radius_msg {int dummy; } ;
struct hostapd_data {TYPE_2__* conf; } ;
struct TYPE_6__ {void* authFail; } ;
struct TYPE_4__ {scalar_t__ dynamic_vlan; } ;
struct TYPE_5__ {TYPE_1__ ssid; int /*<<< orphan*/  vlan; } ;

/* Variables and functions */
 scalar_t__ DYNAMIC_VLAN_REQUIRED ; 
 int /*<<< orphan*/  HOSTAPD_LEVEL_INFO ; 
 int /*<<< orphan*/  HOSTAPD_MODULE_IEEE8021X ; 
 int /*<<< orphan*/  HOSTAPD_MODULE_RADIUS ; 
 int /*<<< orphan*/  MAX_NUM_TAGGED_VLAN ; 
 void* TRUE ; 
 int ap_sta_set_vlan (struct hostapd_data*,struct sta_info*,struct vlan_description*) ; 
 int /*<<< orphan*/  hostapd_logger (struct hostapd_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  hostapd_vlan_valid (int /*<<< orphan*/ ,struct vlan_description*) ; 
 int /*<<< orphan*/  os_memset (struct vlan_description*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radius_msg_get_vlanid (struct radius_msg*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int ieee802_1x_update_vlan(struct radius_msg *msg,
				  struct hostapd_data *hapd,
				  struct sta_info *sta)
{
	struct vlan_description vlan_desc;

	os_memset(&vlan_desc, 0, sizeof(vlan_desc));
	vlan_desc.notempty = !!radius_msg_get_vlanid(msg, &vlan_desc.untagged,
						     MAX_NUM_TAGGED_VLAN,
						     vlan_desc.tagged);

	if (vlan_desc.notempty &&
	    !hostapd_vlan_valid(hapd->conf->vlan, &vlan_desc)) {
		sta->eapol_sm->authFail = TRUE;
		hostapd_logger(hapd, sta->addr, HOSTAPD_MODULE_RADIUS,
			       HOSTAPD_LEVEL_INFO,
			       "Invalid VLAN %d%s received from RADIUS server",
			       vlan_desc.untagged,
			       vlan_desc.tagged[0] ? "+" : "");
		os_memset(&vlan_desc, 0, sizeof(vlan_desc));
		ap_sta_set_vlan(hapd, sta, &vlan_desc);
		return -1;
	}

	if (hapd->conf->ssid.dynamic_vlan == DYNAMIC_VLAN_REQUIRED &&
	    !vlan_desc.notempty) {
		sta->eapol_sm->authFail = TRUE;
		hostapd_logger(hapd, sta->addr, HOSTAPD_MODULE_IEEE8021X,
			       HOSTAPD_LEVEL_INFO,
			       "authentication server did not include required VLAN ID in Access-Accept");
		return -1;
	}

	return ap_sta_set_vlan(hapd, sta, &vlan_desc);
}