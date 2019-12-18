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
typedef  int /*<<< orphan*/  uint8_t ;
struct ifnet {int if_flags; int /*<<< orphan*/  if_transmit; int /*<<< orphan*/  if_ioctl; struct gx_softc* if_softc; int /*<<< orphan*/  if_init; int /*<<< orphan*/  if_mtu; } ;
struct gx_softc {int sc_flags; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_ifmedia; struct ifnet* sc_ifp; int /*<<< orphan*/ * sc_intr; int /*<<< orphan*/  sc_intr_cookie; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_port; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  ETHERMTU ; 
 scalar_t__ GXEMUL_ETHER_DEV_IRQ ; 
 int /*<<< orphan*/  GXEMUL_ETHER_DEV_MAC ; 
 int /*<<< orphan*/  GXEMUL_ETHER_DEV_WRITE (int /*<<< orphan*/ ,uintptr_t) ; 
 int IFF_ALLMULTI ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int IFM_AUTO ; 
 int IFM_ETHER ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int /*<<< orphan*/  INTR_TYPE_NET ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/ * bus_alloc_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_describe_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct gx_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 struct gx_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gx_init ; 
 int /*<<< orphan*/  gx_ioctl ; 
 int /*<<< orphan*/  gx_medchange ; 
 int /*<<< orphan*/  gx_medstat ; 
 int /*<<< orphan*/  gx_rx_intr ; 
 int /*<<< orphan*/  gx_transmit ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_add (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifmedia_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gx_attach(device_t dev)
{
	struct ifnet *ifp;
	struct gx_softc *sc;
	uint8_t mac[6];
	int error;
	int rid;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;
	sc->sc_port = device_get_unit(dev);

	/* Read MAC address.  */
	GXEMUL_ETHER_DEV_WRITE(GXEMUL_ETHER_DEV_MAC, (uintptr_t)mac);

	/* Allocate and establish interrupt.  */
	rid = 0;
	sc->sc_intr = bus_alloc_resource(sc->sc_dev, SYS_RES_IRQ, &rid,
	    GXEMUL_ETHER_DEV_IRQ - 2, GXEMUL_ETHER_DEV_IRQ - 2, 1, RF_ACTIVE);
	if (sc->sc_intr == NULL) {
		device_printf(dev, "unable to allocate IRQ.\n");
		return (ENXIO);
	}

	error = bus_setup_intr(sc->sc_dev, sc->sc_intr, INTR_TYPE_NET, NULL,
	    gx_rx_intr, sc, &sc->sc_intr_cookie);
	if (error != 0) {
		device_printf(dev, "unable to setup interrupt.\n");
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->sc_intr);
		return (ENXIO);
	}

	bus_describe_intr(sc->sc_dev, sc->sc_intr, sc->sc_intr_cookie, "rx");

	ifp = if_alloc(IFT_ETHER);
	if (ifp == NULL) {
		device_printf(dev, "cannot allocate ifnet.\n");
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->sc_intr);
		return (ENOMEM);
	}

	if_initname(ifp, device_get_name(dev), device_get_unit(dev));
	ifp->if_mtu = ETHERMTU;
	ifp->if_init = gx_init;
	ifp->if_softc = sc;
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST | IFF_ALLMULTI;
	ifp->if_ioctl = gx_ioctl;

	sc->sc_ifp = ifp;
	sc->sc_flags = ifp->if_flags;

	ifmedia_init(&sc->sc_ifmedia, 0, gx_medchange, gx_medstat);

	ifmedia_add(&sc->sc_ifmedia, IFM_ETHER | IFM_AUTO, 0, NULL);
	ifmedia_set(&sc->sc_ifmedia, IFM_ETHER | IFM_AUTO);

	mtx_init(&sc->sc_mtx, "GXemul Ethernet", NULL, MTX_DEF);

	ether_ifattach(ifp, mac);

	ifp->if_transmit = gx_transmit;

	return (bus_generic_attach(dev));
}