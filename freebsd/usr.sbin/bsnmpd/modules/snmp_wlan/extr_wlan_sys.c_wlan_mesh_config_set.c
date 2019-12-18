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
typedef  int /*<<< orphan*/  uint8_t ;
struct wlan_iface {int mesh_ttl; int /*<<< orphan*/  wname; int /*<<< orphan*/  mesh_path; int /*<<< orphan*/  mesh_metric; int /*<<< orphan*/  mesh_forwarding; int /*<<< orphan*/  mesh_peering; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int IEEE80211_IOC_MESH_AP ; 
 int IEEE80211_IOC_MESH_FWRD ; 
 int IEEE80211_IOC_MESH_PR_METRIC ; 
 int IEEE80211_IOC_MESH_PR_PATH ; 
 int IEEE80211_IOC_MESH_TTL ; 
#define  LEAF_wlanMeshForwardingEnabled 132 
#define  LEAF_wlanMeshMetric 131 
#define  LEAF_wlanMeshPath 130 
#define  LEAF_wlanMeshPeeringEnabled 129 
#define  LEAF_wlanMeshTTL 128 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  wlanMeshForwardingEnabled_true ; 
 int /*<<< orphan*/  wlanMeshMetric_airtime ; 
 int /*<<< orphan*/  wlanMeshPath_hwmp ; 
 int /*<<< orphan*/  wlanMeshPeeringEnabled_true ; 
 scalar_t__ wlan_ioctl (int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ *,size_t*,int) ; 

int
wlan_mesh_config_set(struct wlan_iface *wif, int which)
{
	int op, val = 0;
	size_t argsize = 0;
	uint8_t data[32], *pd = NULL;

	switch (which) {
	case LEAF_wlanMeshTTL:
		op = IEEE80211_IOC_MESH_TTL;
		val = wif->mesh_ttl;
		break;
	case LEAF_wlanMeshPeeringEnabled:
		op = IEEE80211_IOC_MESH_AP;
		if (wif->mesh_peering == wlanMeshPeeringEnabled_true)
			val = 1;
		break;
	case LEAF_wlanMeshForwardingEnabled:
		if (wif->mesh_forwarding == wlanMeshForwardingEnabled_true)
			val = 1;
		op = IEEE80211_IOC_MESH_FWRD;
		break;
	case LEAF_wlanMeshMetric:
		op = IEEE80211_IOC_MESH_PR_METRIC;
		if (wif->mesh_metric == wlanMeshMetric_airtime)
			strcpy(data, "AIRTIME");
		else
			return (-1);
		pd = data;
		argsize = sizeof(data);
		break;
	case LEAF_wlanMeshPath:
		op = IEEE80211_IOC_MESH_PR_PATH;
		if (wif->mesh_path == wlanMeshPath_hwmp)
			strcpy(data, "HWMP");
		else
			return (-1);
		pd = data;
		argsize = sizeof(data);
		break;
	default:
		return (-1);
	}

	if (wlan_ioctl(wif->wname, op, &val, pd, &argsize, 1) < 0)
		return (-1);

	return(0);
}