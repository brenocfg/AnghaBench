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
typedef  int /*<<< orphan*/  uint16_t ;
struct usb_ether {int dummy; } ;
struct ifnet {int if_drv_flags; } ;
struct axge_softc {int /*<<< orphan*/ * sc_xfer; int /*<<< orphan*/  sc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXGE_ACCESS_MAC ; 
 size_t AXGE_BULK_DT_RD ; 
 size_t AXGE_BULK_DT_WR ; 
 int /*<<< orphan*/  AXGE_FLAG_LINK ; 
 int /*<<< orphan*/  AXGE_LOCK_ASSERT (struct axge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AXGE_MSR ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MSR_RE ; 
 int /*<<< orphan*/  axge_read_cmd_2 (struct axge_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axge_write_cmd_2 (struct axge_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ifnet* uether_getifp (struct usb_ether*) ; 
 struct axge_softc* uether_getsc (struct usb_ether*) ; 
 int /*<<< orphan*/  usbd_transfer_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
axge_stop(struct usb_ether *ue)
{
	struct axge_softc *sc;
	struct ifnet *ifp;
	uint16_t val;

	sc = uether_getsc(ue);
	ifp = uether_getifp(ue);

	AXGE_LOCK_ASSERT(sc, MA_OWNED);

	val = axge_read_cmd_2(sc, AXGE_ACCESS_MAC, 2, AXGE_MSR);
	val &= ~MSR_RE;
	axge_write_cmd_2(sc, AXGE_ACCESS_MAC, 2, AXGE_MSR, val);

	if (ifp != NULL)
		ifp->if_drv_flags &= ~(IFF_DRV_RUNNING | IFF_DRV_OACTIVE);
	sc->sc_flags &= ~AXGE_FLAG_LINK;

	/*
	 * Stop all the transfers, if not already stopped:
	 */
	usbd_transfer_stop(sc->sc_xfer[AXGE_BULK_DT_WR]);
	usbd_transfer_stop(sc->sc_xfer[AXGE_BULK_DT_RD]);
}