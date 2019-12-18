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
struct ieee80211vap {int iv_flags; struct ieee80211_node* iv_bss; } ;
struct iwm_vap {struct ieee80211vap iv_vap; } ;
struct TYPE_3__ {int ba_enabled; int /*<<< orphan*/  bf_enabled; } ;
struct iwm_softc {int /*<<< orphan*/  sc_ps_disabled; TYPE_1__ sc_bf; } ;
struct iwm_beacon_filter_cmd {int /*<<< orphan*/  bf_enable_beacon_filter; int /*<<< orphan*/  member_0; } ;
struct ieee80211_node {int dummy; } ;
typedef  scalar_t__ boolean_t ;
struct TYPE_4__ {scalar_t__ in_assoc; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int IEEE80211_F_PMGTON ; 
 int /*<<< orphan*/  IWM_BF_CMD_CONFIG_DEFAULTS ; 
 TYPE_2__* IWM_NODE (struct ieee80211_node*) ; 
 scalar_t__ TRUE ; 
 int _iwm_mvm_enable_beacon_filter (struct iwm_softc*,struct iwm_vap*,struct iwm_beacon_filter_cmd*) ; 
 int /*<<< orphan*/  htole32 (int) ; 

__attribute__((used)) static int
iwm_mvm_power_set_ba(struct iwm_softc *sc, struct iwm_vap *ivp)
{
	struct iwm_beacon_filter_cmd cmd = {
		IWM_BF_CMD_CONFIG_DEFAULTS,
		.bf_enable_beacon_filter = htole32(1),
	};
	struct ieee80211vap *vap = &ivp->iv_vap;
	struct ieee80211_node *ni = vap->iv_bss;
	boolean_t bss_conf_ps = FALSE;

	if (!sc->sc_bf.bf_enabled)
		return 0;

	if (ni != NULL && IWM_NODE(ni)->in_assoc &&
	    (vap->iv_flags & IEEE80211_F_PMGTON) != 0) {
		bss_conf_ps = TRUE;
	}
	sc->sc_bf.ba_enabled = !sc->sc_ps_disabled && bss_conf_ps;

	return _iwm_mvm_enable_beacon_filter(sc, ivp, &cmd);
}