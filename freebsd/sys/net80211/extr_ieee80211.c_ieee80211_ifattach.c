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
struct ieee80211com {int /*<<< orphan*/  ic_txpowlimit; int /*<<< orphan*/  ic_bintval; int /*<<< orphan*/  ic_lintval; int /*<<< orphan*/  ic_hash_key; int /*<<< orphan*/  ic_update_chw; int /*<<< orphan*/  ic_update_promisc; int /*<<< orphan*/  ic_update_mcast; void* ic_oerrors; void* ic_ierrors; int /*<<< orphan*/  ic_name; int /*<<< orphan*/  ic_tq; int /*<<< orphan*/  ic_vaps; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_BINTVAL_DEFAULT ; 
 int /*<<< orphan*/  IEEE80211_LOCK_INIT (struct ieee80211com*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_TXPOWER_MAX ; 
 int /*<<< orphan*/  IEEE80211_TX_LOCK_INIT (struct ieee80211com*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct ieee80211com*,int /*<<< orphan*/ ) ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PI_NET ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arc4random () ; 
 void* counter_u64_alloc (int) ; 
 int /*<<< orphan*/  ic_head ; 
 int /*<<< orphan*/  ic_list_mtx ; 
 int /*<<< orphan*/  ic_next ; 
 int /*<<< orphan*/  ieee80211_chan_init (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_crypto_attach (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_dfs_attach (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_ht_attach (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_node_attach (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_power_attach (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_proto_attach (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_regdomain_attach (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_scan_attach (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_superg_attach (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_sysctl_attach (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_vht_attach (struct ieee80211com*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  null_update_chw ; 
 int /*<<< orphan*/  null_update_mcast ; 
 int /*<<< orphan*/  null_update_promisc ; 
 int /*<<< orphan*/  taskqueue_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_start_threads (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 

void
ieee80211_ifattach(struct ieee80211com *ic)
{

	IEEE80211_LOCK_INIT(ic, ic->ic_name);
	IEEE80211_TX_LOCK_INIT(ic, ic->ic_name);
	TAILQ_INIT(&ic->ic_vaps);

	/* Create a taskqueue for all state changes */
	ic->ic_tq = taskqueue_create("ic_taskq", M_WAITOK | M_ZERO,
	    taskqueue_thread_enqueue, &ic->ic_tq);
	taskqueue_start_threads(&ic->ic_tq, 1, PI_NET, "%s net80211 taskq",
	    ic->ic_name);
	ic->ic_ierrors = counter_u64_alloc(M_WAITOK);
	ic->ic_oerrors = counter_u64_alloc(M_WAITOK);
	/*
	 * Fill in 802.11 available channel set, mark all
	 * available channels as active, and pick a default
	 * channel if not already specified.
	 */
	ieee80211_chan_init(ic);

	ic->ic_update_mcast = null_update_mcast;
	ic->ic_update_promisc = null_update_promisc;
	ic->ic_update_chw = null_update_chw;

	ic->ic_hash_key = arc4random();
	ic->ic_bintval = IEEE80211_BINTVAL_DEFAULT;
	ic->ic_lintval = ic->ic_bintval;
	ic->ic_txpowlimit = IEEE80211_TXPOWER_MAX;

	ieee80211_crypto_attach(ic);
	ieee80211_node_attach(ic);
	ieee80211_power_attach(ic);
	ieee80211_proto_attach(ic);
#ifdef IEEE80211_SUPPORT_SUPERG
	ieee80211_superg_attach(ic);
#endif
	ieee80211_ht_attach(ic);
	ieee80211_vht_attach(ic);
	ieee80211_scan_attach(ic);
	ieee80211_regdomain_attach(ic);
	ieee80211_dfs_attach(ic);

	ieee80211_sysctl_attach(ic);

	mtx_lock(&ic_list_mtx);
	LIST_INSERT_HEAD(&ic_head, ic, ic_next);
	mtx_unlock(&ic_list_mtx);
}