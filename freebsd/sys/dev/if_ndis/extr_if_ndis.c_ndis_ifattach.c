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
typedef  int /*<<< orphan*/  u_char ;
struct ndis_softc {int /*<<< orphan*/  ifmedia; int /*<<< orphan*/  ndis_hwassist; int /*<<< orphan*/  ndis_dev; struct ifnet* ifp; } ;
struct TYPE_3__ {int ifq_drv_maxlen; } ;
struct ifnet {int if_flags; int if_baudrate; int /*<<< orphan*/  if_hwassist; int /*<<< orphan*/  if_capabilities; int /*<<< orphan*/  if_capenable; TYPE_1__ if_snd; int /*<<< orphan*/  if_init; int /*<<< orphan*/  if_start; int /*<<< orphan*/  if_ioctl; struct ndis_softc* if_softc; } ;
typedef  int /*<<< orphan*/  eaddr ;

/* Variables and functions */
 int ENOSPC ; 
 int ETHER_ADDR_LEN ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int IFM_100_TX ; 
 int IFM_10_T ; 
 int IFM_AUTO ; 
 int IFM_ETHER ; 
 int IFM_FDX ; 
 int /*<<< orphan*/  IFM_IMASK ; 
 int /*<<< orphan*/  IFQ_SET_MAXLEN (TYPE_1__*,int) ; 
 int /*<<< orphan*/  IFQ_SET_READY (TYPE_1__*) ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int /*<<< orphan*/  OID_802_3_CURRENT_ADDRESS ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int /*<<< orphan*/ *) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_add (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifmedia_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ndis_get_info (struct ndis_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ndis_ifioctl ; 
 int /*<<< orphan*/  ndis_ifmedia_sts ; 
 int /*<<< orphan*/  ndis_ifmedia_upd ; 
 int /*<<< orphan*/  ndis_ifstart ; 
 int /*<<< orphan*/  ndis_init ; 
 int /*<<< orphan*/  ndis_probe_offload (struct ndis_softc*) ; 

__attribute__((used)) static int
ndis_ifattach(struct ndis_softc *sc)
{
	struct ifnet *ifp;
	u_char eaddr[ETHER_ADDR_LEN];
	int len;

	ifp = if_alloc(IFT_ETHER);
	if (ifp == NULL)
		return (ENOSPC);
	sc->ifp = ifp;
	ifp->if_softc = sc;

	/* Check for task offload support. */
	ndis_probe_offload(sc);

	/*
	 * Get station address from the driver.
	 */
	len = sizeof(eaddr);
	ndis_get_info(sc, OID_802_3_CURRENT_ADDRESS, eaddr, &len);

	if_initname(ifp, device_get_name(sc->ndis_dev),
	    device_get_unit(sc->ndis_dev));
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
	ifp->if_ioctl = ndis_ifioctl;
	ifp->if_start = ndis_ifstart;
	ifp->if_init = ndis_init;
	ifp->if_baudrate = 10000000;
	IFQ_SET_MAXLEN(&ifp->if_snd, 50);
	ifp->if_snd.ifq_drv_maxlen = 25;
	IFQ_SET_READY(&ifp->if_snd);
	ifp->if_capenable = ifp->if_capabilities;
	ifp->if_hwassist = sc->ndis_hwassist;

	ifmedia_init(&sc->ifmedia, IFM_IMASK, ndis_ifmedia_upd,
	    ndis_ifmedia_sts);
	ifmedia_add(&sc->ifmedia, IFM_ETHER|IFM_10_T, 0, NULL);
	ifmedia_add(&sc->ifmedia, IFM_ETHER|IFM_10_T|IFM_FDX, 0, NULL);
	ifmedia_add(&sc->ifmedia, IFM_ETHER|IFM_100_TX, 0, NULL);
	ifmedia_add(&sc->ifmedia, IFM_ETHER|IFM_100_TX|IFM_FDX, 0, NULL);
	ifmedia_add(&sc->ifmedia, IFM_ETHER|IFM_AUTO, 0, NULL);
	ifmedia_set(&sc->ifmedia, IFM_ETHER|IFM_AUTO);
	ether_ifattach(ifp, eaddr);

	return (0);
}