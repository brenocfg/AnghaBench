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
struct cpswp_softc {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  active; } ;
struct cpsw_softc {int active_slave; TYPE_2__* port; int /*<<< orphan*/  dualemac; TYPE_1__ tx; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPSW_CPDMA_TX_CP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPSW_CPDMA_TX_HDP (int /*<<< orphan*/ ) ; 
 int CPSW_PORTS ; 
 int /*<<< orphan*/  CPSW_PORT_LOCK (struct cpswp_softc*) ; 
 int /*<<< orphan*/  CPSW_PORT_UNLOCK (struct cpswp_softc*) ; 
 int /*<<< orphan*/  cpsw_debugf_head (char*) ; 
 int /*<<< orphan*/  cpsw_dump_queue (struct cpsw_softc*,int /*<<< orphan*/ *) ; 
 int cpsw_read_4 (struct cpsw_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpswp_stop_locked (struct cpswp_softc*) ; 
 struct cpswp_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
cpsw_tx_watchdog_full_reset(struct cpsw_softc *sc)
{
	struct cpswp_softc *psc;
	int i;

	cpsw_debugf_head("CPSW watchdog");
	device_printf(sc->dev, "watchdog timeout\n");
	printf("CPSW_CPDMA_TX%d_HDP=0x%x\n", 0,
	    cpsw_read_4(sc, CPSW_CPDMA_TX_HDP(0)));
	printf("CPSW_CPDMA_TX%d_CP=0x%x\n", 0,
	    cpsw_read_4(sc, CPSW_CPDMA_TX_CP(0)));
	cpsw_dump_queue(sc, &sc->tx.active);
	for (i = 0; i < CPSW_PORTS; i++) {
		if (!sc->dualemac && i != sc->active_slave)
			continue;
		psc = device_get_softc(sc->port[i].dev);
		CPSW_PORT_LOCK(psc);
		cpswp_stop_locked(psc);
		CPSW_PORT_UNLOCK(psc);
	}
}