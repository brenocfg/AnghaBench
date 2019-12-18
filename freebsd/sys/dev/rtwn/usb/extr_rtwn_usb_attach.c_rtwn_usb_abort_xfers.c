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
struct rtwn_usb_softc {int /*<<< orphan*/ * uc_xfer; } ;
struct rtwn_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTWN_ASSERT_LOCKED (struct rtwn_softc*) ; 
 int /*<<< orphan*/  RTWN_LOCK (struct rtwn_softc*) ; 
 int RTWN_N_TRANSFER ; 
 int /*<<< orphan*/  RTWN_UNLOCK (struct rtwn_softc*) ; 
 struct rtwn_usb_softc* RTWN_USB_SOFTC (struct rtwn_softc*) ; 
 int /*<<< orphan*/  usbd_transfer_drain (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rtwn_usb_abort_xfers(struct rtwn_softc *sc)
{
	struct rtwn_usb_softc *uc = RTWN_USB_SOFTC(sc);
	int i;

	RTWN_ASSERT_LOCKED(sc);

	/* abort any pending transfers */
	RTWN_UNLOCK(sc);
	for (i = 0; i < RTWN_N_TRANSFER; i++)
		usbd_transfer_drain(uc->uc_xfer[i]);
	RTWN_LOCK(sc);
}