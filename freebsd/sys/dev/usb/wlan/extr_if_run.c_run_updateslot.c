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
struct ieee80211com {struct run_softc* ic_softc; } ;
struct TYPE_2__ {struct ieee80211com* arg0; int /*<<< orphan*/  func; } ;

/* Variables and functions */
 size_t RUN_CMDQ_GET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RUN_DEBUG_BEACON ; 
 int /*<<< orphan*/  RUN_DPRINTF (struct run_softc*,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  ieee80211_runtask (struct ieee80211com*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  run_updateslot_cb ; 

__attribute__((used)) static void
run_updateslot(struct ieee80211com *ic)
{
	struct run_softc *sc = ic->ic_softc;
	uint32_t i;

	i = RUN_CMDQ_GET(&sc->cmdq_store);
	RUN_DPRINTF(sc, RUN_DEBUG_BEACON, "cmdq_store=%d\n", i);
	sc->cmdq[i].func = run_updateslot_cb;
	sc->cmdq[i].arg0 = ic;
	ieee80211_runtask(ic, &sc->cmdq_task);

	return;
}