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
typedef  char uint8_t ;
struct wlan_iface {int mesh_ttl; int /*<<< orphan*/  mesh_path; int /*<<< orphan*/  mesh_metric; int /*<<< orphan*/  mesh_forwarding; int /*<<< orphan*/  mesh_peering; int /*<<< orphan*/  wname; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int IEEE80211_IOC_MESH_AP ; 
 int IEEE80211_IOC_MESH_FWRD ; 
 int IEEE80211_IOC_MESH_PR_METRIC ; 
 int IEEE80211_IOC_MESH_PR_PATH ; 
 int IEEE80211_IOC_MESH_TTL ; 
#define  LEAF_wlanMeshForwardingEnabled 133 
#define  LEAF_wlanMeshMetric 132 
#define  LEAF_wlanMeshPath 131 
#define  LEAF_wlanMeshPeeringEnabled 130 
#define  LEAF_wlanMeshRoutesFlush 129 
#define  LEAF_wlanMeshTTL 128 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  wlanMeshForwardingEnabled_false ; 
 int /*<<< orphan*/  wlanMeshForwardingEnabled_true ; 
 int /*<<< orphan*/  wlanMeshMetric_airtime ; 
 int /*<<< orphan*/  wlanMeshMetric_unknown ; 
 int /*<<< orphan*/  wlanMeshPath_hwmp ; 
 int /*<<< orphan*/  wlanMeshPath_unknown ; 
 int /*<<< orphan*/  wlanMeshPeeringEnabled_false ; 
 int /*<<< orphan*/  wlanMeshPeeringEnabled_true ; 
 scalar_t__ wlan_ioctl (int /*<<< orphan*/ ,int,int*,char*,size_t*,int /*<<< orphan*/ ) ; 

int
wlan_mesh_config_get(struct wlan_iface *wif, int which)
{
	int op, val = 0;
	size_t argsize = 0;
	uint8_t data[32], *pd = NULL;

	switch (which) {
	case LEAF_wlanMeshTTL:
		op = IEEE80211_IOC_MESH_TTL;
		break;
	case LEAF_wlanMeshPeeringEnabled:
		op = IEEE80211_IOC_MESH_AP;
		break;
	case LEAF_wlanMeshForwardingEnabled:
		op = IEEE80211_IOC_MESH_FWRD;
		break;
	case LEAF_wlanMeshMetric:
		op = IEEE80211_IOC_MESH_PR_METRIC;
		pd = data;
		argsize = sizeof(data);
		break;
	case LEAF_wlanMeshPath:
		op = IEEE80211_IOC_MESH_PR_PATH;
		pd = data;
		argsize = sizeof(data);
		break;
	case LEAF_wlanMeshRoutesFlush:
		return (0);
	default:
		return (-1);
	}

	if (wlan_ioctl(wif->wname, op, &val, pd, &argsize, 0) < 0)
		return (-1);

	switch (which) {
	case LEAF_wlanMeshTTL:
		wif->mesh_ttl = val;
		break;
	case LEAF_wlanMeshPeeringEnabled:
		if (val)
			wif->mesh_peering = wlanMeshPeeringEnabled_true;
		else
			wif->mesh_peering = wlanMeshPeeringEnabled_false;
		break;
	case LEAF_wlanMeshForwardingEnabled:
		if (val)
			wif->mesh_forwarding = wlanMeshForwardingEnabled_true;
		else
			wif->mesh_forwarding = wlanMeshForwardingEnabled_false;
		break;
	case LEAF_wlanMeshMetric:
		data[argsize] = '\0';
		if (strcmp(data, "AIRTIME") == 0)
			wif->mesh_metric = wlanMeshMetric_airtime;
		else
			wif->mesh_metric = wlanMeshMetric_unknown;
		break;
	case LEAF_wlanMeshPath:
		data[argsize] = '\0';
		if (strcmp(data, "HWMP") == 0)
			wif->mesh_path = wlanMeshPath_hwmp;
		else
			wif->mesh_path = wlanMeshPath_unknown;
	}

	return (0);
}