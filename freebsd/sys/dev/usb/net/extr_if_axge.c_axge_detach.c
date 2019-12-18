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
typedef  int uint16_t ;
struct usb_ether {int /*<<< orphan*/  ue_tq; } ;
struct axge_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_xfer; struct usb_ether sc_ue; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AXGE_ACCESS_MAC ; 
 int /*<<< orphan*/  AXGE_CLK_SELECT ; 
 int /*<<< orphan*/  AXGE_EPPRCR ; 
 int /*<<< orphan*/  AXGE_LOCK (struct axge_softc*) ; 
 int /*<<< orphan*/  AXGE_N_TRANSFER ; 
 int /*<<< orphan*/  AXGE_RCR ; 
 int /*<<< orphan*/  AXGE_UNLOCK (struct axge_softc*) ; 
 int EPPRCR_BZ ; 
 int EPPRCR_IPRL ; 
 int axge_read_cmd_2 (struct axge_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axge_stop (struct usb_ether*) ; 
 int /*<<< orphan*/  axge_write_cmd_1 (struct axge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axge_write_cmd_2 (struct axge_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 struct axge_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uether_ifdetach (struct usb_ether*) ; 
 int /*<<< orphan*/  usb_proc_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
axge_detach(device_t dev)
{
	struct axge_softc *sc;
	struct usb_ether *ue;
	uint16_t val;

	sc = device_get_softc(dev);
	ue = &sc->sc_ue;
	if (device_is_attached(dev)) {

		/* wait for any post attach or other command to complete */
		usb_proc_drain(&ue->ue_tq);

		AXGE_LOCK(sc);
		/*
		 * XXX
		 * ether_ifdetach(9) should be called first.
		 */
		axge_stop(ue);
		/* Force bulk-in to return a zero-length USB packet. */
		val = axge_read_cmd_2(sc, AXGE_ACCESS_MAC, 2, AXGE_EPPRCR);
		val |= EPPRCR_BZ | EPPRCR_IPRL;
		axge_write_cmd_2(sc, AXGE_ACCESS_MAC, 2, AXGE_EPPRCR, val);
		/* Change clock. */
		axge_write_cmd_1(sc, AXGE_ACCESS_MAC, AXGE_CLK_SELECT, 0);
		/* Disable MAC. */
		axge_write_cmd_2(sc, AXGE_ACCESS_MAC, 2, AXGE_RCR, 0);
		AXGE_UNLOCK(sc);
	}
	usbd_transfer_unsetup(sc->sc_xfer, AXGE_N_TRANSFER);
	uether_ifdetach(ue);
	mtx_destroy(&sc->sc_mtx);

	return (0);
}