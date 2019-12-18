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
struct mpc85xx_rcpm_softc {int /*<<< orphan*/  sc_mem; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  RCPM_CTBENR ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct mpc85xx_rcpm_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int maxcpu ; 

__attribute__((used)) static void
mpc85xx_rcpm_freeze_timebase(device_t dev, bool freeze)
{
	struct mpc85xx_rcpm_softc *sc;

	sc = device_get_softc(dev);
	
	if (freeze)
		bus_write_4(sc->sc_mem, RCPM_CTBENR, 0);
	else
		bus_write_4(sc->sc_mem, RCPM_CTBENR, (1 << maxcpu) - 1);
}