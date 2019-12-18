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
struct resource {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  begin_transaction; } ;
struct ata_channel {TYPE_2__ hw; int /*<<< orphan*/  flags; scalar_t__ unit; TYPE_1__* r_io; } ;
struct TYPE_6__ {int dbdma_rid; struct ata_channel sc_ch; int /*<<< orphan*/  dbdma_offset; int /*<<< orphan*/ * dbdma_regs; } ;
struct ata_kauai_softc {int* pioconf; TYPE_3__ sc_ch; int /*<<< orphan*/ * sc_memr; scalar_t__* wdmaconf; scalar_t__* udmaconf; } ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {scalar_t__ offset; int /*<<< orphan*/ * res; } ;

/* Variables and functions */
 int ATA_COMMAND ; 
 size_t ATA_CONTROL ; 
 int ATA_DATA ; 
 int /*<<< orphan*/  ATA_INTR_FLAGS ; 
 scalar_t__ ATA_KAUAI_ALTOFFSET ; 
 int /*<<< orphan*/  ATA_KAUAI_DBDMAOFFSET ; 
 int ATA_KAUAI_REGGAP ; 
 scalar_t__ ATA_KAUAI_REGOFFSET ; 
 int /*<<< orphan*/  ATA_NO_ATAPI_DMA ; 
 int /*<<< orphan*/  ATA_USE_16BIT ; 
 int ENXIO ; 
 int PCIR_BARS ; 
 int /*<<< orphan*/  PIO_CONFIG_REG ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int ata_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_dbdma_dmainit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_default_registers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_generic_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_kauai_begin_transaction ; 
 scalar_t__ ata_kauai_dma_interrupt ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int bus_read_4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_setup_intr (int /*<<< orphan*/ ,struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ata_kauai_softc*,void**) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct ata_kauai_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ata_kauai_attach(device_t dev)
{
	struct ata_kauai_softc *sc = device_get_softc(dev);
	struct ata_channel *ch;
	int i, rid;
#if USE_DBDMA_IRQ
	int dbdma_irq_rid = 1;
	struct resource *dbdma_irq;
	void *cookie;
#endif

	ch = &sc->sc_ch.sc_ch;

        rid = PCIR_BARS;
	sc->sc_memr = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid, 
	    RF_ACTIVE);
        if (sc->sc_memr == NULL) {
                device_printf(dev, "could not allocate memory\n");
                return (ENXIO);
        }

	/*
	 * Set up the resource vectors
	 */
        for (i = ATA_DATA; i <= ATA_COMMAND; i++) {
                ch->r_io[i].res = sc->sc_memr;
                ch->r_io[i].offset = i*ATA_KAUAI_REGGAP + ATA_KAUAI_REGOFFSET;
        }
        ch->r_io[ATA_CONTROL].res = sc->sc_memr;
        ch->r_io[ATA_CONTROL].offset = ATA_KAUAI_ALTOFFSET;
	ata_default_registers(dev);

	ch->unit = 0;
	ch->flags |= ATA_USE_16BIT;

	/* XXX: ATAPI DMA is unreliable. We should find out why. */
	ch->flags |= ATA_NO_ATAPI_DMA;
	ata_generic_hw(dev);

	pci_enable_busmaster(dev);

	/* Init DMA engine */

	sc->sc_ch.dbdma_rid = 1;
	sc->sc_ch.dbdma_regs = sc->sc_memr;
	sc->sc_ch.dbdma_offset = ATA_KAUAI_DBDMAOFFSET;

	ata_dbdma_dmainit(dev);

#if USE_DBDMA_IRQ
	/* Bind to DBDMA interrupt as well */
	if ((dbdma_irq = bus_alloc_resource_any(dev, SYS_RES_IRQ,
	    &dbdma_irq_rid, RF_SHAREABLE | RF_ACTIVE)) != NULL) {
		bus_setup_intr(dev, dbdma_irq, ATA_INTR_FLAGS, NULL,
		    (driver_intr_t *)ata_kauai_dma_interrupt, sc,&cookie);
	}
#endif

	/* Set up initial mode */
	sc->pioconf[0] = sc->pioconf[1] = 
	    bus_read_4(sc->sc_memr, PIO_CONFIG_REG) & 0x0f000fff;

	sc->udmaconf[0] = sc->udmaconf[1] = 0;
	sc->wdmaconf[0] = sc->wdmaconf[1] = 0;

	/* Magic FCR value from Apple */
	bus_write_4(sc->sc_memr, 0, 0x00000007);

	/* Set begin_transaction */
	sc->sc_ch.sc_ch.hw.begin_transaction = ata_kauai_begin_transaction;

	return ata_attach(dev);
}