#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_ether {TYPE_1__* ue_methods; int /*<<< orphan*/  ue_miibus; int /*<<< orphan*/  ue_dev; struct ifnet* ue_ifp; } ;
struct muge_softc {int /*<<< orphan*/  sc_phyno; } ;
struct TYPE_5__ {int /*<<< orphan*/  ifq_drv_maxlen; } ;
struct ifnet {int if_flags; int if_capabilities; int if_hwassist; int if_capenable; TYPE_2__ if_snd; int /*<<< orphan*/  if_init; int /*<<< orphan*/  if_ioctl; int /*<<< orphan*/  if_start; } ;
struct TYPE_4__ {int /*<<< orphan*/  ue_mii_sts; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMSR_DEFCAPMASK ; 
 int CSUM_TCP ; 
 int CSUM_UDP ; 
 int /*<<< orphan*/  Giant ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_TSO4 ; 
 int IFCAP_TSO6 ; 
 int IFCAP_TXCSUM ; 
 int IFCAP_VLAN_MTU ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int /*<<< orphan*/  IFQ_SET_MAXLEN (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFQ_SET_READY (TYPE_2__*) ; 
 int /*<<< orphan*/  MII_OFFSET_ANY ; 
 scalar_t__ MUGE_DEFAULT_RX_CSUM_ENABLE ; 
 scalar_t__ MUGE_DEFAULT_TSO_CSUM_ENABLE ; 
 scalar_t__ MUGE_DEFAULT_TX_CSUM_ENABLE ; 
 int /*<<< orphan*/  ifqmaxlen ; 
 int mii_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  muge_dbg_printf (struct muge_softc*,char*) ; 
 int /*<<< orphan*/  muge_ioctl ; 
 struct muge_softc* uether_getsc (struct usb_ether*) ; 
 int /*<<< orphan*/  uether_ifmedia_upd ; 
 int /*<<< orphan*/  uether_init ; 
 int /*<<< orphan*/  uether_start ; 

__attribute__((used)) static int
muge_attach_post_sub(struct usb_ether *ue)
{
	struct muge_softc *sc;
	struct ifnet *ifp;
	int error;

	sc = uether_getsc(ue);
	muge_dbg_printf(sc, "Calling muge_attach_post_sub.\n");
	ifp = ue->ue_ifp;
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
	ifp->if_start = uether_start;
	ifp->if_ioctl = muge_ioctl;
	ifp->if_init = uether_init;
	IFQ_SET_MAXLEN(&ifp->if_snd, ifqmaxlen);
	ifp->if_snd.ifq_drv_maxlen = ifqmaxlen;
	IFQ_SET_READY(&ifp->if_snd);

	/*
	 * The chip supports TCP/UDP checksum offloading on TX and RX paths,
	 * however currently only RX checksum is supported in the driver
	 * (see top of file).
	 */
	ifp->if_capabilities |= IFCAP_VLAN_MTU;
	ifp->if_hwassist = 0;
	if (MUGE_DEFAULT_RX_CSUM_ENABLE)
		ifp->if_capabilities |= IFCAP_RXCSUM;

	if (MUGE_DEFAULT_TX_CSUM_ENABLE)
		ifp->if_capabilities |= IFCAP_TXCSUM;

	/*
	 * In the Linux driver they also enable scatter/gather (NETIF_F_SG)
	 * here, that's something related to socket buffers used in Linux.
	 * FreeBSD doesn't have that as an interface feature.
	 */
	if (MUGE_DEFAULT_TSO_CSUM_ENABLE)
		ifp->if_capabilities |= IFCAP_TSO4 | IFCAP_TSO6;

#if 0
	/* TX checksuming is disabled since not yet implemented. */
	ifp->if_capabilities |= IFCAP_TXCSUM;
	ifp->if_capenable |= IFCAP_TXCSUM;
	ifp->if_hwassist = CSUM_TCP | CSUM_UDP;
#endif

	ifp->if_capenable = ifp->if_capabilities;

	mtx_lock(&Giant);
	error = mii_attach(ue->ue_dev, &ue->ue_miibus, ifp,
		uether_ifmedia_upd, ue->ue_methods->ue_mii_sts,
		BMSR_DEFCAPMASK, sc->sc_phyno, MII_OFFSET_ANY, 0);
	mtx_unlock(&Giant);

	return (0);
}