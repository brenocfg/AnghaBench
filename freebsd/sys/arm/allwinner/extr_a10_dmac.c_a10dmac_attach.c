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
struct a10dmac_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/ * sc_res; int /*<<< orphan*/  sc_ih; TYPE_1__* sc_ddma_channels; TYPE_1__* sc_ndma_channels; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  clk_t ;
struct TYPE_2__ {unsigned int ch_index; int /*<<< orphan*/  ch_regoff; int /*<<< orphan*/ * ch_callbackarg; int /*<<< orphan*/ * ch_callback; int /*<<< orphan*/  ch_type; struct a10dmac_softc* ch_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  AWIN_DDMA_CTL_REG ; 
 int /*<<< orphan*/  AWIN_DDMA_REG (unsigned int) ; 
 int /*<<< orphan*/  AWIN_DMA_IRQ_EN_REG ; 
 int /*<<< orphan*/  AWIN_DMA_IRQ_PEND_STA_REG ; 
 int /*<<< orphan*/  AWIN_NDMA_CTL_REG ; 
 int /*<<< orphan*/  AWIN_NDMA_REG (unsigned int) ; 
 int /*<<< orphan*/  CH_DDMA ; 
 int /*<<< orphan*/  CH_NDMA ; 
 unsigned int DDMA_CHANNELS ; 
 int /*<<< orphan*/  DMACH_WRITE (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_WRITE (struct a10dmac_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 unsigned int NDMA_CHANNELS ; 
 int /*<<< orphan*/  OF_device_register_xref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_xref_from_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a10dmac_intr ; 
 int /*<<< orphan*/  a10dmac_spec ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct a10dmac_softc*,int /*<<< orphan*/ *) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int clk_get_by_ofw_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct a10dmac_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
a10dmac_attach(device_t dev)
{
	struct a10dmac_softc *sc;
	unsigned int index;
	clk_t clk;
	int error;

	sc = device_get_softc(dev);

	if (bus_alloc_resources(dev, a10dmac_spec, sc->sc_res)) {
		device_printf(dev, "cannot allocate resources for device\n");
		return (ENXIO);
	}

	mtx_init(&sc->sc_mtx, "a10 dmac", NULL, MTX_SPIN);

	/* Activate DMA controller clock */
	error = clk_get_by_ofw_index(dev, 0, 0, &clk);
	if (error != 0) {
		device_printf(dev, "cannot get clock\n");
		return (error);
	}
	error = clk_enable(clk);
	if (error != 0) {
		device_printf(dev, "cannot enable clock\n");
		return (error);
	}

	/* Disable all interrupts and clear pending status */
	DMA_WRITE(sc, AWIN_DMA_IRQ_EN_REG, 0);
	DMA_WRITE(sc, AWIN_DMA_IRQ_PEND_STA_REG, ~0);

	/* Initialize channels */
	for (index = 0; index < NDMA_CHANNELS; index++) {
		sc->sc_ndma_channels[index].ch_sc = sc;
		sc->sc_ndma_channels[index].ch_index = index;
		sc->sc_ndma_channels[index].ch_type = CH_NDMA;
		sc->sc_ndma_channels[index].ch_callback = NULL;
		sc->sc_ndma_channels[index].ch_callbackarg = NULL;
		sc->sc_ndma_channels[index].ch_regoff = AWIN_NDMA_REG(index);
		DMACH_WRITE(&sc->sc_ndma_channels[index], AWIN_NDMA_CTL_REG, 0);
	}
	for (index = 0; index < DDMA_CHANNELS; index++) {
		sc->sc_ddma_channels[index].ch_sc = sc;
		sc->sc_ddma_channels[index].ch_index = index;
		sc->sc_ddma_channels[index].ch_type = CH_DDMA;
		sc->sc_ddma_channels[index].ch_callback = NULL;
		sc->sc_ddma_channels[index].ch_callbackarg = NULL;
		sc->sc_ddma_channels[index].ch_regoff = AWIN_DDMA_REG(index);
		DMACH_WRITE(&sc->sc_ddma_channels[index], AWIN_DDMA_CTL_REG, 0);
	}

	error = bus_setup_intr(dev, sc->sc_res[1], INTR_MPSAFE | INTR_TYPE_MISC,
	    NULL, a10dmac_intr, sc, &sc->sc_ih);
	if (error != 0) {
		device_printf(dev, "could not setup interrupt handler\n");
		bus_release_resources(dev, a10dmac_spec, sc->sc_res);
		mtx_destroy(&sc->sc_mtx);
		return (ENXIO);
	}

	OF_device_register_xref(OF_xref_from_node(ofw_bus_get_node(dev)), dev);
	return (0);
}