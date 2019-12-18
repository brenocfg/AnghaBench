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
struct ifnet {int /*<<< orphan*/  if_broadcastaddr; } ;
struct ieee80211vap {int iv_flags_ext; int /*<<< orphan*/  iv_myaddr; int /*<<< orphan*/  iv_bss; struct ifnet* iv_ifp; struct ieee80211com* iv_ic; } ;
struct ieee80211com {struct ieee80211_scan_state* ic_scan; } ;
struct ieee80211_scan_state {int ss_nssid; int ss_flags; TYPE_1__* ss_ssid; } ;
struct TYPE_2__ {char* ssid; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int IEEE80211_FEXT_SCAN_OFFLOAD ; 
 int IEEE80211_SCAN_NOBCAST ; 
 int /*<<< orphan*/  ieee80211_send_probereq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ieee80211_swscan_probe_curchan(struct ieee80211vap *vap, int force)
{
	struct ieee80211com *ic = vap->iv_ic;
	struct ieee80211_scan_state *ss = ic->ic_scan;
	struct ifnet *ifp = vap->iv_ifp;
	int i;

	/*
	 * Full-offload scan devices don't require this.
	 */
	if (vap->iv_flags_ext & IEEE80211_FEXT_SCAN_OFFLOAD)
		return;

	/*
	 * Send directed probe requests followed by any
	 * broadcast probe request.
	 * XXX remove dependence on ic/vap->iv_bss
	 */
	for (i = 0; i < ss->ss_nssid; i++)
		ieee80211_send_probereq(vap->iv_bss,
			vap->iv_myaddr, ifp->if_broadcastaddr,
			ifp->if_broadcastaddr,
			ss->ss_ssid[i].ssid, ss->ss_ssid[i].len);
	if ((ss->ss_flags & IEEE80211_SCAN_NOBCAST) == 0)
		ieee80211_send_probereq(vap->iv_bss,
			vap->iv_myaddr, ifp->if_broadcastaddr,
			ifp->if_broadcastaddr,
			"", 0);
}