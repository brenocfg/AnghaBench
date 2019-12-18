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
struct rssiinfo {int rssi_total; int rssi_samples; } ;
struct ieee80211vap {int iv_opmode; int /*<<< orphan*/ * iv_bss; struct ieee80211com* iv_ic; } ;
struct ieee80211com {int (* ic_node_getrssi ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  ic_sta; } ;
typedef  int int8_t ;

/* Variables and functions */
#define  IEEE80211_M_AHDEMO 133 
#define  IEEE80211_M_HOSTAP 132 
#define  IEEE80211_M_IBSS 131 
#define  IEEE80211_M_MBSS 130 
#define  IEEE80211_M_MONITOR 129 
#define  IEEE80211_M_STA 128 
 int NZ (int) ; 
 int /*<<< orphan*/  get_adhoc_rssi ; 
 int /*<<< orphan*/  get_hostap_rssi ; 
 int /*<<< orphan*/  get_mesh_rssi ; 
 int /*<<< orphan*/  ieee80211_iterate_nodes_vap (int /*<<< orphan*/ *,struct ieee80211vap*,int /*<<< orphan*/ ,struct rssiinfo*) ; 
 int stub1 (int /*<<< orphan*/ *) ; 

int8_t
ieee80211_getrssi(struct ieee80211vap *vap)
{
#define	NZ(x)	((x) == 0 ? 1 : (x))
	struct ieee80211com *ic = vap->iv_ic;
	struct rssiinfo info;

	info.rssi_total = 0;
	info.rssi_samples = 0;
	switch (vap->iv_opmode) {
	case IEEE80211_M_IBSS:		/* average of all ibss neighbors */
	case IEEE80211_M_AHDEMO:	/* average of all neighbors */
		ieee80211_iterate_nodes_vap(&ic->ic_sta, vap, get_adhoc_rssi,
		    &info);
		break;
	case IEEE80211_M_HOSTAP:	/* average of all associated stations */
		ieee80211_iterate_nodes_vap(&ic->ic_sta, vap, get_hostap_rssi,
		    &info);
		break;
#ifdef IEEE80211_SUPPORT_MESH
	case IEEE80211_M_MBSS:		/* average of all mesh neighbors */
		ieee80211_iterate_nodes_vap(&ic->ic_sta, vap, get_mesh_rssi,
		    &info);
		break;
#endif
	case IEEE80211_M_MONITOR:	/* XXX */
	case IEEE80211_M_STA:		/* use stats from associated ap */
	default:
		if (vap->iv_bss != NULL)
			info.rssi_total = ic->ic_node_getrssi(vap->iv_bss);
		info.rssi_samples = 1;
		break;
	}
	return info.rssi_total / NZ(info.rssi_samples);
#undef NZ
}