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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {scalar_t__ ic_promisc; } ;
struct run_softc {TYPE_1__ sc_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT2860_DROP_UC_NOME ; 
 int /*<<< orphan*/  RT2860_RX_FILTR_CFG ; 
 int /*<<< orphan*/  RUN_DEBUG_RECV ; 
 int /*<<< orphan*/  RUN_DPRINTF (struct run_softc*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  run_read (struct run_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  run_write (struct run_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
run_update_promisc_locked(struct run_softc *sc)
{
        uint32_t tmp;

	run_read(sc, RT2860_RX_FILTR_CFG, &tmp);

	tmp |= RT2860_DROP_UC_NOME;
        if (sc->sc_ic.ic_promisc > 0)
		tmp &= ~RT2860_DROP_UC_NOME;

	run_write(sc, RT2860_RX_FILTR_CFG, tmp);

        RUN_DPRINTF(sc, RUN_DEBUG_RECV, "%s promiscuous mode\n",
	    (sc->sc_ic.ic_promisc > 0) ?  "entering" : "leaving");
}