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
struct iwm_softc {int dummy; } ;
struct ieee80211vap {int /*<<< orphan*/  iv_dtim_period; struct ieee80211_node* iv_bss; } ;
struct ieee80211_node {int dummy; } ;
typedef  enum iwm_sf_state { ____Placeholder_iwm_sf_state } iwm_sf_state ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_2__ {int /*<<< orphan*/  in_assoc; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__* IWM_NODE (struct ieee80211_node*) ; 
 int IWM_SF_FULL_ON ; 
 int IWM_SF_INIT_OFF ; 
 int IWM_SF_UNINIT ; 
 int iwm_mvm_sf_config (struct iwm_softc*,struct ieee80211_node*,int) ; 

int
iwm_mvm_sf_update(struct iwm_softc *sc, struct ieee80211vap *changed_vif,
	boolean_t remove_vif)
{
	enum iwm_sf_state new_state;
	struct ieee80211_node *ni = NULL;
	int num_active_macs = 0;

	/* If changed_vif exists and is not to be removed, add to the count */
	if (changed_vif && !remove_vif)
		num_active_macs++;

	switch (num_active_macs) {
	case 0:
		/* If there are no active macs - change state to SF_INIT_OFF */
		new_state = IWM_SF_INIT_OFF;
		break;
	case 1:
		if (!changed_vif)
			return EINVAL;
		ni = changed_vif->iv_bss;
		if (ni != NULL && IWM_NODE(ni)->in_assoc &&
		    changed_vif->iv_dtim_period) {
			new_state = IWM_SF_FULL_ON;
		} else {
			new_state = IWM_SF_INIT_OFF;
		}
		break;
	default:
		/* If there are multiple active macs - change to SF_UNINIT */
		new_state = IWM_SF_UNINIT;
	}
	return iwm_mvm_sf_config(sc, ni, new_state);
}