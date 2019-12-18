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
 size_t CUE_BULK_DT_RD ; 
 size_t CUE_BULK_DT_WR ; 
 int /*<<< orphan*/  CUE_ETHCTL ; 
 int /*<<< orphan*/  CUE_LOCK_ASSERT (struct cue_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  cue_csr_write_1 (struct cue_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cue_reset (struct cue_softc*) ; 
 struct ifnet* uether_getifp (struct usb_ether*) ; 
 struct cue_softc* uether_getsc (struct usb_ether*) ; 
 int /*<<< orphan*/  usbd_transfer_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cue_stop(struct usb_ether *ue)
{
	struct cue_softc *sc = uether_getsc(ue);
	struct ifnet *ifp = uether_getifp(ue);

	CUE_LOCK_ASSERT(sc, MA_OWNED);

	ifp->if_drv_flags &= ~IFF_DRV_RUNNING;

	/*
	 * stop all the transfers, if not already stopped:
	 */
	usbd_transfer_stop(sc->sc_xfer[CUE_BULK_DT_WR]);
	usbd_transfer_stop(sc->sc_xfer[CUE_BULK_DT_RD]);

	cue_csr_write_1(sc, CUE_ETHCTL, 0);
	cue_reset(sc);
}