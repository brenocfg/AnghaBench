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
struct rtwn_softc {int sc_flags; size_t cmdq_first; struct rtwn_cmdq* cmdq; } ;
struct rtwn_cmdq {int /*<<< orphan*/  data; int /*<<< orphan*/  (* func ) (struct rtwn_softc*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RTWN_CMDQ_LOCK (struct rtwn_softc*) ; 
 int RTWN_CMDQ_SIZE ; 
 int /*<<< orphan*/  RTWN_CMDQ_UNLOCK (struct rtwn_softc*) ; 
 int /*<<< orphan*/  RTWN_LOCK (struct rtwn_softc*) ; 
 int RTWN_RUNNING ; 
 int /*<<< orphan*/  RTWN_UNLOCK (struct rtwn_softc*) ; 
 int /*<<< orphan*/  memset (struct rtwn_cmdq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct rtwn_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rtwn_cmdq_cb(void *arg, int pending)
{
	struct rtwn_softc *sc = arg;
	struct rtwn_cmdq *item;

	/*
	 * Device must be powered on (via rtwn_power_on())
	 * before any command may be sent.
	 */
	RTWN_LOCK(sc);
	if (!(sc->sc_flags & RTWN_RUNNING)) {
		RTWN_UNLOCK(sc);
		return;
	}

	RTWN_CMDQ_LOCK(sc);
	while (sc->cmdq[sc->cmdq_first].func != NULL) {
		item = &sc->cmdq[sc->cmdq_first];
		sc->cmdq_first = (sc->cmdq_first + 1) % RTWN_CMDQ_SIZE;
		RTWN_CMDQ_UNLOCK(sc);

		item->func(sc, &item->data);

		RTWN_CMDQ_LOCK(sc);
		memset(item, 0, sizeof (*item));
	}
	RTWN_CMDQ_UNLOCK(sc);
	RTWN_UNLOCK(sc);
}