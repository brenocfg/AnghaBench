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
struct ieee80211vap {int /*<<< orphan*/  iv_ps_sta; int /*<<< orphan*/  (* iv_update_ps ) (struct ieee80211vap*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* iv_set_tim ) (struct ieee80211_node*,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {scalar_t__ psq_len; } ;
struct ieee80211_node {int ni_flags; TYPE_1__ ni_psq; struct ieee80211vap* ni_vap; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_MSG_POWER ; 
 int IEEE80211_NODE_PWR_MGT ; 
 int /*<<< orphan*/  IEEE80211_NOTE (struct ieee80211vap*,int /*<<< orphan*/ ,struct ieee80211_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwrsave_flushq (struct ieee80211_node*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211vap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct ieee80211vap*,int /*<<< orphan*/ ) ; 

void
ieee80211_node_pwrsave(struct ieee80211_node *ni, int enable)
{
	struct ieee80211vap *vap = ni->ni_vap;
	int update;

	update = 0;
	if (enable) {
		if ((ni->ni_flags & IEEE80211_NODE_PWR_MGT) == 0) {
			vap->iv_ps_sta++;
			update = 1;
		}
		ni->ni_flags |= IEEE80211_NODE_PWR_MGT;
		IEEE80211_NOTE(vap, IEEE80211_MSG_POWER, ni,
		    "power save mode on, %u sta's in ps mode", vap->iv_ps_sta);

		if (update)
			vap->iv_update_ps(vap, vap->iv_ps_sta);
	} else {
		if (ni->ni_flags & IEEE80211_NODE_PWR_MGT) {
			vap->iv_ps_sta--;
			update = 1;
		}
		ni->ni_flags &= ~IEEE80211_NODE_PWR_MGT;
		IEEE80211_NOTE(vap, IEEE80211_MSG_POWER, ni,
		    "power save mode off, %u sta's in ps mode", vap->iv_ps_sta);

		/* NB: order here is intentional so TIM is clear before flush */
		if (vap->iv_set_tim != NULL)
			vap->iv_set_tim(ni, 0);
		if (update) {
			/* NB if no sta's in ps, driver should flush mc q */
			vap->iv_update_ps(vap, vap->iv_ps_sta);
		}
		if (ni->ni_psq.psq_len != 0)
			pwrsave_flushq(ni);
	}
}