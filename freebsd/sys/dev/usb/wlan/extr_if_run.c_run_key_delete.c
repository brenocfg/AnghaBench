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
typedef  size_t uint32_t ;
struct run_softc {int /*<<< orphan*/  cmdq_task; TYPE_1__* cmdq; int /*<<< orphan*/  cmdq_store; } ;
struct ieee80211vap {struct ieee80211com* iv_ic; } ;
struct ieee80211com {struct run_softc* ic_softc; } ;
struct ieee80211_key {int /*<<< orphan*/  wk_pad; int /*<<< orphan*/  wk_keyix; int /*<<< orphan*/  wk_flags; } ;
struct TYPE_2__ {struct ieee80211_key key; struct run_softc* arg1; int /*<<< orphan*/ * arg0; int /*<<< orphan*/  func; } ;

/* Variables and functions */
 size_t RUN_CMDQ_GET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RUN_DEBUG_KEY ; 
 int /*<<< orphan*/  RUN_DPRINTF (struct run_softc*,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  ieee80211_runtask (struct ieee80211com*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  run_key_delete_cb ; 

__attribute__((used)) static int
run_key_delete(struct ieee80211vap *vap, struct ieee80211_key *k)
{
	struct ieee80211com *ic = vap->iv_ic;
	struct run_softc *sc = ic->ic_softc;
	struct ieee80211_key *k0;
	uint32_t i;

	/*
	 * When called back, key might be gone. So, make a copy
	 * of some values need to delete keys before deferring.
	 * But, because of LOR with node lock, cannot use lock here.
	 * So, use atomic instead.
	 */
	i = RUN_CMDQ_GET(&sc->cmdq_store);
	RUN_DPRINTF(sc, RUN_DEBUG_KEY, "cmdq_store=%d\n", i);
	sc->cmdq[i].func = run_key_delete_cb;
	sc->cmdq[i].arg0 = NULL;
	sc->cmdq[i].arg1 = sc;
	k0 = &sc->cmdq[i].key;
	k0->wk_flags = k->wk_flags;
	k0->wk_keyix = k->wk_keyix;
	/* matching wcid was written to wk_pad in run_key_set() */
	k0->wk_pad = k->wk_pad;
	ieee80211_runtask(ic, &sc->cmdq_task);
	return (1);	/* return fake success */

}