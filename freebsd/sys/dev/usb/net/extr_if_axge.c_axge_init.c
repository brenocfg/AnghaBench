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
struct ifnet {int if_drv_flags; } ;
struct axge_softc {int /*<<< orphan*/ * sc_xfer; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXGE_ACCESS_MAC ; 
 size_t AXGE_BULK_DT_WR ; 
 int /*<<< orphan*/  AXGE_LOCK_ASSERT (struct axge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AXGE_MMSR ; 
 int /*<<< orphan*/  AXGE_MSR ; 
 int /*<<< orphan*/  AXGE_NIDR ; 
 int /*<<< orphan*/  AXGE_PWLHR ; 
 int /*<<< orphan*/  AXGE_PWLLR ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IF_LLADDR (struct ifnet*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int MSR_FD ; 
 int MSR_GM ; 
 int MSR_RE ; 
 int MSR_RFC ; 
 int MSR_TFC ; 
 int /*<<< orphan*/  axge_csum_cfg (struct usb_ether*) ; 
 int /*<<< orphan*/  axge_ifmedia_upd (struct ifnet*) ; 
 int /*<<< orphan*/  axge_read_cmd_1 (struct axge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axge_reset (struct axge_softc*) ; 
 int /*<<< orphan*/  axge_rxfilter (struct usb_ether*) ; 
 int /*<<< orphan*/  axge_stop (struct usb_ether*) ; 
 int /*<<< orphan*/  axge_write_cmd_1 (struct axge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  axge_write_cmd_2 (struct axge_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  axge_write_mem (struct axge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ifnet* uether_getifp (struct usb_ether*) ; 
 struct axge_softc* uether_getsc (struct usb_ether*) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
axge_init(struct usb_ether *ue)
{
	struct axge_softc *sc;
	struct ifnet *ifp;

	sc = uether_getsc(ue);
	ifp = uether_getifp(ue);
	AXGE_LOCK_ASSERT(sc, MA_OWNED);

	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0)
		return;

	/*
	 * Cancel pending I/O and free all RX/TX buffers.
	 */
	axge_stop(ue);

	axge_reset(sc);

	/* Set MAC address. */
	axge_write_mem(sc, AXGE_ACCESS_MAC, ETHER_ADDR_LEN, AXGE_NIDR,
	    IF_LLADDR(ifp), ETHER_ADDR_LEN);

	axge_write_cmd_1(sc, AXGE_ACCESS_MAC, AXGE_PWLLR, 0x34);
	axge_write_cmd_1(sc, AXGE_ACCESS_MAC, AXGE_PWLHR, 0x52);

	/* Configure TX/RX checksum offloading. */
	axge_csum_cfg(ue);

	/*  Configure RX filters. */
	axge_rxfilter(ue);

	/*
	 * XXX
	 * Controller supports wakeup on link change detection,
	 * magic packet and wakeup frame recpetion.  But it seems
	 * there is no framework for USB ethernet suspend/wakeup.
	 * Disable all wakeup functions.
	 */
	axge_write_cmd_1(sc, AXGE_ACCESS_MAC, AXGE_MMSR, 0);
	(void)axge_read_cmd_1(sc, AXGE_ACCESS_MAC, AXGE_MMSR);

	/* Configure default medium type. */
	axge_write_cmd_2(sc, AXGE_ACCESS_MAC, 2, AXGE_MSR, MSR_GM | MSR_FD |
	    MSR_RFC | MSR_TFC | MSR_RE);

	usbd_xfer_set_stall(sc->sc_xfer[AXGE_BULK_DT_WR]);

	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	/* Switch to selected media. */
	axge_ifmedia_upd(ifp);
}