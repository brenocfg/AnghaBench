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
struct otus_softc {int /*<<< orphan*/  sc_xfer; } ;

/* Variables and functions */
 int /*<<< orphan*/  OTUS_LOCK (struct otus_softc*) ; 
 int /*<<< orphan*/  OTUS_N_XFER ; 
 int /*<<< orphan*/  OTUS_UNLOCK (struct otus_softc*) ; 
 int /*<<< orphan*/  otus_free_rx_list (struct otus_softc*) ; 
 int /*<<< orphan*/  otus_free_tx_cmd_list (struct otus_softc*) ; 
 int /*<<< orphan*/  otus_free_tx_list (struct otus_softc*) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
otus_close_pipes(struct otus_softc *sc)
{

	OTUS_LOCK(sc);
	otus_free_tx_cmd_list(sc);
	otus_free_tx_list(sc);
	otus_free_rx_list(sc);
	OTUS_UNLOCK(sc);

	usbd_transfer_unsetup(sc->sc_xfer, OTUS_N_XFER);
}