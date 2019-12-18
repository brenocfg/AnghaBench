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
struct aue_softc {int /*<<< orphan*/ * sc_xfer; int /*<<< orphan*/  sc_flags; } ;

/* Variables and functions */
 size_t AUE_BULK_DT_RD ; 
 size_t AUE_BULK_DT_WR ; 
 int /*<<< orphan*/  AUE_CTL0 ; 
 int /*<<< orphan*/  AUE_CTL1 ; 
 int /*<<< orphan*/  AUE_FLAG_LINK ; 
 size_t AUE_INTR_DT_RD ; 
 int /*<<< orphan*/  AUE_LOCK_ASSERT (struct aue_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  aue_csr_write_1 (struct aue_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aue_reset (struct aue_softc*) ; 
 struct ifnet* uether_getifp (struct usb_ether*) ; 
 struct aue_softc* uether_getsc (struct usb_ether*) ; 
 int /*<<< orphan*/  usbd_transfer_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
aue_stop(struct usb_ether *ue)
{
	struct aue_softc *sc = uether_getsc(ue);
	struct ifnet *ifp = uether_getifp(ue);

	AUE_LOCK_ASSERT(sc, MA_OWNED);

	ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
	sc->sc_flags &= ~AUE_FLAG_LINK;

	/*
	 * stop all the transfers, if not already stopped:
	 */
	usbd_transfer_stop(sc->sc_xfer[AUE_BULK_DT_WR]);
	usbd_transfer_stop(sc->sc_xfer[AUE_BULK_DT_RD]);
	usbd_transfer_stop(sc->sc_xfer[AUE_INTR_DT_RD]);

	aue_csr_write_1(sc, AUE_CTL0, 0);
	aue_csr_write_1(sc, AUE_CTL1, 0);
	aue_reset(sc);
}