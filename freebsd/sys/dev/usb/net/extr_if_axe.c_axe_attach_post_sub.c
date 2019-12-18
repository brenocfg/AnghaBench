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
typedef  scalar_t__ u_int ;
struct usb_ether {TYPE_1__* ue_methods; int /*<<< orphan*/  ue_miibus; int /*<<< orphan*/  ue_dev; struct ifnet* ue_ifp; } ;
struct TYPE_5__ {int /*<<< orphan*/  ifq_drv_maxlen; } ;
struct ifnet {int if_flags; int if_capabilities; int if_capenable; int /*<<< orphan*/  if_hwassist; TYPE_2__ if_snd; int /*<<< orphan*/  if_init; int /*<<< orphan*/  if_ioctl; int /*<<< orphan*/  if_start; } ;
struct axe_softc {int sc_flags; int /*<<< orphan*/  sc_phyno; } ;
struct TYPE_4__ {int /*<<< orphan*/  ue_mii_sts; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXE_CSUM_FEATURES ; 
 int AXE_FLAG_178 ; 
 int AXE_FLAG_772A ; 
 int AXE_FLAG_772B ; 
 scalar_t__ AXE_IS_178_FAMILY (struct axe_softc*) ; 
 int /*<<< orphan*/  BMSR_DEFCAPMASK ; 
 int /*<<< orphan*/  Giant ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_TXCSUM ; 
 int IFCAP_VLAN_MTU ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int /*<<< orphan*/  IFQ_SET_MAXLEN (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFQ_SET_READY (TYPE_2__*) ; 
 scalar_t__ MIIF_DOPAUSE ; 
 int /*<<< orphan*/  MII_OFFSET_ANY ; 
 int /*<<< orphan*/  axe_ioctl ; 
 int /*<<< orphan*/  ifqmaxlen ; 
 int mii_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 struct axe_softc* uether_getsc (struct usb_ether*) ; 
 int /*<<< orphan*/  uether_ifmedia_upd ; 
 int /*<<< orphan*/  uether_init ; 
 int /*<<< orphan*/  uether_start ; 

__attribute__((used)) static int
axe_attach_post_sub(struct usb_ether *ue)
{
	struct axe_softc *sc;
	struct ifnet *ifp;
	u_int adv_pause;
	int error;

	sc = uether_getsc(ue);
	ifp = ue->ue_ifp;
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
	ifp->if_start = uether_start;
	ifp->if_ioctl = axe_ioctl;
	ifp->if_init = uether_init;
	IFQ_SET_MAXLEN(&ifp->if_snd, ifqmaxlen);
	ifp->if_snd.ifq_drv_maxlen = ifqmaxlen;
	IFQ_SET_READY(&ifp->if_snd);

	if (AXE_IS_178_FAMILY(sc))
		ifp->if_capabilities |= IFCAP_VLAN_MTU;
	if (sc->sc_flags & AXE_FLAG_772B) {
		ifp->if_capabilities |= IFCAP_TXCSUM | IFCAP_RXCSUM;
		ifp->if_hwassist = AXE_CSUM_FEATURES;
		/*
		 * Checksum offloading of AX88772B also works with VLAN
		 * tagged frames but there is no way to take advantage
		 * of the feature because vlan(4) assumes
		 * IFCAP_VLAN_HWTAGGING is prerequisite condition to
		 * support checksum offloading with VLAN. VLAN hardware
		 * tagging support of AX88772B is very limited so it's
		 * not possible to announce IFCAP_VLAN_HWTAGGING.
		 */
	}
	ifp->if_capenable = ifp->if_capabilities;
	if (sc->sc_flags & (AXE_FLAG_772A | AXE_FLAG_772B | AXE_FLAG_178))
		adv_pause = MIIF_DOPAUSE;
	else
		adv_pause = 0;
	mtx_lock(&Giant);
	error = mii_attach(ue->ue_dev, &ue->ue_miibus, ifp,
	    uether_ifmedia_upd, ue->ue_methods->ue_mii_sts,
	    BMSR_DEFCAPMASK, sc->sc_phyno, MII_OFFSET_ANY, adv_pause);
	mtx_unlock(&Giant);

	return (error);
}