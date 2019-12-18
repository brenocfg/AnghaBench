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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int clock; } ;
struct bcm_sdhci_softc {TYPE_1__ sc_slot; int /*<<< orphan*/  sc_bsh; int /*<<< orphan*/  sc_bst; } ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
WR4(struct bcm_sdhci_softc *sc, bus_size_t off, uint32_t val)
{

	bus_space_write_4(sc->sc_bst, sc->sc_bsh, off, val);
	/*
	 * The Arasan HC has a bug where it may lose the content of
	 * consecutive writes to registers that are within two SD-card
	 * clock cycles of each other (a clock domain crossing problem). 
	 */
	if (sc->sc_slot.clock > 0)
		DELAY(((2 * 1000000) / sc->sc_slot.clock) + 1);
}