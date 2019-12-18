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
struct urndis_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_xfer; struct usb_ether sc_ue; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  URNDIS_LOCK (struct urndis_softc*) ; 
 int /*<<< orphan*/  URNDIS_N_TRANSFER ; 
 int /*<<< orphan*/  URNDIS_UNLOCK (struct urndis_softc*) ; 
 struct urndis_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uether_ifdetach (struct usb_ether*) ; 
 int /*<<< orphan*/  urndis_ctrl_halt (struct urndis_softc*) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
urndis_detach(device_t dev)
{
	struct urndis_softc *sc = device_get_softc(dev);
	struct usb_ether *ue = &sc->sc_ue;

	/* stop all USB transfers first */
	usbd_transfer_unsetup(sc->sc_xfer, URNDIS_N_TRANSFER);

	uether_ifdetach(ue);

	URNDIS_LOCK(sc);
	(void)urndis_ctrl_halt(sc);
	URNDIS_UNLOCK(sc);

	mtx_destroy(&sc->sc_mtx);

	return (0);
}