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
struct TYPE_6__ {int /*<<< orphan*/  hdp_offset; int /*<<< orphan*/  queue_slots; int /*<<< orphan*/  active; int /*<<< orphan*/  avail; int /*<<< orphan*/  lock; } ;
struct cpsw_softc {int active_slave; int dualemac; TYPE_1__* port; TYPE_3__ rx; TYPE_3__ tx; int /*<<< orphan*/  nullpad; int /*<<< orphan*/  mbuf_dtag; int /*<<< orphan*/  dev; int /*<<< orphan*/ * mem_res; scalar_t__ mem_rid; int /*<<< orphan*/  irq_res; int /*<<< orphan*/  node; int /*<<< orphan*/  attach_uptime; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_5__ {int vid; } ;
struct TYPE_4__ {int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  CPSW_CPDMA_RX_HDP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPSW_CPDMA_TX_HDP (int /*<<< orphan*/ ) ; 
 int CPSW_PORTS ; 
 int /*<<< orphan*/  CPSW_SS_IDVER ; 
 int /*<<< orphan*/  CPSW_TXFRAGS ; 
 int CPSW_VLANS ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  ETHER_MIN_LEN ; 
 int /*<<< orphan*/  MCLBYTES ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ OF_getencprop (int /*<<< orphan*/ ,char*,int*,int) ; 
 scalar_t__ OF_hasprop (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 scalar_t__ cpsw_add_slots (struct cpsw_softc*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  cpsw_add_sysctls (struct cpsw_softc*) ; 
 int /*<<< orphan*/  cpsw_detach (int /*<<< orphan*/ ) ; 
 scalar_t__ cpsw_get_fdt_data (struct cpsw_softc*,int) ; 
 int /*<<< orphan*/  cpsw_init (struct cpsw_softc*) ; 
 int /*<<< orphan*/  cpsw_init_slots (struct cpsw_softc*) ; 
 int cpsw_intr_attach (struct cpsw_softc*) ; 
 int cpsw_read_4 (struct cpsw_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_reset (struct cpsw_softc*) ; 
 TYPE_2__* cpsw_vgroups ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct cpsw_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  getbinuptime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_res_spec ; 
 int /*<<< orphan*/  malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cpsw_attach(device_t dev)
{
	int error, i;
	struct cpsw_softc *sc;
	uint32_t reg;

	sc = device_get_softc(dev);
	sc->dev = dev;
	sc->node = ofw_bus_get_node(dev);
	getbinuptime(&sc->attach_uptime);

	if (OF_getencprop(sc->node, "active_slave", &sc->active_slave,
	    sizeof(sc->active_slave)) <= 0) {
		sc->active_slave = 0;
	}
	if (sc->active_slave > 1)
		sc->active_slave = 1;

	if (OF_hasprop(sc->node, "dual_emac"))
		sc->dualemac = 1;

	for (i = 0; i < CPSW_PORTS; i++) {
		if (!sc->dualemac && i != sc->active_slave)
			continue;
		if (cpsw_get_fdt_data(sc, i) != 0) {
			device_printf(dev,
			    "failed to get PHY address from FDT\n");
			return (ENXIO);
		}
	}

	/* Initialize mutexes */
	mtx_init(&sc->tx.lock, device_get_nameunit(dev),
	    "cpsw TX lock", MTX_DEF);
	mtx_init(&sc->rx.lock, device_get_nameunit(dev),
	    "cpsw RX lock", MTX_DEF);

	/* Allocate IRQ resources */
	error = bus_alloc_resources(dev, irq_res_spec, sc->irq_res);
	if (error) {
		device_printf(dev, "could not allocate IRQ resources\n");
		cpsw_detach(dev);
		return (ENXIO);
	}

	sc->mem_rid = 0;
	sc->mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, 
	    &sc->mem_rid, RF_ACTIVE);
	if (sc->mem_res == NULL) {
		device_printf(sc->dev, "failed to allocate memory resource\n");
		cpsw_detach(dev);
		return (ENXIO);
	}

	reg = cpsw_read_4(sc, CPSW_SS_IDVER);
	device_printf(dev, "CPSW SS Version %d.%d (%d)\n", (reg >> 8 & 0x7),
		reg & 0xFF, (reg >> 11) & 0x1F);

	cpsw_add_sysctls(sc);

	/* Allocate a busdma tag and DMA safe memory for mbufs. */
	error = bus_dma_tag_create(
		bus_get_dma_tag(sc->dev),	/* parent */
		1, 0,				/* alignment, boundary */
		BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
		BUS_SPACE_MAXADDR,		/* highaddr */
		NULL, NULL,			/* filtfunc, filtfuncarg */
		MCLBYTES, CPSW_TXFRAGS,		/* maxsize, nsegments */
		MCLBYTES, 0,			/* maxsegsz, flags */
		NULL, NULL,			/* lockfunc, lockfuncarg */
		&sc->mbuf_dtag);		/* dmatag */
	if (error) {
		device_printf(dev, "bus_dma_tag_create failed\n");
		cpsw_detach(dev);
		return (error);
	}

	/* Allocate a NULL buffer for padding. */
	sc->nullpad = malloc(ETHER_MIN_LEN, M_DEVBUF, M_WAITOK | M_ZERO);

	cpsw_init_slots(sc);

	/* Allocate slots to TX and RX queues. */
	STAILQ_INIT(&sc->rx.avail);
	STAILQ_INIT(&sc->rx.active);
	STAILQ_INIT(&sc->tx.avail);
	STAILQ_INIT(&sc->tx.active);
	// For now:  128 slots to TX, rest to RX.
	// XXX TODO: start with 32/64 and grow dynamically based on demand.
	if (cpsw_add_slots(sc, &sc->tx, 128) ||
	    cpsw_add_slots(sc, &sc->rx, -1)) {
		device_printf(dev, "failed to allocate dmamaps\n");
		cpsw_detach(dev);
		return (ENOMEM);
	}
	device_printf(dev, "Initial queue size TX=%d RX=%d\n",
	    sc->tx.queue_slots, sc->rx.queue_slots);

	sc->tx.hdp_offset = CPSW_CPDMA_TX_HDP(0);
	sc->rx.hdp_offset = CPSW_CPDMA_RX_HDP(0);

	if (cpsw_intr_attach(sc) == -1) {
		device_printf(dev, "failed to setup interrupts\n");
		cpsw_detach(dev);
		return (ENXIO);
	}

#ifdef CPSW_ETHERSWITCH
	for (i = 0; i < CPSW_VLANS; i++)
		cpsw_vgroups[i].vid = -1;
#endif

	/* Reset the controller. */
	cpsw_reset(sc);
	cpsw_init(sc);

	for (i = 0; i < CPSW_PORTS; i++) {
		if (!sc->dualemac && i != sc->active_slave)
			continue;
		sc->port[i].dev = device_add_child(dev, "cpsw", i);
		if (sc->port[i].dev == NULL) {
			cpsw_detach(dev);
			return (ENXIO);
		}
	}
	bus_generic_probe(dev);
	bus_generic_attach(dev);

	return (0);
}