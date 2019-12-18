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
struct gicv3_its_softc {int /*<<< orphan*/  sc_its_flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ITS_FLAGS_ERRATA_CAVIUM_22375 ; 
 struct gicv3_its_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
its_quirk_cavium_22375(device_t dev)
{
	struct gicv3_its_softc *sc;

	sc = device_get_softc(dev);
	sc->sc_its_flags |= ITS_FLAGS_ERRATA_CAVIUM_22375;
}