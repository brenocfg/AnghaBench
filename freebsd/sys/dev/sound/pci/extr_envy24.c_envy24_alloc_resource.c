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
struct sc_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  dmat; int /*<<< orphan*/  ih; void* irq; void* irqid; void* mt; void* mth; void* mtt; void* ds; void* dsh; void* dst; void* ddma; void* ddmah; void* ddmat; void* cs; void* csh; void* cst; void* mtid; void* dsid; void* ddmaid; void* csid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_ENVY24 ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE_ENVY24 ; 
 int ENXIO ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  INTR_MPSAFE ; 
 void* PCIR_CCS ; 
 void* PCIR_DDMA ; 
 void* PCIR_DS ; 
 void* PCIR_MT ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int) ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  busdma_lock_mutex ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  envy24_intr ; 
 int /*<<< orphan*/  pci_read_config (int /*<<< orphan*/ ,void*,int) ; 
 void* rman_get_bushandle (void*) ; 
 void* rman_get_bustag (void*) ; 
 scalar_t__ snd_setup_intr (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sc_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
envy24_alloc_resource(struct sc_info *sc)
{
	/* allocate I/O port resource */
	sc->csid = PCIR_CCS;
	sc->cs = bus_alloc_resource_any(sc->dev, SYS_RES_IOPORT,
	    &sc->csid, RF_ACTIVE);
	sc->ddmaid = PCIR_DDMA;
	sc->ddma = bus_alloc_resource_any(sc->dev, SYS_RES_IOPORT,
	    &sc->ddmaid, RF_ACTIVE);
	sc->dsid = PCIR_DS;
	sc->ds = bus_alloc_resource_any(sc->dev, SYS_RES_IOPORT,
	    &sc->dsid, RF_ACTIVE);
	sc->mtid = PCIR_MT;
	sc->mt = bus_alloc_resource_any(sc->dev, SYS_RES_IOPORT,
	    &sc->mtid, RF_ACTIVE);
	if (!sc->cs || !sc->ddma || !sc->ds || !sc->mt) {
		device_printf(sc->dev, "unable to map IO port space\n");
		return ENXIO;
	}
	sc->cst = rman_get_bustag(sc->cs);
	sc->csh = rman_get_bushandle(sc->cs);
	sc->ddmat = rman_get_bustag(sc->ddma);
	sc->ddmah = rman_get_bushandle(sc->ddma);
	sc->dst = rman_get_bustag(sc->ds);
	sc->dsh = rman_get_bushandle(sc->ds);
	sc->mtt = rman_get_bustag(sc->mt);
	sc->mth = rman_get_bushandle(sc->mt);
#if(0)
	device_printf(sc->dev,
	    "IO port register values\nCCS: 0x%lx\nDDMA: 0x%lx\nDS: 0x%lx\nMT: 0x%lx\n",
	    pci_read_config(sc->dev, PCIR_CCS, 4),
	    pci_read_config(sc->dev, PCIR_DDMA, 4),
	    pci_read_config(sc->dev, PCIR_DS, 4),
	    pci_read_config(sc->dev, PCIR_MT, 4));
#endif

	/* allocate interrupt resource */
	sc->irqid = 0;
	sc->irq = bus_alloc_resource_any(sc->dev, SYS_RES_IRQ, &sc->irqid,
				 RF_ACTIVE | RF_SHAREABLE);
	if (!sc->irq ||
	    snd_setup_intr(sc->dev, sc->irq, INTR_MPSAFE, envy24_intr, sc, &sc->ih)) {
		device_printf(sc->dev, "unable to map interrupt\n");
		return ENXIO;
	}

	/* allocate DMA resource */
	if (bus_dma_tag_create(/*parent*/bus_get_dma_tag(sc->dev),
	    /*alignment*/4,
	    /*boundary*/0,
	    /*lowaddr*/BUS_SPACE_MAXADDR_ENVY24,
	    /*highaddr*/BUS_SPACE_MAXADDR_ENVY24,
	    /*filter*/NULL, /*filterarg*/NULL,
	    /*maxsize*/BUS_SPACE_MAXSIZE_ENVY24,
	    /*nsegments*/1, /*maxsegsz*/0x3ffff,
	    /*flags*/0, /*lockfunc*/busdma_lock_mutex,
	    /*lockarg*/&Giant, &sc->dmat) != 0) {
		device_printf(sc->dev, "unable to create dma tag\n");
		return ENXIO;
	}

	return 0;
}