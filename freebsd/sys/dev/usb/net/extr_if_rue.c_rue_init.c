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
struct rue_softc {int /*<<< orphan*/ * sc_xfer; } ;
struct ifnet {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IF_LLADDR (struct ifnet*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 size_t RUE_BULK_DT_WR ; 
 int /*<<< orphan*/  RUE_CR ; 
 int RUE_CR_EP3CLREN ; 
 int RUE_CR_RE ; 
 int RUE_CR_TE ; 
 int /*<<< orphan*/  RUE_IDR0 ; 
 int /*<<< orphan*/  RUE_LOCK_ASSERT (struct rue_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RUE_RCR ; 
 int RUE_RCR_AB ; 
 int RUE_RCR_CONFIG ; 
 int /*<<< orphan*/  RUE_TCR ; 
 int RUE_TCR_CONFIG ; 
 int /*<<< orphan*/  rue_csr_write_1 (struct rue_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rue_csr_write_2 (struct rue_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rue_reset (struct rue_softc*) ; 
 int /*<<< orphan*/  rue_setmulti (struct usb_ether*) ; 
 int /*<<< orphan*/  rue_setpromisc (struct usb_ether*) ; 
 int /*<<< orphan*/  rue_start (struct usb_ether*) ; 
 int /*<<< orphan*/  rue_stop (struct usb_ether*) ; 
 int /*<<< orphan*/  rue_write_mem (struct rue_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ifnet* uether_getifp (struct usb_ether*) ; 
 struct rue_softc* uether_getsc (struct usb_ether*) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rue_init(struct usb_ether *ue)
{
	struct rue_softc *sc = uether_getsc(ue);
	struct ifnet *ifp = uether_getifp(ue);

	RUE_LOCK_ASSERT(sc, MA_OWNED);

	/*
	 * Cancel pending I/O
	 */
	rue_reset(sc);

	/* Set MAC address */
	rue_write_mem(sc, RUE_IDR0, IF_LLADDR(ifp), ETHER_ADDR_LEN);

	rue_stop(ue);

	/*
	 * Set the initial TX and RX configuration.
	 */
	rue_csr_write_1(sc, RUE_TCR, RUE_TCR_CONFIG);
	rue_csr_write_2(sc, RUE_RCR, RUE_RCR_CONFIG|RUE_RCR_AB);

	/* Load the multicast filter */
	rue_setpromisc(ue);
	/* Load the multicast filter. */
	rue_setmulti(ue);

	/* Enable RX and TX */
	rue_csr_write_1(sc, RUE_CR, (RUE_CR_TE | RUE_CR_RE | RUE_CR_EP3CLREN));

	usbd_xfer_set_stall(sc->sc_xfer[RUE_BULK_DT_WR]);

	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	rue_start(ue);
}