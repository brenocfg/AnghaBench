#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  bus_mtx; } ;
struct TYPE_3__ {int /*<<< orphan*/  status_suspend; } ;
struct atmegadci_softc {TYPE_2__ sc_bus; TYPE_1__ sc_flags; } ;

/* Variables and functions */
 int ATMEGA_READ_1 (struct atmegadci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATMEGA_UDCON ; 
 int ATMEGA_UDCON_RMWKUP ; 
 int /*<<< orphan*/  ATMEGA_WRITE_1 (struct atmegadci_softc*,int /*<<< orphan*/ ,int) ; 
 int hz ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
atmegadci_wakeup_peer(struct atmegadci_softc *sc)
{
	uint8_t temp;

	if (!sc->sc_flags.status_suspend) {
		return;
	}

	temp = ATMEGA_READ_1(sc, ATMEGA_UDCON);
	ATMEGA_WRITE_1(sc, ATMEGA_UDCON, temp | ATMEGA_UDCON_RMWKUP);

	/* wait 8 milliseconds */
	/* Wait for reset to complete. */
	usb_pause_mtx(&sc->sc_bus.bus_mtx, hz / 125);

	/* hardware should have cleared RMWKUP bit */
}