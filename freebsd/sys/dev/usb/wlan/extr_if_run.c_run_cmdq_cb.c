#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct run_softc {size_t cmdq_exec; scalar_t__ cmdq_run; TYPE_1__* cmdq; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* func ) (TYPE_1__*) ;struct TYPE_3__* arg0; } ;

/* Variables and functions */
 scalar_t__ RUN_CMDQ_GO ; 
 size_t RUN_CMDQ_MASQ ; 
 int /*<<< orphan*/  RUN_DEBUG_CMD ; 
 int /*<<< orphan*/  RUN_DPRINTF (struct run_softc*,int /*<<< orphan*/ ,char*,size_t,int) ; 
 int /*<<< orphan*/  RUN_LOCK (struct run_softc*) ; 
 int /*<<< orphan*/  RUN_UNLOCK (struct run_softc*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*) ; 

__attribute__((used)) static void
run_cmdq_cb(void *arg, int pending)
{
	struct run_softc *sc = arg;
	uint8_t i;

	/* call cmdq[].func locked */
	RUN_LOCK(sc);
	for (i = sc->cmdq_exec; sc->cmdq[i].func && pending;
	    i = sc->cmdq_exec, pending--) {
		RUN_DPRINTF(sc, RUN_DEBUG_CMD, "cmdq_exec=%d pending=%d\n",
		    i, pending);
		if (sc->cmdq_run == RUN_CMDQ_GO) {
			/*
			 * If arg0 is NULL, callback func needs more
			 * than one arg. So, pass ptr to cmdq struct.
			 */
			if (sc->cmdq[i].arg0)
				sc->cmdq[i].func(sc->cmdq[i].arg0);
			else
				sc->cmdq[i].func(&sc->cmdq[i]);
		}
		sc->cmdq[i].arg0 = NULL;
		sc->cmdq[i].func = NULL;
		sc->cmdq_exec++;
		sc->cmdq_exec &= RUN_CMDQ_MASQ;
	}
	RUN_UNLOCK(sc);
}