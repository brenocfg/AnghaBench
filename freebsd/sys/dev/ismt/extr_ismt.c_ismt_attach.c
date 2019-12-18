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
struct ismt_softc {int mmio_rid; int desc_bus_addr; int dma_buffer_bus_addr; int using_msi; int intr_rid; int /*<<< orphan*/  intr_handle; int /*<<< orphan*/ * intr_res; int /*<<< orphan*/ * mmio_res; int /*<<< orphan*/  dma_buffer; int /*<<< orphan*/  dma_buffer_dma_map; int /*<<< orphan*/  dma_buffer_dma_tag; int /*<<< orphan*/  desc; int /*<<< orphan*/  desc_dma_map; int /*<<< orphan*/  desc_dma_tag; int /*<<< orphan*/  mmio_handle; int /*<<< orphan*/  mmio_tag; int /*<<< orphan*/ * smbdev; int /*<<< orphan*/  pcidev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_WAITOK ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  DESC_SIZE ; 
 int /*<<< orphan*/  DMA_BUFFER_SIZE ; 
 int ENOMEM ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  ISMT_DEBUG (int /*<<< orphan*/ ,char*,int) ; 
 int ISMT_DESC_ENTRIES ; 
 int ISMT_MCTRL_MEIE ; 
 int ISMT_MDS_MASK ; 
 scalar_t__ ISMT_MSTR_MCTRL ; 
 scalar_t__ ISMT_MSTR_MDBA ; 
 scalar_t__ ISMT_MSTR_MDS ; 
 scalar_t__ ISMT_MSTR_MSTS ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PCIR_BAR (int /*<<< orphan*/ ) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int bus_read_4 (int /*<<< orphan*/ *,scalar_t__) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ismt_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 struct ismt_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ismt_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ismt_intr ; 
 int /*<<< orphan*/  ismt_single_map ; 
 scalar_t__ pci_alloc_msi (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_msi_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ismt_attach(device_t dev)
{
	struct ismt_softc *sc = device_get_softc(dev);
	int err, num_vectors, val;

	sc->pcidev = dev;
	pci_enable_busmaster(dev);

	if ((sc->smbdev = device_add_child(dev, "smbus", -1)) == NULL) {
		device_printf(dev, "no smbus child found\n");
		err = ENXIO;
		goto fail;
	}

	sc->mmio_rid = PCIR_BAR(0);
	sc->mmio_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &sc->mmio_rid, RF_ACTIVE);
	if (sc->mmio_res == NULL) {
		device_printf(dev, "cannot allocate mmio region\n");
		err = ENOMEM;
		goto fail;
	}

	sc->mmio_tag = rman_get_bustag(sc->mmio_res);
	sc->mmio_handle = rman_get_bushandle(sc->mmio_res);

	/* Attach "smbus" child */
	if ((err = bus_generic_attach(dev)) != 0) {
		device_printf(dev, "failed to attach child: %d\n", err);
		err = ENXIO;
		goto fail;
	}

	bus_dma_tag_create(bus_get_dma_tag(dev), 4, PAGE_SIZE,
	    BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR, NULL, NULL,
	    DESC_SIZE, 1, DESC_SIZE,
	    0, NULL, NULL, &sc->desc_dma_tag);

	bus_dma_tag_create(bus_get_dma_tag(dev), 4, PAGE_SIZE,
	    BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR, NULL, NULL,
	    DMA_BUFFER_SIZE, 1, DMA_BUFFER_SIZE,
	    0, NULL, NULL, &sc->dma_buffer_dma_tag);

	bus_dmamap_create(sc->desc_dma_tag, 0,
	    &sc->desc_dma_map);
	bus_dmamap_create(sc->dma_buffer_dma_tag, 0,
	    &sc->dma_buffer_dma_map);

	bus_dmamem_alloc(sc->desc_dma_tag,
	    (void **)&sc->desc, BUS_DMA_WAITOK,
	    &sc->desc_dma_map);
	bus_dmamem_alloc(sc->dma_buffer_dma_tag,
	    (void **)&sc->dma_buffer, BUS_DMA_WAITOK,
	    &sc->dma_buffer_dma_map);

	bus_dmamap_load(sc->desc_dma_tag,
	    sc->desc_dma_map, sc->desc, DESC_SIZE,
	    ismt_single_map, &sc->desc_bus_addr, 0);
	bus_dmamap_load(sc->dma_buffer_dma_tag,
	    sc->dma_buffer_dma_map, sc->dma_buffer, DMA_BUFFER_SIZE,
	    ismt_single_map, &sc->dma_buffer_bus_addr, 0);

	bus_write_4(sc->mmio_res, ISMT_MSTR_MDBA,
	    (sc->desc_bus_addr & 0xFFFFFFFFLL));
	bus_write_4(sc->mmio_res, ISMT_MSTR_MDBA + 4,
	    (sc->desc_bus_addr >> 32));

	/* initialize the Master Control Register (MCTRL) */
	bus_write_4(sc->mmio_res, ISMT_MSTR_MCTRL, ISMT_MCTRL_MEIE);

	/* initialize the Master Status Register (MSTS) */
	bus_write_4(sc->mmio_res, ISMT_MSTR_MSTS, 0);

	/* initialize the Master Descriptor Size (MDS) */
	val = bus_read_4(sc->mmio_res, ISMT_MSTR_MDS);
	val &= ~ISMT_MDS_MASK;
	val |= (ISMT_DESC_ENTRIES - 1);
	bus_write_4(sc->mmio_res, ISMT_MSTR_MDS, val);

	sc->using_msi = 1;

	if (pci_msi_count(dev) == 0) {
		sc->using_msi = 0;
		goto intx;
	}

	num_vectors = 1;
	if (pci_alloc_msi(dev, &num_vectors) != 0) {
		sc->using_msi = 0;
		goto intx;
	}

	sc->intr_rid = 1;
	sc->intr_res = bus_alloc_resource_any(dev, SYS_RES_IRQ,
	    &sc->intr_rid, RF_ACTIVE);

	if (sc->intr_res == NULL) {
		sc->using_msi = 0;
		pci_release_msi(dev);
	}

intx:
	if (sc->using_msi == 0) {
		sc->intr_rid = 0;
		sc->intr_res = bus_alloc_resource_any(dev, SYS_RES_IRQ,
		    &sc->intr_rid, RF_SHAREABLE | RF_ACTIVE);
		if (sc->intr_res == NULL) {
			device_printf(dev, "cannot allocate irq\n");
			err = ENXIO;
			goto fail;
		}
	}

	ISMT_DEBUG(dev, "using_msi = %d\n", sc->using_msi);

	err = bus_setup_intr(dev, sc->intr_res,
	    INTR_TYPE_MISC | INTR_MPSAFE, NULL, ismt_intr, sc,
	    &sc->intr_handle);
	if (err != 0) {
		device_printf(dev, "cannot setup interrupt\n");
		err = ENXIO;
		goto fail;
	}

	return (0);

fail:
	ismt_detach(dev);
	return (err);
}