#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct resource {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  begin_transaction; } ;
struct ata_channel {int flags; TYPE_2__ hw; scalar_t__ unit; TYPE_1__* r_io; } ;
struct TYPE_6__ {int dbdma_rid; struct ata_channel sc_ch; void* dbdma_regs; } ;
struct ata_macio_softc {int rev; int* udmaconf; int* wdmaconf; int* pioconf; TYPE_3__ sc_ch; int /*<<< orphan*/ * sc_mem; } ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int offset; int /*<<< orphan*/ * res; } ;

/* Variables and functions */
 int ATA_COMMAND ; 
 size_t ATA_CONTROL ; 
 int ATA_DATA ; 
 int /*<<< orphan*/  ATA_INTR_FLAGS ; 
 int ATA_MACIO_ALTOFFSET ; 
 int ATA_MACIO_REGGAP ; 
 int /*<<< orphan*/  ATA_MACIO_TIMINGREG ; 
 int ATA_NO_ATAPI_DMA ; 
 int ATA_USE_16BIT ; 
 int ENXIO ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int ata_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_dbdma_dmainit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_default_registers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_generic_hw (int /*<<< orphan*/ ) ; 
 scalar_t__ ata_interrupt ; 
 int /*<<< orphan*/  ata_macio_begin_transaction ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int bus_read_4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_setup_intr (int /*<<< orphan*/ ,struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ata_macio_softc*,void**) ; 
 struct ata_macio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
ata_macio_attach(device_t dev)
{
	struct ata_macio_softc *sc = device_get_softc(dev);
	uint32_t timingreg;
	struct ata_channel *ch;
	int rid, i;

	/*
	 * Allocate resources
	 */

	rid = 0;
	ch = &sc->sc_ch.sc_ch;
	sc->sc_mem = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid, 
	    RF_ACTIVE);
	if (sc->sc_mem == NULL) {
		device_printf(dev, "could not allocate memory\n");
		return (ENXIO);
	}

	/*
	 * Set up the resource vectors
	 */
	for (i = ATA_DATA; i <= ATA_COMMAND; i++) {
		ch->r_io[i].res = sc->sc_mem;
		ch->r_io[i].offset = i * ATA_MACIO_REGGAP;
	}
	ch->r_io[ATA_CONTROL].res = sc->sc_mem;
	ch->r_io[ATA_CONTROL].offset = ATA_MACIO_ALTOFFSET;
	ata_default_registers(dev);

	ch->unit = 0;
	ch->flags |= ATA_USE_16BIT | ATA_NO_ATAPI_DMA;
	ata_generic_hw(dev);

#if USE_DBDMA_IRQ
	int dbdma_irq_rid = 1;
	struct resource *dbdma_irq;
	void *cookie;
#endif

	/* Init DMA engine */

	sc->sc_ch.dbdma_rid = 1;
	sc->sc_ch.dbdma_regs = bus_alloc_resource_any(dev, SYS_RES_MEMORY, 
	    &sc->sc_ch.dbdma_rid, RF_ACTIVE); 

	ata_dbdma_dmainit(dev);

	/* Configure initial timings */
	timingreg = bus_read_4(sc->sc_mem, ATA_MACIO_TIMINGREG);
	if (sc->rev == 4) {
		sc->udmaconf[0] = sc->udmaconf[1] = timingreg & 0x1ff00000;
		sc->wdmaconf[0] = sc->wdmaconf[1] = timingreg & 0x001ffc00;
		sc->pioconf[0]  = sc->pioconf[1]  = timingreg & 0x000003ff;
	} else {
		sc->udmaconf[0] = sc->udmaconf[1] = 0;
		sc->wdmaconf[0] = sc->wdmaconf[1] = timingreg & 0xfffff800;
		sc->pioconf[0]  = sc->pioconf[1]  = timingreg & 0x000007ff;
	}

#if USE_DBDMA_IRQ
	/* Bind to DBDMA interrupt as well */

	if ((dbdma_irq = bus_alloc_resource_any(dev, SYS_RES_IRQ,
	    &dbdma_irq_rid, RF_SHAREABLE | RF_ACTIVE)) != NULL) {
		bus_setup_intr(dev, dbdma_irq, ATA_INTR_FLAGS, NULL,
			(driver_intr_t *)ata_interrupt, sc,&cookie);
	} 
#endif

	/* Set begin_transaction */
	sc->sc_ch.sc_ch.hw.begin_transaction = ata_macio_begin_transaction;

	return ata_attach(dev);
}