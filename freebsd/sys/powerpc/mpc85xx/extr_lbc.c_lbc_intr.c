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
typedef  int /*<<< orphan*/  uint32_t ;
struct lbc_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_bsh; int /*<<< orphan*/  sc_bst; int /*<<< orphan*/  sc_ltesr; } ;

/* Variables and functions */
 int /*<<< orphan*/  LBC85XX_LTESR ; 
 int /*<<< orphan*/  bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lbc_intr(void *arg)
{
	struct lbc_softc *sc = arg;
	uint32_t ltesr;

	ltesr = bus_space_read_4(sc->sc_bst, sc->sc_bsh, LBC85XX_LTESR);
	sc->sc_ltesr = ltesr;
	bus_space_write_4(sc->sc_bst, sc->sc_bsh, LBC85XX_LTESR, ltesr);
	wakeup(sc->sc_dev);
}