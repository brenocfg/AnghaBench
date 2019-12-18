#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int clocks_off; } ;
struct atmegadci_softc {TYPE_1__ sc_flags; int /*<<< orphan*/  sc_bus; int /*<<< orphan*/  (* sc_clocks_off ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEGA_USBCON ; 
 int ATMEGA_USBCON_FRZCLK ; 
 int ATMEGA_USBCON_OTGPADE ; 
 int ATMEGA_USBCON_USBE ; 
 int ATMEGA_USBCON_VBUSTE ; 
 int /*<<< orphan*/  ATMEGA_WRITE_1 (struct atmegadci_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
atmegadci_clocks_off(struct atmegadci_softc *sc)
{
	if (!sc->sc_flags.clocks_off) {

		DPRINTFN(5, "\n");

		/* disable Transceiver ? */

		ATMEGA_WRITE_1(sc, ATMEGA_USBCON,
		    ATMEGA_USBCON_USBE |
		    ATMEGA_USBCON_OTGPADE |
		    ATMEGA_USBCON_FRZCLK |
		    ATMEGA_USBCON_VBUSTE);

		/* turn clocks off */
		(sc->sc_clocks_off) (&sc->sc_bus);

		sc->sc_flags.clocks_off = 1;
	}
}