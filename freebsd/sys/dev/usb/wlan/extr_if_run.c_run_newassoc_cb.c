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
typedef  size_t uint8_t ;
struct run_softc {int /*<<< orphan*/ * wcid_stats; } ;
struct run_cmdq {size_t wcid; struct ieee80211_node* arg1; } ;
struct ieee80211_node {int /*<<< orphan*/  ni_macaddr; TYPE_2__* ni_vap; } ;
struct TYPE_4__ {TYPE_1__* iv_ic; } ;
struct TYPE_3__ {struct run_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_ADDR_LEN ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  RT2860_WCID_ENTRY (size_t) ; 
 int /*<<< orphan*/  RUN_LOCK_ASSERT (struct run_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  run_write_region_1 (struct run_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
run_newassoc_cb(void *arg)
{
	struct run_cmdq *cmdq = arg;
	struct ieee80211_node *ni = cmdq->arg1;
	struct run_softc *sc = ni->ni_vap->iv_ic->ic_softc;
	uint8_t wcid = cmdq->wcid;

	RUN_LOCK_ASSERT(sc, MA_OWNED);

	run_write_region_1(sc, RT2860_WCID_ENTRY(wcid),
	    ni->ni_macaddr, IEEE80211_ADDR_LEN);

	memset(&(sc->wcid_stats[wcid]), 0, sizeof(sc->wcid_stats[wcid]));
}