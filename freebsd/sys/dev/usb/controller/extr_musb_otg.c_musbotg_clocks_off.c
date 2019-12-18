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
struct musbotg_softc {TYPE_1__ sc_flags; int /*<<< orphan*/  sc_clocks_arg; int /*<<< orphan*/  (* sc_clocks_off ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
musbotg_clocks_off(struct musbotg_softc *sc)
{
	if (!sc->sc_flags.clocks_off) {

		DPRINTFN(4, "\n");

		/* XXX disable Transceiver */

		if (sc->sc_clocks_off) {
			(sc->sc_clocks_off) (sc->sc_clocks_arg);
		}
		sc->sc_flags.clocks_off = 1;
	}
}