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
struct upgt_softc {int /*<<< orphan*/ * sc_xfer; } ;

/* Variables and functions */
 int /*<<< orphan*/  UPGT_ASSERT_LOCKED (struct upgt_softc*) ; 
 int UPGT_N_XFERS ; 
 int /*<<< orphan*/  usbd_transfer_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
upgt_abort_xfers_locked(struct upgt_softc *sc)
{
	int i;

	UPGT_ASSERT_LOCKED(sc);
	/* abort any pending transfers */
	for (i = 0; i < UPGT_N_XFERS; i++)
		usbd_transfer_stop(sc->sc_xfer[i]);
}