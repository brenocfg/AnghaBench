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
struct urtw_softc {int sc_flags; int /*<<< orphan*/ * sc_xfer; } ;

/* Variables and functions */
 int URTW_8187B_N_XFERS ; 
 int URTW_8187L_N_XFERS ; 
 int /*<<< orphan*/  URTW_ASSERT_LOCKED (struct urtw_softc*) ; 
 int URTW_RTL8187B ; 
 int /*<<< orphan*/  usbd_transfer_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
urtw_abort_xfers(struct urtw_softc *sc)
{
	int i, max;

	URTW_ASSERT_LOCKED(sc);

	max = (sc->sc_flags & URTW_RTL8187B) ? URTW_8187B_N_XFERS :
	    URTW_8187L_N_XFERS;

	/* abort any pending transfers */
	for (i = 0; i < max; i++)
		usbd_transfer_stop(sc->sc_xfer[i]);
}