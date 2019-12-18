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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {struct cqspi_softc* ich_arg; int /*<<< orphan*/  ich_func; } ;
struct cqspi_softc {TYPE_1__ config_intrhook; int /*<<< orphan*/ * xchan_rx; int /*<<< orphan*/ * xchan_tx; int /*<<< orphan*/  dev; int /*<<< orphan*/  ih_rx; int /*<<< orphan*/  ih_tx; int /*<<< orphan*/ * xdma_rx; int /*<<< orphan*/ * xdma_tx; int /*<<< orphan*/  ih; int /*<<< orphan*/ * res; int /*<<< orphan*/  sram_phys; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  CQSPI_LOCK_INIT (struct cqspi_softc*) ; 
 int ENOMEM ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_BIO ; 
 int /*<<< orphan*/  MAXPHYS ; 
 int /*<<< orphan*/  TX_QUEUE_SIZE ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct cqspi_softc*,int /*<<< orphan*/ *) ; 
 scalar_t__ config_intrhook_establish (TYPE_1__*) ; 
 int /*<<< orphan*/  cqspi_delayed_attach ; 
 int /*<<< orphan*/  cqspi_init (struct cqspi_softc*) ; 
 int /*<<< orphan*/  cqspi_intr ; 
 int /*<<< orphan*/  cqspi_spec ; 
 int /*<<< orphan*/  cqspi_xdma_rx_intr ; 
 int /*<<< orphan*/  cqspi_xdma_tx_intr ; 
 struct cqspi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_start (int /*<<< orphan*/ ) ; 
 void* xdma_channel_alloc (int /*<<< orphan*/ *,scalar_t__) ; 
 void* xdma_ofw_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xdma_prep_sg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xdma_setup_intr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct cqspi_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cqspi_attach(device_t dev)
{
	struct cqspi_softc *sc;
	uint32_t caps;
	int error;

	sc = device_get_softc(dev);
	sc->dev = dev;

	if (bus_alloc_resources(dev, cqspi_spec, sc->res)) {
		device_printf(dev, "could not allocate resources\n");
		return (ENXIO);
	}

	/* Memory interface */
	sc->bst = rman_get_bustag(sc->res[0]);
	sc->bsh = rman_get_bushandle(sc->res[0]);

	sc->sram_phys = rman_get_start(sc->res[1]);

	/* Setup interrupt handlers */
	if (bus_setup_intr(sc->dev, sc->res[2], INTR_TYPE_BIO | INTR_MPSAFE,
	    NULL, cqspi_intr, sc, &sc->ih)) {
		device_printf(sc->dev, "Unable to setup intr\n");
		return (ENXIO);
	}

	CQSPI_LOCK_INIT(sc);

	caps = 0;

	/* Get xDMA controller. */
	sc->xdma_tx = xdma_ofw_get(sc->dev, "tx");
	if (sc->xdma_tx == NULL) {
		device_printf(dev, "Can't find DMA controller.\n");
		return (ENXIO);
	}

	sc->xdma_rx = xdma_ofw_get(sc->dev, "rx");
	if (sc->xdma_rx == NULL) {
		device_printf(dev, "Can't find DMA controller.\n");
		return (ENXIO);
	}

	/* Alloc xDMA virtual channels. */
	sc->xchan_tx = xdma_channel_alloc(sc->xdma_tx, caps);
	if (sc->xchan_tx == NULL) {
		device_printf(dev, "Can't alloc virtual DMA channel.\n");
		return (ENXIO);
	}

	sc->xchan_rx = xdma_channel_alloc(sc->xdma_rx, caps);
	if (sc->xchan_rx == NULL) {
		device_printf(dev, "Can't alloc virtual DMA channel.\n");
		return (ENXIO);
	}

	/* Setup xDMA interrupt handlers. */
	error = xdma_setup_intr(sc->xchan_tx, cqspi_xdma_tx_intr,
	    sc, &sc->ih_tx);
	if (error) {
		device_printf(sc->dev,
		    "Can't setup xDMA interrupt handler.\n");
		return (ENXIO);
	}

	error = xdma_setup_intr(sc->xchan_rx, cqspi_xdma_rx_intr,
	    sc, &sc->ih_rx);
	if (error) {
		device_printf(sc->dev,
		    "Can't setup xDMA interrupt handler.\n");
		return (ENXIO);
	}

	xdma_prep_sg(sc->xchan_tx, TX_QUEUE_SIZE, MAXPHYS, 8, 16, 0,
	    BUS_SPACE_MAXADDR_32BIT, BUS_SPACE_MAXADDR);
	xdma_prep_sg(sc->xchan_rx, TX_QUEUE_SIZE, MAXPHYS, 8, 16, 0,
	    BUS_SPACE_MAXADDR_32BIT, BUS_SPACE_MAXADDR);

	cqspi_init(sc);

	sc->config_intrhook.ich_func = cqspi_delayed_attach;
	sc->config_intrhook.ich_arg = sc;
	if (config_intrhook_establish(&sc->config_intrhook) != 0) {
		device_printf(dev, "config_intrhook_establish failed\n");
		return (ENOMEM);
	}

	return (0);
}