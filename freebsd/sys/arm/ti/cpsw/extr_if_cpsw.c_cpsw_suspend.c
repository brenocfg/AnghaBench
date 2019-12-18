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
struct cpswp_softc {int dummy; } ;
struct cpsw_softc {int active_slave; TYPE_1__* port; int /*<<< orphan*/  dualemac; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPSW_DEBUGF (struct cpsw_softc*,char*) ; 
 int CPSW_PORTS ; 
 int /*<<< orphan*/  CPSW_PORT_LOCK (struct cpswp_softc*) ; 
 int /*<<< orphan*/  CPSW_PORT_UNLOCK (struct cpswp_softc*) ; 
 int /*<<< orphan*/  cpswp_stop_locked (struct cpswp_softc*) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cpsw_suspend(device_t dev)
{
	struct cpsw_softc *sc;
	struct cpswp_softc *psc;
	int i;

	sc = device_get_softc(dev);
	CPSW_DEBUGF(sc, (""));
	for (i = 0; i < CPSW_PORTS; i++) {
		if (!sc->dualemac && i != sc->active_slave)
			continue;
		psc = device_get_softc(sc->port[i].dev);
		CPSW_PORT_LOCK(psc);
		cpswp_stop_locked(psc);
		CPSW_PORT_UNLOCK(psc);
	}

	return (0);
}