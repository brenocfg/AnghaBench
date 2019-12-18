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
struct uath_softc {int /*<<< orphan*/ * sc_xfer; } ;

/* Variables and functions */
 int /*<<< orphan*/  UATH_ASSERT_LOCKED (struct uath_softc*) ; 
 int UATH_N_XFERS ; 
 int /*<<< orphan*/  usbd_transfer_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uath_abort_xfers(struct uath_softc *sc)
{
	int i;

	UATH_ASSERT_LOCKED(sc);
	/* abort any pending transfers */
	for (i = 0; i < UATH_N_XFERS; i++)
		usbd_transfer_stop(sc->sc_xfer[i]);
}