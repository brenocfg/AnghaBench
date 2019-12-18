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
struct TYPE_2__ {scalar_t__ clocks_off; scalar_t__ port_powered; } ;
struct avr32dci_softc {TYPE_1__ sc_flags; int /*<<< orphan*/  sc_bus; int /*<<< orphan*/  (* sc_clocks_on ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AVR32_CTRL_DEV_EN_USBA ; 
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int /*<<< orphan*/  avr32dci_mod_ctrl (struct avr32dci_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
avr32dci_clocks_on(struct avr32dci_softc *sc)
{
	if (sc->sc_flags.clocks_off &&
	    sc->sc_flags.port_powered) {

		DPRINTFN(5, "\n");

		/* turn on clocks */
		(sc->sc_clocks_on) (&sc->sc_bus);

		avr32dci_mod_ctrl(sc, AVR32_CTRL_DEV_EN_USBA, 0);

		sc->sc_flags.clocks_off = 0;
	}
}