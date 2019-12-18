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
struct rsu_softc {int /*<<< orphan*/  del_key_task; int /*<<< orphan*/  free_keys_bmap; int /*<<< orphan*/  sc_running; struct ieee80211_key const** group_keys; } ;
struct ieee80211vap {struct ieee80211_key const* iv_nw_keys; TYPE_1__* iv_ic; } ;
struct ieee80211_key {int wk_flags; size_t wk_keyix; } ;
struct TYPE_2__ {struct rsu_softc* ic_softc; } ;

/* Variables and functions */
 int IEEE80211_KEY_SWCRYPT ; 
 size_t IEEE80211_WEP_NKID ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  RSU_DELKEY_BMAP_LOCK (struct rsu_softc*) ; 
 int /*<<< orphan*/  RSU_DELKEY_BMAP_UNLOCK (struct rsu_softc*) ; 
 int /*<<< orphan*/  RSU_LOCK (struct rsu_softc*) ; 
 int /*<<< orphan*/  RSU_UNLOCK (struct rsu_softc*) ; 
 size_t nitems (struct ieee80211_key const**) ; 
 int rsu_delete_key (struct rsu_softc*,size_t) ; 
 int rsu_set_key_group (struct rsu_softc*,struct ieee80211_key const*) ; 
 int rsu_set_key_pair (struct rsu_softc*,struct ieee80211_key const*) ; 
 int /*<<< orphan*/  setbit (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_thread ; 

__attribute__((used)) static int
rsu_process_key(struct ieee80211vap *vap, const struct ieee80211_key *k,
    int set)
{
	struct rsu_softc *sc = vap->iv_ic->ic_softc;
	int ret;

	if (k->wk_flags & IEEE80211_KEY_SWCRYPT) {
		/* Not for us. */
		return (1);
	}

	/* Handle group keys. */
	if (&vap->iv_nw_keys[0] <= k &&
	    k < &vap->iv_nw_keys[IEEE80211_WEP_NKID]) {
		KASSERT(k->wk_keyix < nitems(sc->group_keys),
		    ("keyix %u > %zu\n", k->wk_keyix, nitems(sc->group_keys)));

		RSU_LOCK(sc);
		sc->group_keys[k->wk_keyix] = (set ? k : NULL);
		if (!sc->sc_running) {
			/* Static keys will be set during device startup. */
			RSU_UNLOCK(sc);
			return (1);
		}

		if (set)
			ret = rsu_set_key_group(sc, k);
		else
			ret = rsu_delete_key(sc, k->wk_keyix);
		RSU_UNLOCK(sc);

		return (!ret);
	}

	if (set) {
		/* wait for pending key removal */
		taskqueue_drain(taskqueue_thread, &sc->del_key_task);

		RSU_LOCK(sc);
		ret = rsu_set_key_pair(sc, k);
		RSU_UNLOCK(sc);
	} else {
		RSU_DELKEY_BMAP_LOCK(sc);
		setbit(sc->free_keys_bmap, k->wk_keyix);
		RSU_DELKEY_BMAP_UNLOCK(sc);

		/* workaround ieee80211_node_delucastkey() locking */
		taskqueue_enqueue(taskqueue_thread, &sc->del_key_task);
		ret = 0;	/* fake success */
	}

	return (!ret);
}