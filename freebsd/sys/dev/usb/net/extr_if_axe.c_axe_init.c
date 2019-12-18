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
typedef  int uint16_t ;
struct usb_ether {int dummy; } ;
struct ifnet {int if_drv_flags; int if_capenable; int if_flags; } ;
struct axe_softc {int* sc_ipgs; int sc_flags; int /*<<< orphan*/ * sc_xfer; int /*<<< orphan*/  sc_lenmask; } ;
struct TYPE_2__ {int threshold; int byte_cnt; } ;

/* Variables and functions */
 size_t AX88772B_MFB_16K ; 
 int /*<<< orphan*/  AXE_172_CMD_WRITE_IPG0 ; 
 int /*<<< orphan*/  AXE_172_CMD_WRITE_IPG1 ; 
 int /*<<< orphan*/  AXE_172_CMD_WRITE_IPG2 ; 
 int /*<<< orphan*/  AXE_172_CMD_WRITE_NODEID ; 
 int AXE_172_RXCMD_UNICAST ; 
 int /*<<< orphan*/  AXE_178_CMD_WRITE_IPG012 ; 
 int /*<<< orphan*/  AXE_178_CMD_WRITE_NODEID ; 
 int AXE_178_RXCMD_MFB_16384 ; 
 int /*<<< orphan*/  AXE_772B_CMD_RXCTL_WRITE_CFG ; 
 int AXE_772B_RXCMD_HDR_TYPE_1 ; 
 int AXE_772B_RXCMD_IPHDR_ALIGN ; 
 size_t AXE_BULK_DT_WR ; 
 int /*<<< orphan*/  AXE_CMD_RXCTL_WRITE ; 
 int /*<<< orphan*/  AXE_CSUM_HDR_LEN_MASK ; 
 int AXE_FLAG_772B ; 
 int AXE_FLAG_CSUM_FRAME ; 
 int AXE_FLAG_STD_FRAME ; 
 int /*<<< orphan*/  AXE_HDR_LEN_MASK ; 
 scalar_t__ AXE_IS_178_FAMILY (struct axe_softc*) ; 
 int /*<<< orphan*/  AXE_LOCK_ASSERT (struct axe_softc*,int /*<<< orphan*/ ) ; 
 int AXE_RXCMD_BROADCAST ; 
 int AXE_RXCMD_ENABLE ; 
 int AXE_RXCMD_MULTICAST ; 
 int AXE_RXCMD_PROMISC ; 
 int IFCAP_RXCSUM ; 
 int IFF_BROADCAST ; 
 int IFF_DRV_RUNNING ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/ * IF_LLADDR (struct ifnet*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 TYPE_1__* ax88772b_mfb_table ; 
 int /*<<< orphan*/  axe_cmd (struct axe_softc*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  axe_csum_cfg (struct usb_ether*) ; 
 int /*<<< orphan*/  axe_ifmedia_upd (struct ifnet*) ; 
 int /*<<< orphan*/  axe_reset (struct axe_softc*) ; 
 int /*<<< orphan*/  axe_setmulti (struct usb_ether*) ; 
 int /*<<< orphan*/  axe_stop (struct usb_ether*) ; 
 struct ifnet* uether_getifp (struct usb_ether*) ; 
 struct axe_softc* uether_getsc (struct usb_ether*) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
axe_init(struct usb_ether *ue)
{
	struct axe_softc *sc = uether_getsc(ue);
	struct ifnet *ifp = uether_getifp(ue);
	uint16_t rxmode;

	AXE_LOCK_ASSERT(sc, MA_OWNED);

	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0)
		return;

	/* Cancel pending I/O */
	axe_stop(ue);

	axe_reset(sc);

	/* Set MAC address and transmitter IPG values. */
	if (AXE_IS_178_FAMILY(sc)) {
		axe_cmd(sc, AXE_178_CMD_WRITE_NODEID, 0, 0, IF_LLADDR(ifp));
		axe_cmd(sc, AXE_178_CMD_WRITE_IPG012, sc->sc_ipgs[2],
		    (sc->sc_ipgs[1] << 8) | (sc->sc_ipgs[0]), NULL);
	} else {
		axe_cmd(sc, AXE_172_CMD_WRITE_NODEID, 0, 0, IF_LLADDR(ifp));
		axe_cmd(sc, AXE_172_CMD_WRITE_IPG0, 0, sc->sc_ipgs[0], NULL);
		axe_cmd(sc, AXE_172_CMD_WRITE_IPG1, 0, sc->sc_ipgs[1], NULL);
		axe_cmd(sc, AXE_172_CMD_WRITE_IPG2, 0, sc->sc_ipgs[2], NULL);
	}

	if (AXE_IS_178_FAMILY(sc)) {
		sc->sc_flags &= ~(AXE_FLAG_STD_FRAME | AXE_FLAG_CSUM_FRAME);
		if ((sc->sc_flags & AXE_FLAG_772B) != 0 &&
		    (ifp->if_capenable & IFCAP_RXCSUM) != 0) {
			sc->sc_lenmask = AXE_CSUM_HDR_LEN_MASK;
			sc->sc_flags |= AXE_FLAG_CSUM_FRAME;
		} else {
			sc->sc_lenmask = AXE_HDR_LEN_MASK;
			sc->sc_flags |= AXE_FLAG_STD_FRAME;
		}
	}

	/* Configure TX/RX checksum offloading. */
	axe_csum_cfg(ue);

	if (sc->sc_flags & AXE_FLAG_772B) {
		/* AX88772B uses different maximum frame burst configuration. */
		axe_cmd(sc, AXE_772B_CMD_RXCTL_WRITE_CFG,
		    ax88772b_mfb_table[AX88772B_MFB_16K].threshold,
		    ax88772b_mfb_table[AX88772B_MFB_16K].byte_cnt, NULL);
	}

	/* Enable receiver, set RX mode. */
	rxmode = (AXE_RXCMD_MULTICAST | AXE_RXCMD_ENABLE);
	if (AXE_IS_178_FAMILY(sc)) {
		if (sc->sc_flags & AXE_FLAG_772B) {
			/*
			 * Select RX header format type 1.  Aligning IP
			 * header on 4 byte boundary is not needed when
			 * checksum offloading feature is not used
			 * because we always copy the received frame in
			 * RX handler.  When RX checksum offloading is
			 * active, aligning IP header is required to
			 * reflect actual frame length including RX
			 * header size.
			 */
			rxmode |= AXE_772B_RXCMD_HDR_TYPE_1;
			if ((ifp->if_capenable & IFCAP_RXCSUM) != 0)
				rxmode |= AXE_772B_RXCMD_IPHDR_ALIGN;
		} else {
			/*
			 * Default Rx buffer size is too small to get
			 * maximum performance.
			 */
			rxmode |= AXE_178_RXCMD_MFB_16384;
		}
	} else {
		rxmode |= AXE_172_RXCMD_UNICAST;
	}

	/* If we want promiscuous mode, set the allframes bit. */
	if (ifp->if_flags & IFF_PROMISC)
		rxmode |= AXE_RXCMD_PROMISC;

	if (ifp->if_flags & IFF_BROADCAST)
		rxmode |= AXE_RXCMD_BROADCAST;

	axe_cmd(sc, AXE_CMD_RXCTL_WRITE, 0, rxmode, NULL);

	/* Load the multicast filter. */
	axe_setmulti(ue);

	usbd_xfer_set_stall(sc->sc_xfer[AXE_BULK_DT_WR]);

	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	/* Switch to selected media. */
	axe_ifmedia_upd(ifp);
}