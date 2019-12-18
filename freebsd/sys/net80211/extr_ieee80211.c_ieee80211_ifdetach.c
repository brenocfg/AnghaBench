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
struct ieee80211vap {int dummy; } ;
struct ieee80211com {int /*<<< orphan*/ * ic_tq; int /*<<< orphan*/  ic_oerrors; int /*<<< orphan*/  ic_ierrors; int /*<<< orphan*/  ic_vaps; int /*<<< orphan*/  ic_restart_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_LOCK_DESTROY (struct ieee80211com*) ; 
 int /*<<< orphan*/  IEEE80211_TX_LOCK_DESTROY (struct ieee80211com*) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct ieee80211com*,int /*<<< orphan*/ ) ; 
 struct ieee80211vap* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  counter_u64_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ic_list_mtx ; 
 int /*<<< orphan*/  ic_next ; 
 int /*<<< orphan*/  ieee80211_com_vdetach (struct ieee80211vap*) ; 
 int /*<<< orphan*/  ieee80211_crypto_detach (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_dfs_detach (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_ht_detach (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_node_detach (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_power_detach (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_proto_detach (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_regdomain_detach (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_scan_detach (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_superg_detach (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_sysctl_detach (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_vap_destroy (struct ieee80211vap*) ; 
 int /*<<< orphan*/  ieee80211_vht_detach (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_waitfor_parent (struct ieee80211com*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_thread ; 

void
ieee80211_ifdetach(struct ieee80211com *ic)
{
	struct ieee80211vap *vap;

	/*
	 * We use this as an indicator that ifattach never had a chance to be
	 * called, e.g. early driver attach failed and ifdetach was called
	 * during subsequent detach.  Never fear, for we have nothing to do
	 * here.
	 */
	if (ic->ic_tq == NULL)
		return;

	mtx_lock(&ic_list_mtx);
	LIST_REMOVE(ic, ic_next);
	mtx_unlock(&ic_list_mtx);

	taskqueue_drain(taskqueue_thread, &ic->ic_restart_task);

	/*
	 * The VAP is responsible for setting and clearing
	 * the VIMAGE context.
	 */
	while ((vap = TAILQ_FIRST(&ic->ic_vaps)) != NULL) {
		ieee80211_com_vdetach(vap);
		ieee80211_vap_destroy(vap);
	}
	ieee80211_waitfor_parent(ic);

	ieee80211_sysctl_detach(ic);
	ieee80211_dfs_detach(ic);
	ieee80211_regdomain_detach(ic);
	ieee80211_scan_detach(ic);
#ifdef IEEE80211_SUPPORT_SUPERG
	ieee80211_superg_detach(ic);
#endif
	ieee80211_vht_detach(ic);
	ieee80211_ht_detach(ic);
	/* NB: must be called before ieee80211_node_detach */
	ieee80211_proto_detach(ic);
	ieee80211_crypto_detach(ic);
	ieee80211_power_detach(ic);
	ieee80211_node_detach(ic);

	counter_u64_free(ic->ic_ierrors);
	counter_u64_free(ic->ic_oerrors);

	taskqueue_free(ic->ic_tq);
	IEEE80211_TX_LOCK_DESTROY(ic);
	IEEE80211_LOCK_DESTROY(ic);
}