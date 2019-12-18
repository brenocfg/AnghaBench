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
struct spi_softc {int debug; int /*<<< orphan*/  spibus; int /*<<< orphan*/  dev; int /*<<< orphan*/ * cspins; int /*<<< orphan*/  inthandle; int /*<<< orphan*/ * intres; int /*<<< orphan*/ * memres; int /*<<< orphan*/  mtx; int /*<<< orphan*/  basefreq; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  ich_func_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RWTUN ; 
 int /*<<< orphan*/  CTLREG_CMODES_MASTER ; 
 int /*<<< orphan*/  ECSPI_CTLREG ; 
 int ENXIO ; 
 int /*<<< orphan*/  GPIO_PIN_OUTPUT ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  WR4 (struct spi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_generic_attach ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct spi_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_intrhook_oneshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct spi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int gpio_pin_get_by_ofw_propidx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_pin_setflags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_ccm_ecspi_hz () ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nitems (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_intr ; 

__attribute__((used)) static int
spi_attach(device_t dev)
{
	struct spi_softc *sc = device_get_softc(dev);
	phandle_t node;
	int err, idx, rid;

	sc->dev = dev;
	sc->basefreq = imx_ccm_ecspi_hz();

	mtx_init(&sc->mtx, device_get_nameunit(dev), NULL, MTX_DEF);

	/* Set up debug-enable sysctl. */
	SYSCTL_ADD_INT(device_get_sysctl_ctx(sc->dev), 
	    SYSCTL_CHILDREN(device_get_sysctl_tree(sc->dev)),
	    OID_AUTO, "debug", CTLFLAG_RWTUN, &sc->debug, 0,
	    "Enable debug, higher values = more info");

	/* Allocate mmio register access resources. */
	rid = 0;
	sc->memres = bus_alloc_resource_any(sc->dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (sc->memres == NULL) {
		device_printf(sc->dev, "could not allocate registers\n");
		spi_detach(sc->dev);
		return (ENXIO);
	}

	/* Allocate interrupt resources and set up handler. */
	rid = 0;
	sc->intres = bus_alloc_resource_any(sc->dev, SYS_RES_IRQ, &rid,
	    RF_ACTIVE);
	if (sc->intres == NULL) {
		device_printf(sc->dev, "could not allocate interrupt\n");
		device_detach(sc->dev);
		return (ENXIO);
	}
	err = bus_setup_intr(sc->dev, sc->intres, INTR_TYPE_MISC | INTR_MPSAFE,
	    NULL, spi_intr, sc, &sc->inthandle);
	if (err != 0) {
		device_printf(sc->dev, "could not setup interrupt handler");
		device_detach(sc->dev);
		return (ENXIO);
	}

	/* Allocate gpio pins for configured chip selects. */
	node = ofw_bus_get_node(sc->dev);
	for (idx = 0; idx < nitems(sc->cspins); ++idx) {
		err = gpio_pin_get_by_ofw_propidx(sc->dev, node, "cs-gpios",
		    idx, &sc->cspins[idx]);
		if (err == 0) {
			gpio_pin_setflags(sc->cspins[idx], GPIO_PIN_OUTPUT);
		} else if (sc->debug >= 2) {
			device_printf(sc->dev,
			    "cannot configure gpio for chip select %u\n", idx);
		}
	}

	/*
	 * Hardware init: put all channels into Master mode, turn off the enable
	 * bit (gates off clocks); we only enable the hardware while xfers run.
	 */
	WR4(sc, ECSPI_CTLREG, CTLREG_CMODES_MASTER);

	/*
	 * Add the spibus driver as a child, and setup a one-shot intrhook to
	 * attach it after interrupts are working.  It will attach actual SPI
	 * devices as its children, and those devices may need to do IO during
	 * their attach. We can't do IO until timers and interrupts are working.
	 */
	sc->spibus = device_add_child(dev, "spibus", -1);
	config_intrhook_oneshot((ich_func_t)bus_generic_attach, dev);

	return (0);
}