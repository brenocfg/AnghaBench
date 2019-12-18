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
typedef  int uint32_t ;
struct fhc_softc {int /*<<< orphan*/ * sc_memres; } ;

/* Variables and functions */
 int /*<<< orphan*/  FHC_CTRL ; 
 int FHC_CTRL_AOFF ; 
 int FHC_CTRL_BOFF ; 
 int FHC_CTRL_RLED ; 
 int FHC_CTRL_SLINE ; 
 size_t FHC_INTERNAL ; 
 int bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
fhc_led_func(void *arg, int onoff)
{
	struct fhc_softc *sc;
	uint32_t ctrl;

	sc = (struct fhc_softc *)arg;

	ctrl = bus_read_4(sc->sc_memres[FHC_INTERNAL], FHC_CTRL);
	if (onoff)
		ctrl |= FHC_CTRL_RLED;
	else
		ctrl &= ~FHC_CTRL_RLED;
	ctrl &= ~(FHC_CTRL_AOFF | FHC_CTRL_BOFF | FHC_CTRL_SLINE);
	bus_write_4(sc->sc_memres[FHC_INTERNAL], FHC_CTRL, ctrl);
	(void)bus_read_4(sc->sc_memres[FHC_INTERNAL], FHC_CTRL);
}