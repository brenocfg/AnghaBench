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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct run_softc {int dummy; } ;
struct ieee80211_key {int wk_flags; int wk_keyix; scalar_t__ wk_pad; } ;
struct run_cmdq {struct ieee80211_key key; struct run_softc* arg1; } ;

/* Variables and functions */
 int IEEE80211_KEY_GROUP ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  RT2860_SKEY_MODE_0_7 ; 
 int /*<<< orphan*/  RT2860_WCID_ATTR (scalar_t__) ; 
 int /*<<< orphan*/  RT2860_WCID_ENTRY (scalar_t__) ; 
 int /*<<< orphan*/  RUN_DEBUG_KEY ; 
 int /*<<< orphan*/  RUN_DPRINTF (struct run_softc*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  RUN_LOCK_ASSERT (struct run_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  run_read (struct run_softc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  run_set_region_4 (struct run_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  run_write (struct run_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
run_key_delete_cb(void *arg)
{
	struct run_cmdq *cmdq = arg;
	struct run_softc *sc = cmdq->arg1;
	struct ieee80211_key *k = &cmdq->key;
	uint32_t attr;
	uint8_t wcid;

	RUN_LOCK_ASSERT(sc, MA_OWNED);

	if (k->wk_flags & IEEE80211_KEY_GROUP) {
		/* remove group key */
		RUN_DPRINTF(sc, RUN_DEBUG_KEY, "removing group key\n");
		run_read(sc, RT2860_SKEY_MODE_0_7, &attr);
		attr &= ~(0xf << (k->wk_keyix * 4));
		run_write(sc, RT2860_SKEY_MODE_0_7, attr);
	} else {
		/* remove pairwise key */
		RUN_DPRINTF(sc, RUN_DEBUG_KEY,
		    "removing key for wcid %x\n", k->wk_pad);
		/* matching wcid was written to wk_pad in run_key_set() */
		wcid = k->wk_pad;
		run_read(sc, RT2860_WCID_ATTR(wcid), &attr);
		attr &= ~0xf;
		run_write(sc, RT2860_WCID_ATTR(wcid), attr);
		run_set_region_4(sc, RT2860_WCID_ENTRY(wcid), 0, 8);
	}

	k->wk_pad = 0;
}