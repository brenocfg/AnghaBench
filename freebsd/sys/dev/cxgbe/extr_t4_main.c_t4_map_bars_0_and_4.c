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
struct adapter {int /*<<< orphan*/  dev; int /*<<< orphan*/ * msix_res; void* msix_rid; int /*<<< orphan*/  doorbells; int /*<<< orphan*/ * regs_res; int /*<<< orphan*/  mmio_len; int /*<<< orphan*/  bh; int /*<<< orphan*/  bt; void* regs_rid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOORBELL_KDB ; 
 int ENXIO ; 
 void* PCIR_BAR (int) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setbit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
t4_map_bars_0_and_4(struct adapter *sc)
{
	sc->regs_rid = PCIR_BAR(0);
	sc->regs_res = bus_alloc_resource_any(sc->dev, SYS_RES_MEMORY,
	    &sc->regs_rid, RF_ACTIVE);
	if (sc->regs_res == NULL) {
		device_printf(sc->dev, "cannot map registers.\n");
		return (ENXIO);
	}
	sc->bt = rman_get_bustag(sc->regs_res);
	sc->bh = rman_get_bushandle(sc->regs_res);
	sc->mmio_len = rman_get_size(sc->regs_res);
	setbit(&sc->doorbells, DOORBELL_KDB);

	sc->msix_rid = PCIR_BAR(4);
	sc->msix_res = bus_alloc_resource_any(sc->dev, SYS_RES_MEMORY,
	    &sc->msix_rid, RF_ACTIVE);
	if (sc->msix_res == NULL) {
		device_printf(sc->dev, "cannot map MSI-X BAR.\n");
		return (ENXIO);
	}

	return (0);
}