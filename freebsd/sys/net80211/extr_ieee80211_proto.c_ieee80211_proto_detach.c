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
struct ieee80211com {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_adhoc_detach (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_hostap_detach (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_mesh_detach (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_monitor_detach (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_sta_detach (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_wds_detach (struct ieee80211com*) ; 

void
ieee80211_proto_detach(struct ieee80211com *ic)
{
	ieee80211_monitor_detach(ic);
#ifdef IEEE80211_SUPPORT_MESH
	ieee80211_mesh_detach(ic);
#endif
	ieee80211_hostap_detach(ic);
	ieee80211_wds_detach(ic);
	ieee80211_adhoc_detach(ic);
	ieee80211_sta_detach(ic);
}