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
struct rtwn_softc {int /*<<< orphan*/  sc_mtx; } ;
struct rtwn_usb_softc {int /*<<< orphan*/  uc_xfer; struct rtwn_softc uc_sc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  RTWN_N_TRANSFER ; 
 struct rtwn_usb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtwn_detach (struct rtwn_softc*) ; 
 int /*<<< orphan*/  rtwn_detach_private (struct rtwn_softc*) ; 
 int /*<<< orphan*/  rtwn_usb_free_rx_list (struct rtwn_softc*) ; 
 int /*<<< orphan*/  rtwn_usb_free_tx_list (struct rtwn_softc*) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rtwn_usb_detach(device_t self)
{
	struct rtwn_usb_softc *uc = device_get_softc(self);
	struct rtwn_softc *sc = &uc->uc_sc;

	/* Generic detach. */
	rtwn_detach(sc);

	/* Free Tx/Rx buffers. */
	rtwn_usb_free_tx_list(sc);
	rtwn_usb_free_rx_list(sc);

	/* Detach all USB transfers. */
	usbd_transfer_unsetup(uc->uc_xfer, RTWN_N_TRANSFER);

	rtwn_detach_private(sc);
	mtx_destroy(&sc->sc_mtx);

	return (0);
}