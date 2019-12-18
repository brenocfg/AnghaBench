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
struct nf10bmac_softc {int /*<<< orphan*/ * nf10bmac_rx_irq_res; int /*<<< orphan*/  nf10bmac_rx_intrhand; int /*<<< orphan*/  nf10bmac_media; int /*<<< orphan*/  nf10bmac_eth_addr; struct ifnet* nf10bmac_ifp; int /*<<< orphan*/  nf10bmac_tx_buf; int /*<<< orphan*/  nf10bmac_mtx; int /*<<< orphan*/  nf10bmac_tick; } ;
struct TYPE_3__ {scalar_t__ ifq_drv_maxlen; } ;
struct ifnet {int if_flags; int if_hdrlen; int if_capabilities; int if_capenable; TYPE_1__ if_snd; int /*<<< orphan*/  if_init; int /*<<< orphan*/  if_start; int /*<<< orphan*/  if_ioctl; struct nf10bmac_softc* if_softc; } ;
struct ether_vlan_header {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOSPC ; 
 int ENXIO ; 
 int /*<<< orphan*/  ETHER_MAX_LEN_JUMBO ; 
 int IFCAP_POLLING ; 
 int IFCAP_VLAN_MTU ; 
 int IFF_BROADCAST ; 
 int IFF_SIMPLEX ; 
 int IFM_10G_T ; 
 int IFM_ETHER ; 
 int /*<<< orphan*/  IFQ_SET_MAXLEN (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  IFQ_SET_READY (TYPE_1__*) ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  MTX_NETWORK_LOCK ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ NF10BMAC_MAX_PKTS ; 
 int /*<<< orphan*/  NF10BMAC_RX_INTR_ENABLE (struct nf10bmac_softc*) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nf10bmac_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct nf10bmac_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int ether_poll_register (int /*<<< orphan*/ ,struct ifnet*) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_add (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifmedia_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf10bmac_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf10bmac_init ; 
 int /*<<< orphan*/  nf10bmac_intr ; 
 int /*<<< orphan*/  nf10bmac_ioctl ; 
 int /*<<< orphan*/  nf10bmac_media_change ; 
 int /*<<< orphan*/  nf10bmac_media_status ; 
 int /*<<< orphan*/  nf10bmac_poll ; 
 int /*<<< orphan*/  nf10bmac_reset (struct nf10bmac_softc*) ; 
 int /*<<< orphan*/  nf10bmac_start ; 

int
nf10bmac_attach(device_t dev)
{
	struct nf10bmac_softc *sc;
	struct ifnet *ifp;
	int error;

	sc = device_get_softc(dev);

	mtx_init(&sc->nf10bmac_mtx, device_get_nameunit(dev), MTX_NETWORK_LOCK,
	    MTX_DEF);

#ifdef	ENABLE_WATCHDOG
	callout_init_mtx(&sc->nf10bmac_tick, &sc->nf10bmac_mtx, 0);
#endif

	sc->nf10bmac_tx_buf = malloc(ETHER_MAX_LEN_JUMBO, M_DEVBUF, M_WAITOK);

	/* Reset the adapter. */
	nf10bmac_reset(sc);

	/* Setup interface. */
	ifp = sc->nf10bmac_ifp = if_alloc(IFT_ETHER);
	if (ifp == NULL) {   
		device_printf(dev, "if_alloc() failed\n");
		error = ENOSPC;
		goto err;
	}
	ifp->if_softc = sc;
	if_initname(ifp, device_get_name(dev), device_get_unit(dev));
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX; /* | IFF_MULTICAST; */
	ifp->if_ioctl = nf10bmac_ioctl;
	ifp->if_start = nf10bmac_start;
	ifp->if_init = nf10bmac_init;
	IFQ_SET_MAXLEN(&ifp->if_snd, NF10BMAC_MAX_PKTS - 1);
	ifp->if_snd.ifq_drv_maxlen = NF10BMAC_MAX_PKTS - 1;
	IFQ_SET_READY(&ifp->if_snd);

	/* Call media-indepedent attach routine. */
	ether_ifattach(ifp, sc->nf10bmac_eth_addr);

	/* Tell the upper layer(s) about vlan mtu support. */
	ifp->if_hdrlen = sizeof(struct ether_vlan_header);
	ifp->if_capabilities |= IFCAP_VLAN_MTU;
	ifp->if_capenable = ifp->if_capabilities;
#ifdef DEVICE_POLLING
	/* We will enable polling by default if no irqs available. See below. */
	ifp->if_capabilities |= IFCAP_POLLING;
#endif

	/* We need more media attention.  Fake it! */
        ifmedia_init(&sc->nf10bmac_media, 0, nf10bmac_media_change,
	    nf10bmac_media_status);
        ifmedia_add(&sc->nf10bmac_media, IFM_ETHER | IFM_10G_T, 0, NULL);
        ifmedia_set(&sc->nf10bmac_media, IFM_ETHER | IFM_10G_T);

	/* Initialise. */
	error = 0;

	/* Hook up interrupts. Well the one. */
	if (sc->nf10bmac_rx_irq_res != NULL) {
		error = bus_setup_intr(dev, sc->nf10bmac_rx_irq_res,
		    INTR_TYPE_NET | INTR_MPSAFE, NULL, nf10bmac_intr,
		    sc, &sc->nf10bmac_rx_intrhand);
		if (error != 0) {
			device_printf(dev, "enabling RX IRQ failed\n");
			ether_ifdetach(ifp);
			goto err;
		}
	}

	if ((ifp->if_capenable & IFCAP_POLLING) != 0 ||
	    sc->nf10bmac_rx_irq_res == NULL) {
#ifdef DEVICE_POLLING
		/* If not on and no IRQs force it on. */
		if (sc->nf10bmac_rx_irq_res == NULL) {
			ifp->if_capenable |= IFCAP_POLLING;
			device_printf(dev,
			    "forcing to polling due to no interrupts\n");
		}
		error = ether_poll_register(nf10bmac_poll, ifp);
		if (error != 0)
			goto err;
#else
		device_printf(dev, "no DEVICE_POLLING in kernel and no IRQs\n");
		error = ENXIO;
#endif
	} else {
		NF10BMAC_RX_INTR_ENABLE(sc);
	}

err:
	if (error != 0)
		nf10bmac_detach(dev);

	return (error);                                                                                                                                                                      
}