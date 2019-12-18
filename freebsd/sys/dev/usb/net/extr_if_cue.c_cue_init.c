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
struct usb_ether {int dummy; } ;
struct ifnet {int /*<<< orphan*/  if_drv_flags; } ;
struct cue_softc {int /*<<< orphan*/ * sc_xfer; } ;

/* Variables and functions */
 scalar_t__ CUE_ADVANCED_OPMODES ; 
 int CUE_AOP_EMBED_RXLEN ; 
 size_t CUE_BULK_DT_WR ; 
 scalar_t__ CUE_ETHCTL ; 
 int CUE_ETHCTL_MCAST_ON ; 
 int CUE_ETHCTL_RX_ON ; 
 scalar_t__ CUE_LEDCTL ; 
 int CUE_LEDCTL_FOLLOW_LINK ; 
 int /*<<< orphan*/  CUE_LOCK_ASSERT (struct cue_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ CUE_PAR0 ; 
 scalar_t__ CUE_RX_BUFPKTS ; 
 int CUE_RX_FRAMES ; 
 scalar_t__ CUE_TX_BUFPKTS ; 
 int CUE_TX_FRAMES ; 
 int ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int* IF_LLADDR (struct ifnet*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  cue_csr_write_1 (struct cue_softc*,scalar_t__,int) ; 
 int /*<<< orphan*/  cue_reset (struct cue_softc*) ; 
 int /*<<< orphan*/  cue_setpromisc (struct usb_ether*) ; 
 int /*<<< orphan*/  cue_start (struct usb_ether*) ; 
 int /*<<< orphan*/  cue_stop (struct usb_ether*) ; 
 struct ifnet* uether_getifp (struct usb_ether*) ; 
 struct cue_softc* uether_getsc (struct usb_ether*) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cue_init(struct usb_ether *ue)
{
	struct cue_softc *sc = uether_getsc(ue);
	struct ifnet *ifp = uether_getifp(ue);
	int i;

	CUE_LOCK_ASSERT(sc, MA_OWNED);

	/*
	 * Cancel pending I/O and free all RX/TX buffers.
	 */
	cue_stop(ue);
#if 0
	cue_reset(sc);
#endif
	/* Set MAC address */
	for (i = 0; i < ETHER_ADDR_LEN; i++)
		cue_csr_write_1(sc, CUE_PAR0 - i, IF_LLADDR(ifp)[i]);

	/* Enable RX logic. */
	cue_csr_write_1(sc, CUE_ETHCTL, CUE_ETHCTL_RX_ON | CUE_ETHCTL_MCAST_ON);

	/* Load the multicast filter */
	cue_setpromisc(ue);

	/*
	 * Set the number of RX and TX buffers that we want
	 * to reserve inside the ASIC.
	 */
	cue_csr_write_1(sc, CUE_RX_BUFPKTS, CUE_RX_FRAMES);
	cue_csr_write_1(sc, CUE_TX_BUFPKTS, CUE_TX_FRAMES);

	/* Set advanced operation modes. */
	cue_csr_write_1(sc, CUE_ADVANCED_OPMODES,
	    CUE_AOP_EMBED_RXLEN | 0x01);/* 1 wait state */

	/* Program the LED operation. */
	cue_csr_write_1(sc, CUE_LEDCTL, CUE_LEDCTL_FOLLOW_LINK);

	usbd_xfer_set_stall(sc->sc_xfer[CUE_BULK_DT_WR]);

	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	cue_start(ue);
}