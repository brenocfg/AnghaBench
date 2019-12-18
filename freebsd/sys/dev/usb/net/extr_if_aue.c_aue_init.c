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
struct aue_softc {int /*<<< orphan*/ * sc_xfer; } ;

/* Variables and functions */
 size_t AUE_BULK_DT_WR ; 
 scalar_t__ AUE_CTL0 ; 
 int AUE_CTL0_RXSTAT_APPEND ; 
 int AUE_CTL0_RX_ENB ; 
 int /*<<< orphan*/  AUE_CTL0_TX_ENB ; 
 scalar_t__ AUE_CTL2 ; 
 int /*<<< orphan*/  AUE_CTL2_EP3_CLR ; 
 int /*<<< orphan*/  AUE_LOCK_ASSERT (struct aue_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ AUE_PAR0 ; 
 int /*<<< orphan*/  AUE_SETBIT (struct aue_softc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int* IF_LLADDR (struct ifnet*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  aue_csr_write_1 (struct aue_softc*,scalar_t__,int) ; 
 int /*<<< orphan*/  aue_reset (struct aue_softc*) ; 
 int /*<<< orphan*/  aue_setmulti (struct usb_ether*) ; 
 int /*<<< orphan*/  aue_setpromisc (struct usb_ether*) ; 
 int /*<<< orphan*/  aue_start (struct usb_ether*) ; 
 struct ifnet* uether_getifp (struct usb_ether*) ; 
 struct aue_softc* uether_getsc (struct usb_ether*) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
aue_init(struct usb_ether *ue)
{
	struct aue_softc *sc = uether_getsc(ue);
	struct ifnet *ifp = uether_getifp(ue);
	int i;

	AUE_LOCK_ASSERT(sc, MA_OWNED);

	/*
	 * Cancel pending I/O
	 */
	aue_reset(sc);

	/* Set MAC address */
	for (i = 0; i != ETHER_ADDR_LEN; i++)
		aue_csr_write_1(sc, AUE_PAR0 + i, IF_LLADDR(ifp)[i]);

	/* update promiscuous setting */
	aue_setpromisc(ue);

	/* Load the multicast filter. */
	aue_setmulti(ue);

	/* Enable RX and TX */
	aue_csr_write_1(sc, AUE_CTL0, AUE_CTL0_RXSTAT_APPEND | AUE_CTL0_RX_ENB);
	AUE_SETBIT(sc, AUE_CTL0, AUE_CTL0_TX_ENB);
	AUE_SETBIT(sc, AUE_CTL2, AUE_CTL2_EP3_CLR);

	usbd_xfer_set_stall(sc->sc_xfer[AUE_BULK_DT_WR]);

	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	aue_start(ue);
}