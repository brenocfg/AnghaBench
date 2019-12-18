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
struct ieee80211vap {int /*<<< orphan*/ * iv_aid_bitmap; int /*<<< orphan*/ * iv_bss; struct ieee80211com* iv_ic; } ;
struct ieee80211com {int /*<<< orphan*/  ic_sta; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_FREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_80211_NODE ; 
 int /*<<< orphan*/  ieee80211_free_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_node_table_reset (int /*<<< orphan*/ *,struct ieee80211vap*) ; 

void
ieee80211_node_vdetach(struct ieee80211vap *vap)
{
	struct ieee80211com *ic = vap->iv_ic;

	ieee80211_node_table_reset(&ic->ic_sta, vap);
	if (vap->iv_bss != NULL) {
		ieee80211_free_node(vap->iv_bss);
		vap->iv_bss = NULL;
	}
	if (vap->iv_aid_bitmap != NULL) {
		IEEE80211_FREE(vap->iv_aid_bitmap, M_80211_NODE);
		vap->iv_aid_bitmap = NULL;
	}
}