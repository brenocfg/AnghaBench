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
typedef  int uint32_t ;
struct ifnet {int if_flags; int /*<<< orphan*/  if_snd; int /*<<< orphan*/  if_init; int /*<<< orphan*/  if_ioctl; int /*<<< orphan*/  if_start; struct dme_softc* if_softc; } ;
struct dme_softc {int dme_bits; int dme_rev; int /*<<< orphan*/  dme_intrhand; int /*<<< orphan*/ * dme_irq; int /*<<< orphan*/  dme_macaddr; int /*<<< orphan*/  dme_miibus; struct ifnet* dme_ifp; int /*<<< orphan*/ * dme_res; int /*<<< orphan*/  dme_handle; int /*<<< orphan*/  dme_tag; TYPE_1__* gpio_rset; int /*<<< orphan*/  dme_vcc_regulator; int /*<<< orphan*/  dme_mtx; int /*<<< orphan*/  dme_tick_ch; int /*<<< orphan*/  dme_dev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  pin; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMSR_DEFCAPMASK ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  DME_CHIPR ; 
 int DME_CHIP_DM9000 ; 
 int DME_CHIP_DM9000A ; 
 int DME_CHIP_DM9000B ; 
 int /*<<< orphan*/  DME_ISR ; 
 int /*<<< orphan*/  DME_PIDH ; 
 int /*<<< orphan*/  DME_PIDL ; 
 int /*<<< orphan*/  DME_VIDH ; 
 int /*<<< orphan*/  DME_VIDL ; 
 int ENOSPC ; 
 int ENXIO ; 
 int /*<<< orphan*/  GPIO_PIN_OUTPUT ; 
 int GPIO_PIN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int GPIO_PIN_SETFLAGS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int /*<<< orphan*/  IFQ_MAXLEN ; 
 int /*<<< orphan*/  IFQ_SET_MAXLEN (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MII_OFFSET_ANY ; 
 int /*<<< orphan*/  MII_PHY_ANY ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  MTX_NETWORK_LOCK ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct dme_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct dme_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dme_config (struct dme_softc*) ; 
 int /*<<< orphan*/  dme_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dme_get_macaddr (struct dme_softc*) ; 
 int /*<<< orphan*/  dme_ifmedia_sts ; 
 int /*<<< orphan*/  dme_ifmedia_upd ; 
 int /*<<< orphan*/  dme_init ; 
 int /*<<< orphan*/  dme_intr ; 
 int /*<<< orphan*/  dme_ioctl ; 
 int dme_read_reg (struct dme_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dme_reset (struct dme_softc*) ; 
 int /*<<< orphan*/  dme_start ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mii_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ofw_gpiobus_parse_gpios (int /*<<< orphan*/ ,char*,TYPE_1__**) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int regulator_get_by_ofw_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dme_attach(device_t dev)
{
	struct dme_softc *sc;
	struct ifnet *ifp;
	int error, rid;
	uint32_t data;

	sc = device_get_softc(dev);
	sc->dme_dev = dev;

	error = 0;

	mtx_init(&sc->dme_mtx, device_get_nameunit(dev), MTX_NETWORK_LOCK,
	    MTX_DEF);
	callout_init_mtx(&sc->dme_tick_ch, &sc->dme_mtx, 0);

	rid = 0;
	sc->dme_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (sc->dme_res == NULL) {
		device_printf(dev, "unable to map memory\n");
		error = ENXIO;
		goto fail;
	}

	rid = 0;
	sc->dme_irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    RF_ACTIVE);
	if (sc->dme_irq == NULL) {
		device_printf(dev, "unable to map memory\n");
		error = ENXIO;
		goto fail;
	}
	/*
	 * Power the chip up, if necessary
	 */
	error = regulator_get_by_ofw_property(dev, 0, "vcc-supply", &sc->dme_vcc_regulator);
	if (error == 0) {
		error = regulator_enable(sc->dme_vcc_regulator);
		if (error != 0) {
			device_printf(dev, "unable to enable power supply\n");
			error = ENXIO;
			goto fail;
		}
	}

	/*
	 * Delay a little.  This seems required on rev-1 boards (green.)
	 */
	DELAY(100000);

	/* Bring controller out of reset */
	error = ofw_gpiobus_parse_gpios(dev, "reset-gpios", &sc->gpio_rset);
	if (error > 1) {
		device_printf(dev, "too many reset gpios\n");
		sc->gpio_rset = NULL;
		error = ENXIO;
		goto fail;
	}

	if (sc->gpio_rset != NULL) {
		error = GPIO_PIN_SET(sc->gpio_rset->dev, sc->gpio_rset->pin, 0);
		if (error != 0) {
			device_printf(dev, "Cannot configure GPIO pin %d on %s\n",
			    sc->gpio_rset->pin, device_get_nameunit(sc->gpio_rset->dev));
			goto fail;
		}

		error = GPIO_PIN_SETFLAGS(sc->gpio_rset->dev, sc->gpio_rset->pin,
		    GPIO_PIN_OUTPUT);
		if (error != 0) {
			device_printf(dev, "Cannot configure GPIO pin %d on %s\n",
			    sc->gpio_rset->pin, device_get_nameunit(sc->gpio_rset->dev));
			goto fail;
		}

		DELAY(2000);

		error = GPIO_PIN_SET(sc->gpio_rset->dev, sc->gpio_rset->pin, 1);
		if (error != 0) {
			device_printf(dev, "Cannot configure GPIO pin %d on %s\n",
			    sc->gpio_rset->pin, device_get_nameunit(sc->gpio_rset->dev));
			goto fail;
		}

		DELAY(4000);
	} else
		device_printf(dev, "Unable to find reset GPIO\n");

	sc->dme_tag = rman_get_bustag(sc->dme_res);
	sc->dme_handle = rman_get_bushandle(sc->dme_res);

	/* Reset the chip as soon as possible */
	dme_reset(sc);

	/* Figure IO mode */
	switch((dme_read_reg(sc, DME_ISR) >> 6) & 0x03) {
	case 0:
		/* 16 bit */
		sc->dme_bits = 16;
		break;
	case 1:
		/* 32 bit */
		sc->dme_bits = 32;
		break;
	case 2:
		/* 8 bit */
		sc->dme_bits = 8;
		break;
	default:
		/* reserved */
		device_printf(dev, "Unable to determine device mode\n");
		error = ENXIO;
		goto fail;
	}

	DELAY(100000);

	/* Read vendor and device id's */
	data = dme_read_reg(sc, DME_VIDH) << 8;
	data |= dme_read_reg(sc, DME_VIDL);
	device_printf(dev, "Vendor ID: 0x%04x\n", data);

	/* Read vendor and device id's */
	data = dme_read_reg(sc, DME_PIDH) << 8;
	data |= dme_read_reg(sc, DME_PIDL);
	device_printf(dev, "Product ID: 0x%04x\n", data);

	/* Chip revision */
	data = dme_read_reg(sc, DME_CHIPR);
	device_printf(dev, "Revision: 0x%04x\n", data);
	if (data != DME_CHIP_DM9000A && data != DME_CHIP_DM9000B)
		data = DME_CHIP_DM9000;
	sc->dme_rev = data;

	device_printf(dev, "using %d-bit IO mode\n", sc->dme_bits);
	KASSERT(sc->dme_bits == 8, ("wrong io mode"));

	/* Try to figure our mac address */
	dme_get_macaddr(sc);

	/* Configure chip after reset */
	dme_config(sc);

	ifp = sc->dme_ifp = if_alloc(IFT_ETHER);
	if (ifp == NULL) {
		device_printf(dev, "unable to allocate ifp\n");
		error = ENOSPC;
		goto fail;
	}
	ifp->if_softc = sc;

	/* Setup MII */
	error = mii_attach(dev, &sc->dme_miibus, ifp, dme_ifmedia_upd,
	    dme_ifmedia_sts, BMSR_DEFCAPMASK, MII_PHY_ANY, MII_OFFSET_ANY, 0);
	/* This should never happen as the DM9000 contains it's own PHY */
	if (error != 0) {
		device_printf(dev, "PHY probe failed\n");
		goto fail;
	}

	if_initname(ifp, device_get_name(dev), device_get_unit(dev));
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
	ifp->if_start = dme_start;
	ifp->if_ioctl = dme_ioctl;
	ifp->if_init = dme_init;
	IFQ_SET_MAXLEN(&ifp->if_snd, IFQ_MAXLEN);

	ether_ifattach(ifp, sc->dme_macaddr);

	error = bus_setup_intr(dev, sc->dme_irq, INTR_TYPE_NET | INTR_MPSAFE,
	    NULL, dme_intr, sc, &sc->dme_intrhand);
	if (error) {
		device_printf(dev, "couldn't set up irq\n");
		ether_ifdetach(ifp);
		goto fail;
	}

fail:
	if (error != 0)
		dme_detach(dev);
	return (error);
}