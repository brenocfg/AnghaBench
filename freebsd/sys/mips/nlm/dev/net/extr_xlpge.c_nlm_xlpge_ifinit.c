#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_1__* ifm_cur; int /*<<< orphan*/  ifm_media; } ;
struct TYPE_10__ {TYPE_4__ mii_media; } ;
struct nlm_xlpge_softc {int block; int port; int if_flags; int /*<<< orphan*/  dev_addr; TYPE_2__ xlpge_mii; struct ifnet* xlpge_if; int /*<<< orphan*/  xlpge_dev; } ;
struct TYPE_13__ {int /*<<< orphan*/  ifq_drv_maxlen; } ;
struct ifnet {int if_flags; int /*<<< orphan*/  if_transmit; TYPE_7__ if_snd; scalar_t__ if_hwassist; int /*<<< orphan*/  if_init; int /*<<< orphan*/  if_ioctl; scalar_t__ if_capabilities; scalar_t__ if_capenable; struct nlm_xlpge_softc* if_softc; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_11__ {struct ifnet* xlpge_if; } ;
struct TYPE_9__ {int /*<<< orphan*/  ifm_media; } ;

/* Variables and functions */
 int ENOSPC ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int IFM_AUTO ; 
 int IFM_ETHER ; 
 int /*<<< orphan*/  IFQ_SET_MAXLEN (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFQ_SET_READY (TYPE_7__*) ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int /*<<< orphan*/  NLM_XLPGE_TXQ_SIZE ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int /*<<< orphan*/ ) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_add (TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifmedia_init (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_set (TYPE_4__*,int) ; 
 TYPE_3__* ifp_ports ; 
 int /*<<< orphan*/  nlm_xlpge_init ; 
 int /*<<< orphan*/  nlm_xlpge_ioctl ; 
 int /*<<< orphan*/  xlpge_mediachange ; 
 int /*<<< orphan*/  xlpge_mediastatus ; 
 int /*<<< orphan*/  xlpge_read_mac_addr (struct nlm_xlpge_softc*) ; 
 int /*<<< orphan*/  xlpge_tx ; 

__attribute__((used)) static int
nlm_xlpge_ifinit(struct nlm_xlpge_softc *sc)
{
	struct ifnet *ifp;
	device_t dev;
	int port = sc->block * 4 + sc->port;

	dev = sc->xlpge_dev;
	ifp = sc->xlpge_if = if_alloc(IFT_ETHER);
	/*(sc->network_sc)->ifp_ports[port].xlpge_if = ifp;*/
	ifp_ports[port].xlpge_if = ifp;

	if (ifp == NULL) {
		device_printf(dev, "cannot if_alloc()\n");
		return (ENOSPC);
	}
	ifp->if_softc = sc;
	if_initname(ifp, device_get_name(dev), device_get_unit(dev));
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
	sc->if_flags = ifp->if_flags;
	/*ifp->if_capabilities = IFCAP_TXCSUM | IFCAP_VLAN_HWTAGGING;*/
	ifp->if_capabilities = 0;
	ifp->if_capenable = ifp->if_capabilities;
	ifp->if_ioctl = nlm_xlpge_ioctl;
	ifp->if_init  = nlm_xlpge_init ;
	ifp->if_hwassist = 0;
	ifp->if_snd.ifq_drv_maxlen = NLM_XLPGE_TXQ_SIZE; /* TODO: make this a sysint */
	IFQ_SET_MAXLEN(&ifp->if_snd, ifp->if_snd.ifq_drv_maxlen);
	IFQ_SET_READY(&ifp->if_snd);

	ifmedia_init(&sc->xlpge_mii.mii_media, 0, xlpge_mediachange,
	    xlpge_mediastatus);
	ifmedia_add(&sc->xlpge_mii.mii_media, IFM_ETHER | IFM_AUTO, 0, NULL);
	ifmedia_set(&sc->xlpge_mii.mii_media, IFM_ETHER | IFM_AUTO);
	sc->xlpge_mii.mii_media.ifm_media =
	    sc->xlpge_mii.mii_media.ifm_cur->ifm_media;
	xlpge_read_mac_addr(sc);

	ether_ifattach(ifp, sc->dev_addr);

	/* override if_transmit : per ifnet(9), do it after if_attach */
	ifp->if_transmit = xlpge_tx;

	return (0);
}