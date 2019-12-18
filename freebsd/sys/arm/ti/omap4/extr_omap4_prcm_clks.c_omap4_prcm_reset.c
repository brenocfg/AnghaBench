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
struct omap4_prcm_softc {int /*<<< orphan*/  sc_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRM_INSTANCE ; 
 int /*<<< orphan*/  PRM_RSTCTRL ; 
 int PRM_RSTCTRL_RESET ; 
 int bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct omap4_prcm_softc* omap4_prcm_get_instance_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
omap4_prcm_reset(void)
{
	struct omap4_prcm_softc *sc;
	
	sc = omap4_prcm_get_instance_softc(PRM_INSTANCE);
	if (sc == NULL)
		return;

	bus_write_4(sc->sc_res, PRM_RSTCTRL,
	    bus_read_4(sc->sc_res, PRM_RSTCTRL) | PRM_RSTCTRL_RESET);
	bus_read_4(sc->sc_res, PRM_RSTCTRL);
}