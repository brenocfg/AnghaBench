#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ifq_maxlen; } ;
struct ifnet {int if_flags; int /*<<< orphan*/  if_capabilities; int /*<<< orphan*/  if_capenable; TYPE_1__ if_snd; int /*<<< orphan*/  if_init; int /*<<< orphan*/  if_start; int /*<<< orphan*/  if_ioctl; struct fv_softc* if_softc; } ;
struct fv_softc {int* fv_eaddr; int fv_rid; int /*<<< orphan*/  fv_intrhand; int /*<<< orphan*/ * fv_irq; int /*<<< orphan*/  fv_ifmedia; int /*<<< orphan*/  fv_miibus; int /*<<< orphan*/  fv_dev; int /*<<< orphan*/  fv_miiproxy; struct ifnet* fv_ifp; int /*<<< orphan*/ * fv_res; int /*<<< orphan*/  fv_bhandle; int /*<<< orphan*/  fv_btag; int /*<<< orphan*/  fv_link_task; int /*<<< orphan*/  fv_mtx; int /*<<< orphan*/  fv_stat_callout; int /*<<< orphan*/  fv_ofw; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BMSR_DEFCAPMASK ; 
 int /*<<< orphan*/  BUSMODE_SWR ; 
 int /*<<< orphan*/  CSR_BUSMODE ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct fv_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENOSPC ; 
 int ENXIO ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int IFM_AUTO ; 
 int IFM_ETHER ; 
 int /*<<< orphan*/  IFQ_SET_MAXLEN (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFQ_SET_READY (TYPE_1__*) ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int /*<<< orphan*/  MII_OFFSET_ANY ; 
 int /*<<< orphan*/  MII_PHY_ANY ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  MTX_NETWORK_LOCK ; 
 int OF_getprop (int /*<<< orphan*/ ,char*,void*,int) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fv_softc*) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct fv_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct fv_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int*) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  fv_detach (int /*<<< orphan*/ ) ; 
 scalar_t__ fv_dma_alloc (struct fv_softc*) ; 
 int /*<<< orphan*/  fv_ifmedia_sts ; 
 int /*<<< orphan*/  fv_ifmedia_upd ; 
 int /*<<< orphan*/  fv_init ; 
 int /*<<< orphan*/  fv_intr ; 
 int /*<<< orphan*/  fv_ioctl ; 
 int /*<<< orphan*/  fv_link_task ; 
 int /*<<< orphan*/  fv_start ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ifmedia_add (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifmedia_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ifqmaxlen ; 
 int mii_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_attach_proxy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
fv_attach(device_t dev)
{
	struct ifnet		*ifp;
	struct fv_softc		*sc;
	int			error = 0, rid;
	int			unit;
	int			i;

	sc = device_get_softc(dev);
	unit = device_get_unit(dev);
	sc->fv_dev = dev;
	sc->fv_ofw = ofw_bus_get_node(dev); 

	i = OF_getprop(sc->fv_ofw, "local-mac-address", (void *)&sc->fv_eaddr, 6);
	if (i != 6) {
		/* hardcode macaddress */
		sc->fv_eaddr[0] = 0x00;
		sc->fv_eaddr[1] = 0x0C;
		sc->fv_eaddr[2] = 0x42;
		sc->fv_eaddr[3] = 0x09;
		sc->fv_eaddr[4] = 0x5E;
		sc->fv_eaddr[5] = 0x6B;
	}

	mtx_init(&sc->fv_mtx, device_get_nameunit(dev), MTX_NETWORK_LOCK,
	    MTX_DEF);
	callout_init_mtx(&sc->fv_stat_callout, &sc->fv_mtx, 0);
	TASK_INIT(&sc->fv_link_task, 0, fv_link_task, sc);

	/* Map control/status registers. */
	sc->fv_rid = 0;
	sc->fv_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &sc->fv_rid, 
	    RF_ACTIVE | RF_SHAREABLE);

	if (sc->fv_res == NULL) {
		device_printf(dev, "couldn't map memory\n");
		error = ENXIO;
		goto fail;
	}

	sc->fv_btag = rman_get_bustag(sc->fv_res);
	sc->fv_bhandle = rman_get_bushandle(sc->fv_res);

	/* Allocate interrupts */
	rid = 0;
	sc->fv_irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid, 
	    RF_SHAREABLE | RF_ACTIVE);

	if (sc->fv_irq == NULL) {
		device_printf(dev, "couldn't map interrupt\n");
		error = ENXIO;
		goto fail;
	}

	/* Allocate ifnet structure. */
	ifp = sc->fv_ifp = if_alloc(IFT_ETHER);

	if (ifp == NULL) {
		device_printf(dev, "couldn't allocate ifnet structure\n");
		error = ENOSPC;
		goto fail;
	}
	ifp->if_softc = sc;
	if_initname(ifp, device_get_name(dev), device_get_unit(dev));
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
	ifp->if_ioctl = fv_ioctl;
	ifp->if_start = fv_start;
	ifp->if_init = fv_init;

	/* ifqmaxlen is sysctl value in net/if.c */
	IFQ_SET_MAXLEN(&ifp->if_snd, ifqmaxlen);
	ifp->if_snd.ifq_maxlen = ifqmaxlen;
	IFQ_SET_READY(&ifp->if_snd);

	ifp->if_capenable = ifp->if_capabilities;

	if (fv_dma_alloc(sc) != 0) {
		error = ENXIO;
		goto fail;
	}

	/* TODO: calculate prescale */
/*
	CSR_WRITE_4(sc, FV_ETHMCP, (165000000 / (1250000 + 1)) & ~1);

	CSR_WRITE_4(sc, FV_MIIMCFG, FV_MIIMCFG_R);
	DELAY(1000);
	CSR_WRITE_4(sc, FV_MIIMCFG, 0);
*/
	CSR_WRITE_4(sc, CSR_BUSMODE, BUSMODE_SWR);
	DELAY(1000);

#ifdef FV_MDIO
	sc->fv_miiproxy = mii_attach_proxy(sc->fv_dev);
#endif

#ifdef MII
	/* Do MII setup. */
	error = mii_attach(dev, &sc->fv_miibus, ifp, fv_ifmedia_upd,
	    fv_ifmedia_sts, BMSR_DEFCAPMASK, MII_PHY_ANY, MII_OFFSET_ANY, 0);
	if (error != 0) {
		device_printf(dev, "attaching PHYs failed\n");
		goto fail;
	}
#else
	ifmedia_init(&sc->fv_ifmedia, 0, fv_ifmedia_upd, fv_ifmedia_sts);

	ifmedia_add(&sc->fv_ifmedia, IFM_ETHER | IFM_AUTO, 0, NULL);
	ifmedia_set(&sc->fv_ifmedia, IFM_ETHER | IFM_AUTO);
#endif

	/* Call MI attach routine. */
	ether_ifattach(ifp, sc->fv_eaddr);

	/* Hook interrupt last to avoid having to lock softc */
	error = bus_setup_intr(dev, sc->fv_irq, INTR_TYPE_NET | INTR_MPSAFE,
	    NULL, fv_intr, sc, &sc->fv_intrhand);

	if (error) {
		device_printf(dev, "couldn't set up irq\n");
		ether_ifdetach(ifp);
		goto fail;
	}

fail:
	if (error) 
		fv_detach(dev);

	return (error);
}